import { HttpError, textField, uuid, readJson, digest, sameSecret, issueToken, verifyToken, boundedSetting } from './security.mjs';
import { runAgent } from './agent.mjs';

const FRONTEND = 'https://404nwf3.github.io';
const publicThread = row => row && ({id:row.id,title:row.title,course:row.course,noteId:row.note_id,body:row.body,author:row.author_name,createdAt:row.created_at,updatedAt:row.updated_at,aiStatus:row.ai_status==='running' && row.ai_started<Date.now()-120000?'failed':row.ai_status,aiError:row.ai_status==='running' && row.ai_started<Date.now()-120000?'上次回答中断，可以重新邀请 AI。':row.ai_error,replies:row.reply_count||0});
const publicReply = row => ({id:row.id,author:row.author_name,kind:row.kind,body:row.body,sources:JSON.parse(row.sources||'[]'),createdAt:row.created_at});
const one = (db,sql,...args) => db.prepare(sql).bind(...args).first();
const run = (db,sql,...args) => db.prepare(sql).bind(...args).run();
async function budget(db,bucket,limit,expiresAt) {
  const row = await one(db,`INSERT INTO budgets (bucket,used,expires_at) VALUES (?,1,?) ON CONFLICT(bucket) DO UPDATE SET used=used+1 WHERE used < ? RETURNING used`,bucket,expiresAt,limit);
  if (!row) throw new HttpError(429,'本时段的使用次数已用完，请稍后再试。');
}
async function actor(request,env) {
  const authorization=request.headers.get('Authorization')||'';
  if (!authorization.startsWith('Bearer ')) throw new HttpError(401,'请先输入昵称和学习区邀请码。');
  return verifyToken(authorization.slice(7),env.TOKEN_SECRET);
}
async function getThread(db,id) {
  const thread=await one(db,'SELECT * FROM threads WHERE id=? AND hidden=0',uuid(id));
  if(!thread) throw new HttpError(404,'这个讨论不存在或已被隐藏。');
  return thread;
}
export function createHandler({agent=runAgent,demo=false}={}) {
  return async function handle(request,env,ctx={waitUntil:()=>{}}) {
    const origin=request.headers.get('Origin');
    const allowed=new Set([FRONTEND,...(env.ALLOWED_ORIGINS||'').split(',').filter(Boolean)]);
    const headers={'Content-Type':'application/json; charset=utf-8','Cache-Control':'no-store','X-Content-Type-Options':'nosniff',Vary:'Origin'};
    if(origin && allowed.has(origin)) headers['Access-Control-Allow-Origin']=origin;
    const json=(data,status=200)=>new Response(JSON.stringify(data),{status,headers});
    try {
      if(origin && !allowed.has(origin)) throw new HttpError(403,'请从资料网站访问问答区。');
      if(request.method==='OPTIONS') return new Response(null,{status:204,headers:{...headers,'Access-Control-Allow-Methods':'GET, POST, OPTIONS','Access-Control-Allow-Headers':'Content-Type, Authorization','Access-Control-Max-Age':'600'}});
      const url=new URL(request.url), path=url.pathname;
      if(path==='/') return Response.redirect('https://404nwf3.github.io/SUFE_DS/ask/',302);
      if(!env.DB) throw new HttpError(503,'问答区正在准备，请稍后回来。');
      if(path==='/api/health' && request.method==='GET') {
        await one(env.DB,'SELECT id FROM threads LIMIT 1');
        return json({ready:!!(env.TOKEN_SECRET&&env.STUDY_ACCESS_CODE),aiReady:!!env.DEEPSEEK_API_KEY,demo,public:true});
      }
      if(path==='/api/session' && request.method==='POST') {
        if(!env.TOKEN_SECRET || !env.STUDY_ACCESS_CODE) throw new HttpError(503,'发言功能暂未配置。');
        const fingerprint=await digest(`${env.TOKEN_SECRET}:${request.headers.get('CF-Connecting-IP')||'unknown'}`);
        const hour=Math.floor(Date.now()/3600000);
        await budget(env.DB,`login:${hour}:${fingerprint}`,40,(hour+2)*3600000);
        const data=await readJson(request);
        const name=textField(data.name,'昵称',24),code=textField(data.code,'邀请码',200);
        const admin=await sameSecret(code,env.ADMIN_ACCESS_CODE);
        if(!admin && !await sameSecret(code,env.STUDY_ACCESS_CODE)) throw new HttpError(401,'邀请码不正确，请联系维护者获取。');
        if(!admin && /管理员|助教|deepseek|admin|官方/i.test(name)) throw new HttpError(400,'请使用不会与维护者或 AI 混淆的昵称。');
        const user={id:crypto.randomUUID(),name,role:admin?'admin':'student'};
        const token=await issueToken(user,env.TOKEN_SECRET);
        return json({token,user:{name,role:user.role}});
      }
      if(path==='/api/threads' && request.method==='GET') {
        const q=(url.searchParams.get('q')||'').slice(0,100);
        const course=(url.searchParams.get('course')||'').slice(0,100);
        const page=Math.max(0,Math.min(1000,parseInt(url.searchParams.get('page'),10)||0));
        const pattern=`%${q.replace(/[\\%_]/g,'\\$&')}%`;
        const rows=await env.DB.prepare(`SELECT t.*, (SELECT count(*) FROM replies r WHERE r.thread_id=t.id AND r.hidden=0) AS reply_count FROM threads t WHERE t.hidden=0 AND (?='' OR t.course=?) AND (?='' OR t.title LIKE ? ESCAPE '\\' OR t.body LIKE ? ESCAPE '\\') ORDER BY t.updated_at DESC,t.id LIMIT 21 OFFSET ?`).bind(course,course,q,pattern,pattern,page*20).all();
        return json({threads:rows.results.slice(0,20).map(publicThread),hasMore:rows.results.length>20,page});
      }
      const match=path.match(/^\/api\/threads\/([^/]+)(?:\/(answer|replies|moderate))?$/);
      if(match && request.method==='GET' && !match[2]) {
        const thread=await getThread(env.DB,match[1]);
        const rows=await env.DB.prepare('SELECT * FROM replies WHERE thread_id=? AND hidden=0 ORDER BY created_at,id LIMIT 200').bind(thread.id).all();
        return json({thread:publicThread(thread),replies:rows.results.map(publicReply)});
      }
      if(request.method!=='POST') throw new HttpError(404,'未找到这个接口。');
      const user=await actor(request,env);
      const data=await readJson(request);
      const now=Date.now(),minute=Math.floor(now/60000);
      await budget(env.DB,`write:${minute}:${user.id}`,12,(minute+2)*60000);
      if(path==='/api/threads') {
        const id=uuid(data.id),title=textField(data.title,'标题',100),body=textField(data.body,'问题',4000);
        const course=textField(data.course||'','课程',80,0),noteId=textField(data.noteId||'','笔记编号',12,0);
        if(noteId && !/^[a-f0-9]{12}$/.test(noteId)) throw new HttpError(400,'笔记编号不正确。');
        if(data.publicConsent!==true) throw new HttpError(400,'请确认问题和回复会公开。');
        const existing=await one(env.DB,'SELECT * FROM threads WHERE id=?',id);
        if(existing) { if(existing.author_id!==user.id || existing.hidden) throw new HttpError(409,'请求编号已经使用。'); return json({thread:publicThread(existing)}); }
        await run(env.DB,'INSERT INTO threads (id,title,course,note_id,body,author_id,author_name,created_at,updated_at) VALUES (?,?,?,?,?,?,?,?,?)',id,title,course,noteId,body,user.id,user.name,now,now);
        return json({thread:publicThread(await getThread(env.DB,id))},201);
      }
      if(!match) throw new HttpError(404,'未找到这个接口。');
      const thread=await getThread(env.DB,match[1]);
      if(match[2]==='moderate') {
        if(user.role!=='admin') throw new HttpError(403,'只有维护者可以隐藏内容。');
        if(data.replyId) await run(env.DB,'UPDATE replies SET hidden=1 WHERE id=? AND thread_id=?',uuid(data.replyId),thread.id);
        else await run(env.DB,'UPDATE threads SET hidden=1 WHERE id=?',thread.id);
        return json({ok:true});
      }
      if(match[2]==='replies') {
        const id=uuid(data.id),body=textField(data.body,'回复',4000);
        if(data.publicConsent!==true) throw new HttpError(400,'请确认回复会公开。');
        const existing=await one(env.DB,'SELECT * FROM replies WHERE id=?',id);
        if(existing) { if(existing.thread_id!==thread.id || existing.author_id!==user.id || existing.hidden) throw new HttpError(409,'请求编号已经使用。'); return json({reply:publicReply(existing)}); }
        const count=await one(env.DB,'SELECT count(*) AS total FROM replies WHERE thread_id=? AND hidden=0',thread.id);
        if(count.total>=200) throw new HttpError(409,'这个讨论已达到回复上限，请新建相关问题。');
        await env.DB.batch([
          env.DB.prepare('INSERT INTO replies (id,thread_id,author_id,author_name,kind,body,created_at) VALUES (?,?,?,?,?,?,?)').bind(id,thread.id,user.id,user.name,'student',body,now),
          env.DB.prepare('UPDATE threads SET updated_at=? WHERE id=?').bind(now,thread.id),
        ]);
        return json({reply:publicReply(await one(env.DB,'SELECT * FROM replies WHERE id=?',id))},201);
      }
      if(match[2]==='answer') {
        if(!env.DEEPSEEK_API_KEY) throw new HttpError(503,'AI 服务尚未接通，同学们可以先补充讨论。');
        const locked=await one(env.DB,"UPDATE threads SET ai_status='running',ai_started=?,ai_error='' WHERE id=? AND hidden=0 AND (ai_status<>'running' OR ai_started<?) RETURNING id",now,thread.id,now-120000);
        if(!locked) throw new HttpError(409,'AI 正在回答这个问题，请稍等。');
        try {
          const day=Math.floor((now+8*3600000)/86400000),end=(day+1)*86400000-8*3600000;
          await budget(env.DB,`ai-user:${day}:${user.id}`,boundedSetting(env.USER_DAILY_LIMIT,20,100),end+86400000);
          await budget(env.DB,`ai-global:${day}`,boundedSetting(env.DAILY_AI_LIMIT,100,10000),end+86400000);
          const rows=await env.DB.prepare('SELECT * FROM replies WHERE thread_id=? AND hidden=0 ORDER BY created_at DESC,id LIMIT 10').bind(thread.id).all();
          const result=await agent({thread,replies:rows.results.reverse(),env,signal:AbortSignal.timeout(90000)});
          const id=crypto.randomUUID(),finished=Date.now();
          await env.DB.batch([
            env.DB.prepare("INSERT INTO replies (id,thread_id,author_id,author_name,kind,body,sources,created_at) SELECT ?,id,'assistant','DeepSeek 学习助教','assistant',?,?,? FROM threads WHERE id=? AND ai_started=? AND ai_status='running'").bind(id,result.answer,JSON.stringify(result.sources),finished,thread.id,now),
            env.DB.prepare("UPDATE threads SET ai_status='answered',ai_error='',updated_at=? WHERE id=? AND ai_started=?").bind(finished,thread.id,now),
          ]);
          return json({ok:true});
        } catch(error) {
          const message=error instanceof HttpError?error.message:'AI 回答未完成，问题已保留，可以稍后重试。';
          await run(env.DB,"UPDATE threads SET ai_status='failed',ai_error=? WHERE id=? AND ai_started=?",message,thread.id,now);
          if(error instanceof HttpError) throw error;
          throw new HttpError(502,message);
        } finally {
          ctx.waitUntil(run(env.DB,'DELETE FROM budgets WHERE expires_at<?',Date.now()).catch(()=>{}));
        }
      }
      throw new HttpError(404,'未找到这个接口。');
    } catch(error) {
      return json({error:error instanceof HttpError?error.message:'服务暂时不可用，请稍后重试。'},error instanceof HttpError?error.status:500);
    }
  };
}
export default {fetch:createHandler()};
