import { marked } from './vendor/marked.esm.js';
import DOMPurify from './vendor/purify.es.js';
import katex from './katex/katex.js';

// Raw HTML is not part of forum Markdown. KaTeX HTML is generated separately.
marked.use({renderer:{html:()=>''}});

const root=document.querySelector('[data-qa]');
const $=selector=>root.querySelector(selector);
const apiBase=root.dataset.api.replace(/\/$/,'');
const base=root.dataset.base;
let session=null,threadId=null,threadData=null,page=0,hasMore=false,aiReady=false,notes=[],pendingAi=null,pollTimer,searchTimer;
let listingSequence=0,detailSequence=0;
try { session=JSON.parse(localStorage.getItem('sufe-qa-session')||'null'); } catch {}
const element=(tag,className,text)=>{const node=document.createElement(tag);if(className)node.className=className;if(text!==undefined)node.textContent=text;return node;};
const date=value=>new Date(value).toLocaleString('zh-CN',{month:'numeric',day:'numeric',hour:'2-digit',minute:'2-digit',hour12:false});
function toast(message){const node=$('[data-qa-toast]');node.textContent=message;node.classList.add('visible');setTimeout(()=>node.classList.remove('visible'),3200);}
function error(message){const node=$('[data-global-error]');node.textContent=message;node.hidden=!message;}
function renderMarkdown(text){
  const math=[],prefix=`MATH${crypto.randomUUID().replaceAll('-','')}TOKEN`;
  const source=String(text).split(/(```[\s\S]*?```|~~~[\s\S]*?~~~|`[^`\n]*`)/g).map((part,i)=>i%2?part:part.replace(/\$\$([\s\S]+?)\$\$|(?<!\\)\$([^$\n]+?)\$/g,(_,display,inline)=>{
    const token=`${prefix}${math.length}END`;
    math.push(katex.renderToString(display||inline,{displayMode:!!display,throwOnError:false,trust:false,strict:false,maxSize:20,maxExpand:1000}));return token;
  })).join('');
  let html=marked.parse(source,{breaks:false,gfm:true});
  math.forEach((value,i)=>{html=html.replaceAll(`${prefix}${i}END`,value);});
  const fragment=DOMPurify.sanitize(html,{RETURN_DOM_FRAGMENT:true,FORBID_TAGS:['img','iframe','video','audio','object','embed','form','input','button','style'],FORBID_ATTR:['id','name']});
  for(const link of fragment.querySelectorAll('a')){
    try{const url=new URL(link.getAttribute('href'),location.href);if(!['https:','http:'].includes(url.protocol))throw 0;link.href=url.href;link.target='_blank';link.rel='noopener noreferrer nofollow';}catch{link.removeAttribute('href');}
  }
  return fragment;
}
async function api(path,{method='GET',body,timeout=105000}={}){
  const response=await fetch(`${apiBase}${path}`,{method,headers:{...(body?{'Content-Type':'application/json'}:{}),...(session?.token?{Authorization:`Bearer ${session.token}`}:{})},...(body?{body:JSON.stringify(body)}:{}),credentials:'omit',signal:AbortSignal.timeout(timeout)});
  let data;try{data=await response.json();}catch{throw new Error('服务返回异常，请稍后重试。');}
  if(!response.ok){if(response.status===401){session=null;try{localStorage.removeItem('sufe-qa-session');}catch{}updateSession();}throw new Error(data.error||'请求未完成，请稍后重试。');}
  return data;
}
function updateSession(){
  $('[data-login]').textContent=session?`${session.user.name}${session.user.role==='admin'?' · 维护者':''}`:'进入学习区';
  $('[data-logout]').hidden=!session;
}
function requireSession(){if(session)return true;$('[data-login-dialog]').showModal();return false;}
$('[data-login]').addEventListener('click',()=>{$('[data-login-dialog]').showModal();});
$('[data-close-login]').addEventListener('click',()=>{$('[data-login-dialog]').close();});
$('[data-logout]').addEventListener('click',()=>{session=null;try{localStorage.removeItem('sufe-qa-session');}catch{}updateSession();if(threadData)renderThread(threadData);toast('已退出学习区。');});
$('[data-login-form]').addEventListener('submit',async event=>{
  event.preventDefault();const form=event.currentTarget,button=form.querySelector('[type=submit]');button.disabled=true;$('[data-login-error]').hidden=true;
  try{
    session=await api('/api/session',{method:'POST',body:{name:form.elements.name.value,code:form.elements.code.value},timeout:15000});
    try{localStorage.setItem('sufe-qa-session',JSON.stringify(session));}catch{}
    form.elements.code.value='';updateSession();$('[data-login-dialog]').close();if(threadData)renderThread(threadData);toast('已进入学习区，可以继续发布问题或回复。');
  }catch(err){$('[data-login-error]').textContent=err.message;$('[data-login-error]').hidden=false;}finally{button.disabled=false;}
});
async function listThreads(){
  const sequence=++listingSequence;
  const query=new URLSearchParams({q:$('#qa-search').value,course:$('#qa-filter').value,page:String(page)});
  try{
    const data=await api(`/api/threads?${query}`,{timeout:15000});if(sequence!==listingSequence)return;
    hasMore=data.hasMore;const list=$('[data-thread-list]');list.replaceChildren();
    if(!data.threads.length){const empty=element('div','qa-empty');empty.append(element('strong','',page||query.get('q')||query.get('course')?'没有找到相关问题':'第一道问题，等你来提。'),element('p','','想不通的一步，也许正是其他同学的疑惑。'));list.append(empty);}
    for(const thread of data.threads){
      const button=element('button',`qa-thread-item${thread.id===threadId?' active':''}`);button.type='button';button.append(element('strong','',thread.title));
      button.append(element('span','',`${thread.course||'学习交流'} · ${thread.replies} 条回复`));
      if(thread.aiStatus==='answered')button.append(element('span','qa-ai-label','✳ AI 已参与讨论'));
      button.addEventListener('click',()=>openThread(thread.id));list.append(button);
    }
    $('[data-page]').textContent=String(page+1);$('[data-prev-page]').disabled=page===0;$('[data-next-page]').disabled=!hasMore;
  }catch(err){if(sequence===listingSequence){$('[data-thread-list]').replaceChildren(element('p','qa-empty','讨论加载失败，请稍后重试。'));error(err.message);}}
}
$('#qa-search').addEventListener('input',()=>{clearTimeout(searchTimer);searchTimer=setTimeout(()=>{page=0;listThreads();},250);});
$('#qa-filter').addEventListener('change',()=>{page=0;listThreads();});
$('[data-prev-page]').addEventListener('click',()=>{if(page>0){page--;listThreads();}});
$('[data-next-page]').addEventListener('click',()=>{if(hasMore){page++;listThreads();}});
function currentUrl(id){const url=new URL(location.href);url.search='';if(id)url.searchParams.set('thread',id);return url;}
function showCompose(){threadId=null;threadData=null;detailSequence++;clearTimeout(pollTimer);$('[data-thread-view]').hidden=true;$('[data-compose-view]').hidden=false;history.pushState(null,'',currentUrl(null));listThreads();}
$('[data-new]').addEventListener('click',showCompose);$('[data-back]').addEventListener('click',showCompose);
for(const button of root.querySelectorAll('[data-example]'))button.addEventListener('click',()=>{$('#qa-title').value=button.dataset.example;$('#qa-body').focus();});
let noteId=new URLSearchParams(location.search).get('note')||'';
function updateNote(){const note=notes.find(n=>n.id===noteId);$('[data-note-context]').hidden=!note;if(note){$('[data-note-link]').textContent=note.title;$('[data-note-link]').href=`${base}notes/${note.id}/`;$('#qa-course').value=note.course;}else noteId='';}
$('[data-clear-note]').addEventListener('click',()=>{noteId='';updateNote();});
function moderateButton(replyId){const button=element('button','qa-text-button','隐藏');button.type='button';button.addEventListener('click',async()=>{
  if(!window.confirm('隐藏后，普通访客将无法看到这条内容。确定隐藏？'))return;
  try{await api(`/api/threads/${threadId}/moderate`,{method:'POST',body:replyId?{replyId}:{}});if(replyId)await loadThread(threadId);else showCompose();listThreads();toast('内容已隐藏。');}catch(err){error(err.message);}
});return button;}
function renderThread(data){
  threadData=data;const thread=data.thread,detail=$('[data-thread-detail]');detail.replaceChildren();
  const heading=element('header','qa-thread-heading'),meta=element('div','qa-meta');
  meta.append(element('span','qa-pill',thread.course||'学习交流'),element('span','',`${thread.author} · ${date(thread.createdAt)}`));
  if(session?.user.role==='admin')meta.append(moderateButton());
  heading.append(meta,element('h2','',thread.title));detail.append(heading);
  const body=element('div','qa-thread-body');body.append(renderMarkdown(thread.body));detail.append(body);
  if(thread.noteId && /^[a-f0-9]{12}$/.test(thread.noteId)){const link=element('a','qa-source','↗ 打开提问关联的笔记');link.href=`${base}notes/${thread.noteId}/`;detail.append(link);}
  const replies=$('[data-replies]');replies.replaceChildren();
  for(const reply of data.replies){
    const article=element('article',`qa-reply ${reply.kind==='assistant'?'assistant':'student'}`),header=element('div','qa-reply-header');
    header.append(element('span','qa-avatar',reply.kind==='assistant'?'✳':reply.author.slice(0,1)),element('strong','',reply.author),element('time','',date(reply.createdAt)));
    if(session?.user.role==='admin')header.append(moderateButton(reply.id));article.append(header);
    const content=element('div','qa-reply-body');content.append(renderMarkdown(reply.body));article.append(content);
    if(reply.sources?.length){
      const sources=element('div','qa-sources');sources.append(element('p','','本次实际查阅的笔记 · 点击核对原文'));
      reply.sources.forEach((source,i)=>{if(!/^[a-f0-9]{12}$/.test(source.id))return;const link=element('a','qa-source',`[${i+1}] ${source.title}`);link.href=`${base}notes/${source.id}/`;link.append(element('small','',source.course));sources.append(link);});article.append(sources);
    }
    replies.append(article);
  }
  const busy=thread.aiStatus==='running'||pendingAi===thread.id;const state=$('[data-agent-state]');
  state.hidden=!busy && thread.aiStatus!=='failed';state.classList.toggle('busy',busy);state.textContent=busy?'DeepSeek 正在查找资料并整理回答，通常需要一些时间…':thread.aiError||'AI 上次没有完成回答，可以稍后重试。';
  $('[data-ask-ai]').disabled=busy||!aiReady;$('[data-ask-ai]').textContent=!aiReady?'AI 服务准备中':data.replies.some(r=>r.kind==='assistant')?'请 AI 继续回答':'邀请 AI 回答';
  clearTimeout(pollTimer);if(busy)pollTimer=setTimeout(()=>{if(threadId===thread.id)loadThread(thread.id);},4000);
}
async function loadThread(id){const sequence=++detailSequence;try{const data=await api(`/api/threads/${id}`,{timeout:15000});if(sequence===detailSequence && threadId===id)renderThread(data);}catch(err){if(sequence===detailSequence)error(err.message);}}
async function openThread(id,push=true){if(!/^[a-f0-9-]{36}$/.test(id))return;threadId=id;clearTimeout(pollTimer);error('');$('[data-compose-view]').hidden=true;$('[data-thread-view]').hidden=false;$('[data-thread-detail]').replaceChildren(element('p','qa-muted','正在打开讨论…'));$('[data-replies]').replaceChildren();if(push)history.pushState(null,'',currentUrl(id));await loadThread(id);listThreads();}
window.addEventListener('popstate',()=>{const id=new URLSearchParams(location.search).get('thread');if(id)openThread(id,false);else{threadId=null;threadData=null;detailSequence++;clearTimeout(pollTimer);$('[data-thread-view]').hidden=true;$('[data-compose-view]').hidden=false;}});
async function askAi(id){
  if(!requireSession() || pendingAi===id)return;
  error('');
  pendingAi=id;if(threadData?.thread.id===id)renderThread(threadData);
  try{await api(`/api/threads/${id}/answer`,{method:'POST',body:{}});}catch(err){error(err.message);}finally{pendingAi=null;if(threadId===id)await loadThread(id);listThreads();}
}
$('[data-question-form]').addEventListener('submit',async event=>{
  event.preventDefault();if(!requireSession())return;const form=event.currentTarget,button=$('[data-publish]');button.disabled=true;error('');
  try{
    const data=await api('/api/threads',{method:'POST',body:{id:form.dataset.requestId||(form.dataset.requestId=crypto.randomUUID()),title:form.elements.title.value,body:form.elements.body.value,course:form.elements.course.value,noteId,publicConsent:form.elements.publicConsent.checked}});
    const inviteAi=form.elements.askAi.checked&&aiReady;form.reset();delete form.dataset.requestId;await openThread(data.thread.id);toast('问题已公开发布。');if(inviteAi)await askAi(data.thread.id);
  }catch(err){error(err.message);}finally{button.disabled=false;}
});
$('[data-reply-form]').addEventListener('submit',async event=>{
  event.preventDefault();if(!requireSession()||!threadId)return;const form=event.currentTarget,button=form.querySelector('button[type=submit]'),id=threadId;button.disabled=true;error('');
  try{await api(`/api/threads/${id}/replies`,{method:'POST',body:{id:form.dataset.requestId||(form.dataset.requestId=crypto.randomUUID()),body:$('#qa-reply').value,publicConsent:true}});form.reset();delete form.dataset.requestId;if(threadId===id)await loadThread(id);listThreads();toast('回复已公开发布。');}catch(err){error(err.message);}finally{button.disabled=false;}
});
$('[data-ask-ai]').addEventListener('click',()=>{if(threadId)askAi(threadId);});
$('[data-copy-thread]').addEventListener('click',async()=>{try{await navigator.clipboard.writeText(currentUrl(threadId).href);toast('讨论链接已复制。');}catch{toast('请复制浏览器地址栏中的链接。');}});
updateSession();
try{
  const [health,index]=await Promise.all([api('/api/health',{timeout:15000}),fetch(`${base}assets/notes-index.json`).then(r=>r.json())]);
  aiReady=health.aiReady;notes=index.notes;$('[data-service-status]').textContent=aiReady?'学习助教在线':'同学讨论已开放 · AI 准备中';$('.qa-status').classList.toggle('ready',health.ready);$('[data-demo]').hidden=!health.demo;
  $('[name=askAi]').disabled=!aiReady;if(!aiReady)$('[name=askAi]').checked=false;updateNote();await listThreads();
  const id=new URLSearchParams(location.search).get('thread');if(id)await openThread(id,false);
}catch(err){$('[data-service-status]').textContent='暂时无法连接学习区';error(`${err.message} 可以先浏览课程资料。`);$('[data-thread-list]').replaceChildren(element('p','qa-empty','学习区暂时无法连接。'));}
