本仓库旨在通过 Git 和 GitHub 管理一个 Obsidian 知识库，实现以下目标：
* **多设备同步**：在你的电脑、笔记本等多个设备间无缝同步笔记。
* **版本控制**：为你的每一份笔记提供完整的修改历史，随时可以恢复到任何一个版本。
* **协作与分享**：允许他人查看你的部分公开笔记，并通过规范的流程贡献内容。

## 目录

- [环境准备](#-环境准备)
- [角色一：仓库拥有者的操作指南](#-角色一仓库拥有者的操作指南)
  - [首次配置 (Set Up)](#首次配置-set-up)
  - [日常使用 (Daily Workflow)](#日常使用-daily-workflow)
- [角色二：协作者的操作指南 (非拥有者)](#-角色二协作者的操作指南-非拥有者)
  - [核心理念：Fork & Pull Request](#核心理念fork--pull-request)
  - [首次配置](#首次配置)
  - [贡献流程](#贡献流程)
- [附录：常见问题与技巧](#-附录常见问题与技巧)
  - [如何处理合并冲突 (Merge Conflict)](#如何处理合并冲突-merge-conflict)
  - [推荐的 `.gitignore` 配置](#推荐的-gitignore-配置)

---

## 环境准备

在开始之前，请确保你已安装以下工具：

1.  **[Obsidian](https://obsidian.md/)**：知识管理的核心工具。
2.  **[Git](https://git-scm.com/downloads)**：版本控制系统，是实现同步的基础。
3.  **Obsidian Git 插件**：
    * 在 Obsidian 中，进入 `设置` -> `第三方插件` -> `社区插件市场`。
    * 搜索 "Git" 并安装。
    * 安装后，请务必在插件列表中启用它。

---

## 角色一：仓库拥有者的操作指南

> **场景**：这是你自己的个人知识库，你希望在自己的多台设备之间进行同步。

### 首次配置 (Set Up)

#### 1. 在 GitHub 上创建仓库
* 在 GitHub.com 上，创建一个新的 **私有 (Private)** 仓库。
    > **强烈建议设为私有！** 除非你希望所有笔记都公开，否则私有仓库能更好地保护你的个人信息。
* **不要** 勾选 "Add a README file"、".gitignore" 或 "license" 等任何选项，保持仓库为空。

#### 2. 配置 Obsidian Git 插件
* 在 Obsidian 中，进入设置下载 `Git` 插件。
* 按下 `Ctrl + P` (或 `Cmd + P`) 打开命令面板。
* 输入 `Git: Clone an existing remote repo`。
* 接下来依次配置远程仓库的地址以及本地的存储地址(在当前obsidian仓库下新建一个文件夹)

#### 3. 首次提交与推送
* 在完成修改后。
* 按下 `Ctrl + P` (或 `Cmd + P`) 打开命令面板。
* 找到并执行 `Git: Commit all changes`。
* 接着找到并执行 `Git: Push`。

现在，你的所有笔记都已成功上传到 GitHub 仓库了。

### 日常使用 (Daily Workflow)

你的工作流将变得极其简单。

1.  **开始写作前 (拉取更新)**
    * 打开 Obsidian 时，插件会自动拉取（Pull）云端的最新更改。
    * 你也可以随时通过命令面板执行 **`Obsidian Git: Pull`** 来手动同步。

2.  **写作后 (推送备份)**
    * 完成一天的笔记后，通过命令面板执行 **`Obsidian Git: Commit all changes`**。
    * 然后执行 **`Obsidian Git: Push`**。

> **自动化提示**: 如果你希望实现自动化，可以在插件设置中开启 `Vault backup interval`，这样插件会定期自动提交和推送。但请注意，这可能在你不想提交的时候触发。

---

## 角色二：协作者的操作指南(Git fork PR)

> **场景**：你想为他人的公开知识库贡献内容，比如修正一个错字、补充一些笔记。

### 核心理念：Fork & Pull Request

你不能直接修改别人的仓库。标准流程是：先 **Fork** (复制) 一份仓库到你自己的名下，在你的副本上修改，然后发起一个 **Pull Request** (PR) 请求原作者合并你的修改。

### 首次配置

1.  **Fork 仓库**：在原作者的 GitHub 仓库页面，点击右上角的 **"Fork"** 按钮，将其复制到你的账户下。

2.  使用 `Git` 插件，找到并运行 `Git: Clone an existing remote repo`，注意clone你自己fork的仓库，而不是原仓库！

3.  **配置 Git Remote**：为了能同步原作者的更新，你需要添加一个指向原仓库的远程地址，我们通常称之为 `upstream`。

    ```bash
    # 进入仓库文件夹
    cd <repo-name>

    # 添加 upstream 指向原作者的仓库
    # 将 original-owner 替换为原作者的用户名
    git remote add upstream 

    # 验证是否成功
    git remote -v
    # 你应该能看到 origin (指向你的 Fork) 和 upstream (指向原仓库)
    ```

4. 在 `obsidian` 中，使用 `Git` 插件，commit，push到你自己的仓库。
5. 到 `github` 上 Pull Request 你的变化。
6. 等待原作者merge。

最后重申，协作者要依次做：
1. 更新自己fork的仓库
2. pull自己的本地仓库
3. 做修改
4. commit、push到自己的fork仓库
5. PR（Pull Request）
6. 等待原作者merge