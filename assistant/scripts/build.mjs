import { build } from 'esbuild';
import { mkdir, rm, copyFile } from 'node:fs/promises';
await rm('dist',{recursive:true,force:true});
await mkdir('dist/server',{recursive:true});
await mkdir('dist/.openai',{recursive:true});
await build({entryPoints:['src/index.mjs'],outfile:'dist/server/index.js',bundle:true,format:'esm',platform:'browser',target:'es2022',minify:false});
await copyFile('.openai/hosting.json','dist/.openai/hosting.json');
console.log('Built standalone Worker with D1 binding; no source materials or secrets included.');
