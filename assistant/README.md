# SUFE DS 公开学习问答服务

前端位于 `site/`，继续使用 GitHub Pages；本目录是独立托管的 Worker 服务，D1 保存公开讨论。后端源代码只包含程序和数据库迁移，不包含课程原始资料。

## 已实现

- 公开问题列表、关键词及课程筛选、分享链接。
- 邀请码与昵称发言；短期签名凭证有效 7 天，管理员使用不同的管理码。
- 同学回复、AI 回答与实际查阅的资料来源保存在同一个讨论串。
- DeepSeek 工具调用：搜索本站笔记索引、读取固定 Git 提交上的 Markdown 原文。最多 3 次模型请求、4 次资料工具调用，每次输出最多 2200 tokens；不运行代码、不读非 Markdown 附件、不访问任意 URL。
- 每个发言凭证每日 20 次 AI 任务，全站每日 100 次，按北京时间重置；D1 原子计数控制全站额度。邀请码和昵称不是实名认证，重新进入可获得新凭证，因此凭证额度不应被理解为严格的个人额度。
- 同一讨论串一次只生成一个 AI 回答。网络或模型失败保留问题，显示失败状态，可主动重试。失败任务也占用当次额度。
- 管理员可隐藏讨论或回复；不对普通访客开放物理删除接口。

## 本地验证

需要 Node.js 22.13 或更新版本。

```sh
cd assistant
npm ci
npm test
npm run build
MOCK_AI=1 npm run dev
```

本地演示邀请码为 `sufe-demo`，管理码为 `sufe-admin-demo`，只在本地开发脚本中生效。页面明确标注模拟回答。生产 Worker 不包含开发脚本。

另开终端，在仓库根目录执行：

```sh
AI_API_BASE=http://127.0.0.1:8787 npm --prefix site run build
npm --prefix site run preview
```

真实调用时复制 `.env.example` 为被忽略的 `.env.local`，仅在本机填入配置，运行 `npm run dev`；不设置 `MOCK_AI`。

## 托管与配置

服务的 Sites 项目标识保存在 `.openai/hosting.json`。D1 绑定名为 `DB`；托管平台会在发布时创建数据库并应用 `drizzle/` 迁移。环境变量通过 Sites 的加密配置维护，前端只能知道后端公开 URL。

| 配置 | 用途 |
| --- | --- |
| `DEEPSEEK_API_KEY` | DeepSeek 密钥，仅服务端使用 |
| `DEEPSEEK_MODEL` | 模型名，当前默认 `deepseek-flash` |
| `STUDY_ACCESS_CODE` | 发给同学的学习区邀请码 |
| `ADMIN_ACCESS_CODE` | 维护者管理码，不能发给同学 |
| `TOKEN_SECRET` | 签名密钥，随机生成；轮换后现有发言凭证失效 |
| `DAILY_AI_LIMIT` | 全站每日 AI 任务上限，默认 100 |
| `USER_DAILY_LIMIT` | 每个发言凭证每日 AI 任务上限，默认 20 |
| `ALLOWED_ORIGINS` | 可选的额外前端来源；生产默认只允许当前 GitHub Pages 来源 |

邀请码轮换阻止新登录；如需同时撤销现有登录，需要一起轮换 `TOKEN_SECRET`。昵称是用户自选的显示名称，不代表经过验证的学生身份。

更改数据库结构后执行 `npm run db:generate`。已发布迁移不可改写，新增迁移必须提交。部署步骤：

1. `npm test && npm run build`。
2. `node scripts/prepare-deploy.mjs`：将后端程序及产物复制到被忽略的 `.local/assistant-deploy/`，与 GitHub 资料仓库的 Git 历史分离；课程资料和私密配置均不复制。
3. 使用 Sites 技能的 `site-workflow.mjs` 在该目录同步服务源代码并打包，使用已有的同一项目 ID。
4. 保存版本、发布并确认部署成功。密钥或额度配置改变后也需重新部署才能生效。

前端发布继续由 GitHub Actions 完成；后端有单独的部署生命周期。两部分都更新时，先发布后端，再发布前端，最后验证真实问答。

## 数据与维护

`threads` 保存问题及生成状态，`replies` 保存同学和 AI 回答，`budgets` 只保存计数。请求原始 IP 只在服务内用于短期防刷指纹计算，不保存原值。学生发言凭证保存在其浏览器中，不写入公开讨论。

讨论公开可读。维护者进入学习区时使用管理码，讨论与回复旁会出现「隐藏」操作。隐藏保留数据库记录，普通读接口不会返回隐藏内容。

没有内置通用联网搜索、文件上传、考试成绩判断、私人聊天或后台自动发言。API 费用取决于 DeepSeek 的实际计费；次数及 tokens 上限控制用量，不等同于精确人民币预算。

接口依据：[DeepSeek API](https://api-docs.deepseek.com/api/create-chat-completion/)、[Tool Calls](https://api-docs.deepseek.com/guides/tool_calls/)、[D1](https://developers.cloudflare.com/d1/worker-api/d1-database/)。
