import { readFile, readdir, stat } from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { gzipSync } from "node:zlib";
import { parse } from "parse5";
import { base } from "../src/config.mjs";
const site = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const dist = path.join(site, "dist");
const allFiles = [];
async function walk(dir) {
  for (const item of await readdir(dir, { withFileTypes: true })) {
    const file = path.join(dir, item.name);
    if (item.isDirectory()) await walk(file);
    else allFiles.push(file);
  }
}
await walk(dist);
const paths = new Set(allFiles);
const errors = [];
let links = 0,
  totalSize = 0,
  pageCount = 0;
for (const file of allFiles) {
  totalSize += (await stat(file)).size;
  if (/\.(md|pdf|docx?|pptx?|xlsx?|mp3|m4a|zip|ipynb)$/i.test(file))
    errors.push(`Source material copied into site: ${file}`);
  if (!file.endsWith(".html")) continue;
  pageCount++;
  const html = await readFile(file, "utf8");
  const tree = parse(html);
  const ids = new Set();
  function visit(node) {
    const attrs = Object.fromEntries(
      (node.attrs || []).map((a) => [a.name, a.value]),
    );
    if (attrs.id) {
      if (ids.has(attrs.id))
        errors.push(`Duplicate ID ${attrs.id} in ${path.relative(dist, file)}`);
      ids.add(attrs.id);
    }
    if (["iframe", "object", "embed", "audio", "video"].includes(node.tagName))
      errors.push(`Unexpected file preview element ${node.tagName} in ${file}`);
    for (const name of ["href", "src"]) {
      const url = attrs[name];
      if (!url?.startsWith(base)) continue;
      const pathname = decodeURIComponent(
        url.split(/[?#]/)[0].slice(base.length),
      );
      const target = path.resolve(
        dist,
        pathname + (pathname.endsWith("/") || !pathname ? "index.html" : ""),
      );
      links++;
      if (!paths.has(target))
        errors.push(
          `Missing internal target: ${url} from ${path.relative(dist, file)}`,
        );
    }
    for (const child of node.childNodes || []) visit(child);
  }
  visit(tree);
}
if (totalSize > 100 * 1024 * 1024)
  errors.push("Static output exceeds 100 MiB budget");
const manifest = JSON.parse(
  await readFile(path.join(site, ".cache/manifest.json"), "utf8"),
);
for (const entry of manifest) {
  if (
    entry.format === "md" &&
    !paths.has(path.join(dist, "notes", entry.id, "index.html"))
  )
    errors.push(`Missing Markdown page: ${entry.path}`);
  if (!entry.download.startsWith("https://github.com/404NWF3/SUFE_DS/raw/"))
    errors.push(`Invalid download host: ${entry.path}`);
}
let firstLoad = 0;
for (const file of [
  "index.html",
  "assets/style.css",
  "assets/app.js",
  "assets/favicon.svg",
])
  firstLoad += gzipSync(await readFile(path.join(dist, file))).length;
if (firstLoad > 150 * 1024)
  errors.push("Homepage initial assets exceed 150 KiB gzip");
if (errors.length) {
  console.error(errors.join("\n"));
  process.exitCode = 1;
} else
  console.log(
    `Checked ${pageCount} HTML pages and ${links} internal links. Output ${(totalSize / 1048576).toFixed(2)} MiB; homepage ${Math.round(firstLoad / 1024)} KiB gzip. No source materials copied.`,
  );
