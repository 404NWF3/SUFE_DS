export const repository = "404NWF3/SUFE_DS";
export const base = "/SUFE_DS/";
export const siteUrl = "https://404nwf3.github.io";
export const groups = [
  { id: "math", title: "数学与统计", symbol: "∑", color: "sage" },
  { id: "computer", title: "计算机与数据科学", symbol: "{ }", color: "blue" },
  { id: "economy", title: "经济与管理", symbol: "↗", color: "sand" },
  { id: "general", title: "通识与人文", symbol: "文", color: "rose" },
  { id: "exam", title: "考试与拓展", symbol: "✳", color: "lilac" },
  { id: "other", title: "其他课程", symbol: "＋", color: "sage" },
];
export const nonCourseFolders = new Set(["assets", "assistant", "docs", "site"]);
// Course folders are the content source. No materials are copied into this directory.
export const courseDefinitions = [
  [
    "数理统计",
    "statistics",
    "math",
    "从参数估计到假设检验，串起统计推断的思路。",
  ],
  ["概率论", "probability", "math", "随机变量、分布与极限定理，从这里开始。"],
  ["随机过程", "stochastic-processes", "math", "马尔可夫链、泊松过程与随机系统的演化。"],
  ["高维数据分析", "high-dimensional-data", "math", "回归、降维与高维统计方法，连接理论与数据实践。"],
  ["高等数学上", "calculus-1", "math", "极限、导数与积分，打好数学分析基础。"],
  ["高等数学下", "calculus-2", "math", "多元微积分、级数与空间中的数学。"],
  ["线性代数", "linear-algebra", "math", "用向量、矩阵与线性空间理解问题。"],
  ["优化理论与算法", "optimization", "math", "理解优化模型，掌握求解方法。"],
  ["离散数学", "discrete-math", "math", "逻辑、集合与离散结构。"],
  ["机器学习数学基础", "ml-math", "math", "连接数学工具与机器学习的直觉。"],
  [
    "算法设计与分析",
    "algorithms",
    "computer",
    "从贪心到动态规划，理解算法背后的选择。",
  ],
  [
    "数据结构",
    "data-structures",
    "computer",
    "组织数据，也组织解决问题的思路。",
  ],
  [
    "程序设计基础",
    "programming",
    "computer",
    "从第一行代码，到完整的问题求解。",
  ],
  [
    "高级程序设计",
    "advanced-programming",
    "computer",
    "程序设计练习、课程笔记与实践资料。",
  ],
  ["数据库", "databases", "computer", "从数据建模到查询与管理。"],
  [
    "计算机组成原理",
    "computer-architecture",
    "computer",
    "理解程序运行背后的计算机系统。",
  ],
  ["开源技术基础", "open-source", "computer", "开源工具、Python 与数据实践。"],
  [
    "微观经济学",
    "microeconomics",
    "economy",
    "从个体决策出发，理解市场如何运行。",
  ],
  [
    "中级微观经济学",
    "intermediate-micro",
    "economy",
    "进一步理解经济行为与市场分析。",
  ],
  ["宏观经济学", "macroeconomics", "economy", "从国民收入到货币政策，理解经济的整体运行。"],
  ["金融科技导论", "fintech", "economy", "金融科技案例、课程汇报与实践资料。"],
  ["决策仿真", "decision-simulation", "economy", "离散事件仿真项目与 Simio 建模工具。"],
  [
    "经济管理中的计算机应用",
    "business-computing",
    "economy",
    "计算机工具与经济管理实践。",
  ],
  ["经济文献", "economics-readings", "economy", "延伸阅读，积累经济学视角。"],
  ["思想道德与法治", "ethics-law", "general", "课程资料、知识整理与复习参考。"],
  ["近现代史纲要", "modern-history", "general", "历史脉络与课程学习资料。"],
  ["中华人民共和国史", "prc-history", "general", "课程教材与学习参考。"],
  ["马克思主义基本原理", "marxism", "general", "理论学习与课程资料。"],
  ["形势与政策", "policy", "general", "课程学习与相关材料。"],
  [
    "大学生心理健康与发展",
    "psychology",
    "general",
    "关于心理健康、成长与大学生活。",
  ],
  ["卫生保健", "health", "general", "课程笔记与学习参考。"],
  ["西方哲学智慧", "philosophy", "general", "从哲学问题出发，拓展思考。"],
  ["语言科学", "linguistics", "general", "语言、认知与课程探索。"],
  ["四级", "cet-4", "exam", "真题、听力与英语四级备考资料。"],
  ["六级", "cet-6", "exam", "真题、听力与英语六级备考资料。"],
  [
    "全国大学生数学竞赛-非数学类",
    "math-competition",
    "exam",
    "竞赛试题与数学练习。",
  ],
  ["叉班面试", "interviews", "exam", "面试经验与学习参考。"],
  ["for fun", "explorations", "exam", "课堂之外，保留一点探索的乐趣。"],
];
export const featuredPaths = [
  "数理统计/笔记/数理统计期末总结.md",
  "算法设计与分析/笔记/06 Dynamic Programming.md",
  "优化理论与算法/note/单纯形表的矩阵计算与卡西欧991计算器操作.md",
];
export const featuredCourses = [
  "stochastic-processes",
  "high-dimensional-data",
  "macroeconomics",
  "statistics",
  "algorithms",
  "fintech",
];
