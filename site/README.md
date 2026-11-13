# 上财学习资料库网站

一个轻量的静态网站。课程资料继续保存在仓库原目录；构建时读取 Markdown 并生成 HTML，其余文件提供 GitHub 原文件下载链接。图片也引用原仓库，不复制资料进网站目录。

## 本地运行

需要 Node.js 22 或更新版本。从仓库根目录执行：

```sh
npm --prefix site ci
npm --prefix site run dev
```

打开终端打印的 `http://127.0.0.1:4173/SUFE_DS/`。修改代码或内容后重新执行 `npm --prefix site run build` 并刷新浏览器；已运行的预览服务会直接读取新产物。

```sh
npm --prefix site test
npm --prefix site run build
npm --prefix site run check
```

`check` 验证内部链接、笔记页面、页面 ID、产物体积，以及是否误复制了原始资料。构建问题记录在 `site/.cache/build-report.json`，不提交到 Git。

## 内容维护

- **添加资料**：放进已有课程目录并提交 Git，网站会在下一次构建时收录。构建扫描 `git ls-files`，未跟踪文件不发布。
- **添加课程**：在 `src/config.mjs` 的 `courseDefinitions` 中增加文件夹、稳定 URL 标识、学科和简介。
- **设置首页精选**：修改 `featuredPaths` 和 `featuredCourses`；首页书页展示对应首篇精选笔记。
- **修改页面样式**：`src/style.css`；交互在 `src/app.js`；页面模板在 `scripts/build.mjs`。
- **课程说明**：课程根目录非空的 `README.md` 显示在课程页的说明中，不重复计为笔记。只有说明和项目链接的课程默认展开说明；子目录里的 README 作为普通 Markdown 收录。
- **笔记附件**：支持常规 Markdown 图片与 Obsidian 双链图片；缺失附件保留文字提示，不修改原笔记。
- **文件类型**：Markdown 在线阅读。PDF、Office、音频、代码（含 R 脚本）、notebook 等只下载；`.url` 作为原站链接。

页面 ID 由原始文件路径生成，改标题不会改变链接，重命名文件会改变链接。下载链接固定到本次构建提交，原始内容和站点版本保持一致。浏览器可能直接打开某些原始文件，可通过原文件页面保存。

## GitHub Pages

仓库 Pages 来源使用 **GitHub Actions**。`main` 每次更新会运行 `.github/workflows/deploy-pages.yml`：测试 → 构建 → 链接检查 → 发布 `site/dist`。PR 只检查，不发布。

CI 使用稀疏检出，只取得网站代码、Markdown 和 `.url`；其余文件从 Git 索引枚举，下载时仍从原仓库取得。未检出的文件大小不显示，格式和下载不受影响。

站点基础路径为 `/SUFE_DS/`，配置在 `src/config.mjs`。资料浏览不依赖后台或数据库，也不进行在线文件转换。公开问答使用下述独立后端。

## 公开学习问答

`/ask/` 是公开问答入口，笔记页也可携带当前笔记提问。学习资料浏览仍是静态站点；问答由独立的托管服务保存讨论并调用 DeepSeek。前端不持有 API 密钥。服务源码与运维步骤见 [问答服务说明](../assistant/README.md)，产品范围见 [问答规格](../docs/ai-assistant-spec.md)。

构建可用 `AI_API_BASE` 指定后端地址。本地开发使用 `http://127.0.0.1:8787`，生产使用已配置的托管服务地址。`assets/notes-index.json` 仅包含笔记目录、摘要和来源路径，Agent 按需从原 GitHub 仓库读取正文。
