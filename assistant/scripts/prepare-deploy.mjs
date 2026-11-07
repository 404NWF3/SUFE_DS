import {cp, mkdir, rm, access} from 'node:fs/promises';
import path from 'node:path';
import {fileURLToPath} from 'node:url';
const source=path.resolve(path.dirname(fileURLToPath(import.meta.url)),'..');
const target=path.resolve(source,'../.local/assistant-deploy');
await mkdir(target,{recursive:true});
for(const name of ['src','db','drizzle','scripts','test','.openai','dist']) {
  await access(path.join(source,name));
  await rm(path.join(target,name),{recursive:true,force:true});
  await cp(path.join(source,name),path.join(target,name),{recursive:true});
}
for(const name of ['package.json','package-lock.json','.gitignore','README.md','drizzle.config.ts','.env.example'])
  await cp(path.join(source,name),path.join(target,name));
console.log(target);
