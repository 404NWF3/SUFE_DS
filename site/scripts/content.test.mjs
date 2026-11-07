import test from "node:test";
import assert from "node:assert/strict";
import {
  normalizeMath,
  renderMarkdown,
  createResolver,
  encodePath,
  resourceId,
} from "./content.mjs";
const files = [
  "课程/当前.md",
  "课程/下一篇 #1.md",
  "课程/图 1.png",
  "课程/课件.pdf",
  "课程/重复.md",
  "另一课程/重复.md",
];
const resources = files
  .filter((f) => f.endsWith(".md"))
  .map((p) => ({ path: p, id: resourceId(p), format: "md" }));
const resolver = createResolver({
  files,
  resources,
  repo: "example/repo",
  ref: "a".repeat(40),
  base: "/SUFE_DS/",
});

test("math delimiter conversion preserves TeX row spacing and fenced code", async () => {
  const source = String.raw`$$\begin{aligned}a&=1\\[2pt]b&=2\end{aligned}$$`;
  assert.ok(normalizeMath(source).includes(String.raw`a&=1\\[2pt]b&=2`));
  const result = await renderMarkdown(source, "课程/当前.md", resolver);
  assert.equal(result.warnings.filter((w) => w.kind === "math").length, 0);
  assert.match(result.html, /class="katex"/);
  assert.equal(normalizeMath("```tex\n\\[x\\]\n```"), "```tex\n\\[x\\]\n```");
  assert.equal(normalizeMath(String.raw`\(x^2\)`), "$x^2$");
});

test("Obsidian-style display delimiters cannot swallow subsequent prose", async () => {
  const source = "$$\nx=1.$$\n\n下一段 $y$。\n\n> $$\n x=2\n $$\n\n后文。";
  const result = await renderMarkdown(source, "课程/当前.md", resolver);
  assert.equal(result.warnings.filter((w) => w.kind === "math").length, 0);
  assert.match(result.html, /<p>下一段 /);
  assert.match(result.html, /<p>后文。<\/p>/);
});

test("Chinese paths, encoded hash and aliases resolve to static pages", async () => {
  const result = await renderMarkdown(
    "[[下一篇 #1.md|继续学习]]\n\n[课件](课件.pdf)\n\n![配图](图%201.png)",
    "课程/当前.md",
    resolver,
  );
  assert.match(result.html, /继续学习/);
  assert.match(result.html, /\/SUFE_DS\/notes\//);
  assert.match(result.html, /github.com\/example\/repo\/raw\//);
  assert.match(result.html, /raw.githubusercontent.com/);
  assert.equal(resolver.resolve("重复", "课程/当前.md"), "课程/重复.md");
  assert.equal(resolver.resolve("重复", "第三课程/不存在.md"), null);
  assert.equal(
    encodePath("目录/50% #?.pdf"),
    "%E7%9B%AE%E5%BD%95/50%25%20%23%3F.pdf",
  );
});

test("Markdown does not execute embedded HTML or unsafe link schemes", async () => {
  const result = await renderMarkdown(
    "<script>alert(1)</script>\n\n[x](javascript:alert%281%29)\n\n<img src=x onerror=alert(1)>",
    "课程/当前.md",
    resolver,
  );
  assert.doesNotMatch(result.html, /<script|onerror|href="javascript:/);
});

test("missing wiki images have a readable fallback and headings have unique anchors", async () => {
  const result = await renderMarkdown(
    "# 概率\n\n![[没有的图.png]]\n\n## 概率\n\n> [!NOTE]\n> 说明",
    "课程/当前.md",
    resolver,
  );
  assert.match(result.html, /原笔记图片未收录/);
  assert.match(result.html, /class="callout callout-note"/);
  assert.equal(new Set(result.toc.map((h) => h.id)).size, 2);
  assert.equal(
    result.warnings.filter((w) => w.kind === "missing-wikilink").length,
    1,
  );
});
