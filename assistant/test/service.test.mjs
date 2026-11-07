import test from 'node:test';
import assert from 'node:assert/strict';
import {readFileSync,readdirSync} from 'node:fs';
import {localDatabase} from '../scripts/sqlite-adapter.mjs';
import {createHandler} from '../src/index.mjs';
import {issueToken,verifyToken} from '../src/security.mjs';
import {validateIndex,readNote,runAgent} from '../src/agent.mjs';

const origin='https://404nwf3.github.io';
const student={id:'student-1',name:'测试同学',role:'student'};
async function fixture(options={}) {
  const DB=localDatabase();for(const name of readdirSync('drizzle').filter(n=>n.endsWith('.sql'))) DB.sqlite.exec(readFileSync(`drizzle/${name}`,'utf8'));
  const env={DB,TOKEN_SECRET:'test-signing-secret',STUDY_ACCESS_CODE:'test-invite',ADMIN_ACCESS_CODE:'test-admin',DEEPSEEK_API_KEY:'test-only',...options.env};
  const handler=createHandler({agent:options.agent||(async()=>({answer:'测试回答',sources:[]}))});
  const token=await issueToken(student,env.TOKEN_SECRET),admin=await issueToken({...student,id:'admin-1',role:'admin'},env.TOKEN_SECRET);
  const request=async(path,body,credential=token,requestOrigin=origin)=>{
    const response=await handler(new Request(`https://service.test${path}`,{method:body?'POST':'GET',headers:{Origin:requestOrigin,...(body?{'Content-Type':'application/json'}:{}),...(credential?{Authorization:`Bearer ${credential}`}:{})},...(body?{body:JSON.stringify(body)}:{})}),env,{waitUntil:p=>p.catch(()=>{})});
    return {status:response.status,data:await response.json(),response};
  };
  const create=async()=>request('/api/threads',{id:crypto.randomUUID(),title:'条件概率怎样理解？',body:'请解释条件事件与样本空间。',course:'概率论',publicConsent:true});
  return {DB,env,request,create,token,admin};
}
test('tokens cannot be tampered with or used after expiry',async()=>{
  const token=await issueToken(student,'secret',1000);
  assert.equal((await verifyToken(token,'secret',1001)).role,'student');
  await assert.rejects(verifyToken(token,'different-secret',1001));
  await assert.rejects(verifyToken(token,'secret',1000+8*86400000));
  const changed=Buffer.from(JSON.stringify({...student,role:'admin',exp:Date.now()+10000})).toString('base64url')+'.'+token.split('.')[1];
  await assert.rejects(verifyToken(changed,'secret'));
});
test('public readers can read persisted discussions but cannot post or trigger AI',async()=>{
  const f=await fixture(),created=await f.create(),id=created.data.thread.id;
  assert.equal(created.status,201);
  assert.equal((await f.request(`/api/threads/${id}`,null,null)).data.thread.title,'条件概率怎样理解？');
  assert.equal((await f.request('/api/threads',{id:crypto.randomUUID(),title:'test',body:'test',publicConsent:true},null)).status,401);
  assert.equal((await f.request(`/api/threads/${id}/answer`,{},null)).status,401);
  assert.equal((await f.request(`/api/threads/${id}/answer`,{},f.token,'https://evil.test')).status,403);
  assert.equal((await f.request(`/api/threads/${id}`,null,null)).data.thread.authorId,undefined);
});
test('public consent, limits, source identity and duplicate requests are enforced',async()=>{
  const f=await fixture(),id=crypto.randomUUID(),body={id,title:'公开测试',body:'正文',publicConsent:true};
  assert.equal((await f.request('/api/threads',{...body,publicConsent:false})).status,400);
  assert.equal((await f.request('/api/threads',{...body,body:'a'.repeat(4001)})).status,400);
  assert.equal((await f.request('/api/threads',body)).status,201);
  assert.equal((await f.request('/api/threads',body)).status,200);
  const replyId=crypto.randomUUID();
  const result=await f.request(`/api/threads/${id}/replies`,{id:replyId,body:'同学补充',publicConsent:true,kind:'assistant',author_name:'DeepSeek'});
  assert.equal(result.data.reply.kind,'student');assert.equal(result.data.reply.author,'测试同学');
  await f.request(`/api/threads/${id}/replies`,{id:replyId,body:'重复提交',publicConsent:true});
  assert.equal((await f.request(`/api/threads/${id}`)).data.replies.length,1);
});
test('search handles wildcard input literally and cannot inject SQL',async()=>{
  const f=await fixture();await f.create();
  assert.equal((await f.request('/api/threads?q='+encodeURIComponent("%' OR 1=1 --"))).data.threads.length,0);
  assert.equal((await f.request('/api/threads?q='+encodeURIComponent('条件'))).data.threads.length,1);
});
test('students cannot hide discussions; administrator hiding removes public access',async()=>{
  const f=await fixture(),id=(await f.create()).data.thread.id;
  assert.equal((await f.request(`/api/threads/${id}/moderate`,{})).status,403);
  assert.equal((await f.request(`/api/threads/${id}/moderate`,{},f.admin)).status,200);
  assert.equal((await f.request(`/api/threads/${id}`,null,null)).status,404);
});
test('concurrent AI requests take one lock and call the model once',async()=>{
  let release,started;const gate=new Promise(resolve=>{release=resolve;}),ready=new Promise(resolve=>{started=resolve;});let calls=0;
  const f=await fixture({agent:async()=>{calls++;started();await gate;return {answer:'已回答',sources:[]};}}),id=(await f.create()).data.thread.id;
  const first=f.request(`/api/threads/${id}/answer`,{});await ready;
  assert.equal((await f.request(`/api/threads/${id}/answer`,{})).status,409);
  release();assert.equal((await first).status,200);assert.equal(calls,1);
  assert.equal((await f.request(`/api/threads/${id}`)).data.replies.length,1);
});
test('global daily budget stops API spending and failures preserve public questions',async()=>{
  let calls=0;const f=await fixture({env:{DAILY_AI_LIMIT:'1'},agent:async()=>{calls++;throw new Error('upstream unavailable secret-key');}});
  const first=(await f.create()).data.thread.id,second=(await f.create()).data.thread.id;
  const failed=await f.request(`/api/threads/${first}/answer`,{});assert.equal(failed.status,502);assert.doesNotMatch(JSON.stringify(failed.data),/secret-key/);
  assert.equal((await f.request(`/api/threads/${second}/answer`,{})).status,429);assert.equal(calls,1);
  const saved=await f.request(`/api/threads/${first}`);assert.equal(saved.data.thread.aiStatus,'failed');assert.equal(saved.data.replies.length,0);
});
test('indexes reject path traversal and tools only fetch pinned Markdown paths',async()=>{
  const revision='a'.repeat(40),valid={id:'b'.repeat(12),path:'概率论/笔记.md',title:'条件概率',course:'概率论'};
  const index=validateIndex({revision,notes:[valid,{...valid,path:'../.env'},{...valid,path:'http://evil.test/x.md'},{...valid,path:'概率论/../secret.md'}]});
  assert.equal(index.notes.length,1);
  const requests=[];const result=await readNote(index,valid.id,'',async url=>{requests.push(url);return new Response('# 条件概率\n原文');});
  assert.equal(requests.length,1);assert.ok(requests[0].startsWith('https://raw.githubusercontent.com/404NWF3/SUFE_DS/'+revision+'/'));
  assert.match(result.source.url,/404nwf3.github.io\/SUFE_DS\/notes\//);
  assert.ok((await readNote(index,'not-a-note','',()=>{throw new Error('must not fetch');})).error);
});
test('DeepSeek tool loop searches then reads a source and returns grounded references',async()=>{
  const id='a'.repeat(12),revision='b'.repeat(40),modelRequests=[];
  const fakeFetch=async(url,options)=>{
    assert.equal(options.redirect,'manual','Worker fetch must not use unsupported error redirects or forward credentials');
    if(url.endsWith('notes-index.json'))return Response.json({revision,notes:[{id,path:'概率论/条件概率.md',title:'条件概率',course:'概率论',summary:'条件事件'}]});
    if(url.startsWith('https://raw.githubusercontent.com/'))return new Response('# 条件概率\nP(A|B)=P(A∩B)/P(B)，其中 P(B)>0。');
    assert.equal(url,'https://api.deepseek.com/chat/completions');const body=JSON.parse(options.body);modelRequests.push(body);
    const n=modelRequests.length;
    return Response.json({choices:[{message:n===1?{role:'assistant',content:null,tool_calls:[{id:'t1',type:'function',function:{name:'search_notes',arguments:'{"query":"条件概率"}'}}]}:n===2?{role:'assistant',content:null,tool_calls:[{id:'t2',type:'function',function:{name:'read_note',arguments:JSON.stringify({note_id:id})}}]}:{role:'assistant',content:'需要 P(B)>0。[1]'}}]});
  };
  const result=await runAgent({thread:{title:'条件概率',body:'怎么理解？'},replies:[],env:{DEEPSEEK_API_KEY:'test'},fetcher:fakeFetch});
  assert.equal(result.sources.length,1);assert.equal(result.sources[0].id,id);assert.match(result.answer,/\[1\]/);
  assert.equal(modelRequests[2].tools,undefined);assert.equal(modelRequests[2].messages.at(-1).role,'tool');
});
