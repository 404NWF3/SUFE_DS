import http from 'node:http';
import { Readable } from 'node:stream';
import { readFile, readdir, mkdir } from 'node:fs/promises';
import { localDatabase } from './sqlite-adapter.mjs';
import { createHandler } from '../src/index.mjs';
await mkdir('.local',{recursive:true});
const db=localDatabase('.local/qa.sqlite');
db.sqlite.exec('CREATE TABLE IF NOT EXISTS local_migrations(name TEXT PRIMARY KEY)');
for(const name of (await readdir('drizzle')).filter(n=>n.endsWith('.sql')).sort()) {
  if(!db.sqlite.prepare('SELECT name FROM local_migrations WHERE name=?').get(name)) {
    db.sqlite.exec(await readFile(`drizzle/${name}`,'utf8')); db.sqlite.prepare('INSERT INTO local_migrations VALUES (?)').run(name);
  }
}
const mock=process.env.MOCK_AI==='1';
const env={...process.env,DB:db,ALLOWED_ORIGINS:'http://127.0.0.1:4173,http://localhost:4173',TOKEN_SECRET:process.env.TOKEN_SECRET||'local-preview-session-secret',STUDY_ACCESS_CODE:process.env.STUDY_ACCESS_CODE||'sufe-demo',ADMIN_ACCESS_CODE:process.env.ADMIN_ACCESS_CODE||'sufe-admin-demo',...(mock?{DEEPSEEK_API_KEY:'local-mock-only'}:{})};
const handler=createHandler(mock?{demo:true,agent:async()=>({answer:'**本地演示回答：未调用 DeepSeek。**\n\n这里会显示助教结合笔记的解释，例如：\n\n$$P(A\\mid B)=\\frac{P(A\\cap B)}{P(B)}$$\n\n1. 先明确条件和定义。\n2. 再对照原笔记进行推导。\n\n同学们可以在下方继续补充。',sources:[]})}:{});
http.createServer(async(req,res)=>{
  try {
    const request=new Request(`http://127.0.0.1:8787${req.url}`,{method:req.method,headers:req.headers,...(!['GET','HEAD'].includes(req.method)?{body:Readable.toWeb(req),duplex:'half'}:{})});
    const response=await handler(request,env,{waitUntil:promise=>promise.catch(()=>{})});
    res.writeHead(response.status,Object.fromEntries(response.headers));res.end(Buffer.from(await response.arrayBuffer()));
  }catch {res.writeHead(500);res.end('Local development error');}
}).listen(8787,'127.0.0.1',()=>console.log(`Assistant API: http://127.0.0.1:8787 (${mock?'MOCK AI — no DeepSeek calls':'live API if configured'})`));
