#import "@preview/simple-cheatsheet:0.1.0": cheatsheet, container

// 中文字体回退：Windows 常见 CJK 字体优先
#let cjk-fonts = ("Microsoft YaHei", "Microsoft YaHei UI", "SimSun", "Noto Sans CJK SC", "Source Han Sans SC")

// 数学算子（typst 0.15 默认未内置 argmin/argmax/prox 等）
#let argmin = math.op("argmin", limits: true)
#let argmax = math.op("argmax", limits: true)
#let prox = math.op("prox")
#let sign = math.op("sign")
#let tr = math.op("tr")
#let rank = math.op("rank")

#show: cheatsheet.with(
  info: (
    title: "优化理论与算法 · Cheat Sheet",
    authors: ("SUFEllm-wiki",),
  ),
  headers: (align: left, numbering: false),
  layout: (font-size: 6.2pt, margin: (x: 8pt, y: 14pt), columns: (count: 4, gutter: 5pt)),
)

#set text(font: ("Microsoft YaHei", "Microsoft YaHei UI", "SimSun", "Noto Sans CJK SC", "Source Han Sans SC", "Roboto", "Arial"))
#set math.equation(numbering: none)
#show heading.where(level: 2): it => text(weight: "bold", size: 6.6pt, fill: black, it.body)

// ============ 0. 建模与 LP 标准型 ============
= 建模 & LP 标准型

#container[
  == 优化三要素
  - 三要素：决策变量 $x$、目标 $f(x)$、可行域 $Omega$（约束）。
  - 一般形式：$min_x f(x)$ s.t. $g_i(x)<=0, h_j(x)=0$。
  - 难度：$"LP" < "凸优化" < "非凸/整数"$；尽量建成易解模型。

  == LP 标准型
  $min c^T x$ s.t. $A x = b, x >= 0,quad A in RR^(m times n), m<n, "rank"=m$.
  + $max -> min(-c)$，最优值变号。
  + $<=$ / $>=$：加松弛 $+s$ / 减剩余 $-s$，$s>=0$。
  + $x<=0$ / 自由：$-x'$ / $x^+ - x^-$。
  + $b_i<0$：整行 $times(-1)$。

  == 可线性化结构（凸才可）
  + $min sum|x_i|$ → $y_i>=x_i, y_i>=-x_i$。
  + $max sum|x_i|$：❌非凸，不可。
  + $min max_i (dot)$ → $y >=$ 各项；$max min_i (dot)$ → $y <=$ 各项。
  + $max (c^T x+alpha)/(d^T x+beta)$ → Charnes-Cooper：$t=1/(d^T x+beta), y=t x$。
  + $y=1 => a^T x<=b$ → $a^T x <= b + M(1-y)$。
  - Big-M 取紧（由上下界推），过大 $→$ LP 松弛弱、分支慢。
  - $z = x y$（0-1²）：$z<=x,z<=y,z>=x+y-1,z>=0$。
]

// ============ 1. 单纯形法 ============
= 单纯形法

#container[
  == BFS(基本可行解) 与极点
  - 基本解：选 $A$ 的 $m$ 个线性无关列 $B$，$x_B = A_B^(-1) b, x_N=0$；再加 $x>=0$ 得 *BFS* = 极点。
  - 基本解个数 $<= binom(n,m)$。基本定理：有最优则存在*最优 BFS*。

  == 判别 BFS（给定点 $x$，按以下步骤逐条判断）
  + 验 $A x = b$ ？否 $=> $ 非基本解。
  + 非零分量个数 $<= m$ ？否 $=> $ 非基本解。
  + 非零分量对应列 ${A_j : x_j != 0}$ 线性无关 ？相关 $=> $ 非基本解。
  + $x >= 0$：有负 $=> $ 基本解但*不可行*（非 BFS）。

  以上全过 $=> $ $x$是基本可行解 $<=> $ 极点。


  == 检验数与最优性
  $macron(c)_j = c_j - c_B^T A_B^(-1) A_j$ （reduced cost）.
  - 对 $min$：$macron(c)_j >= 0$ 全成立 $=> $ 最优；$macron(c)_j<0 => x_j$ 入基。
  - 基变量检验数恒 0。

  == 单纯形表
  
#figure(
  image("1-单纯型表.png", width: 30%),
)

  - *枢轴 (pivot)* = 一次换基的高斯消元：① 枢轴行 $ell$ 除以 $macron(A)_(ell e)$ 使转轴元素变 1；② 其余行（含目标行）消去第 $e$ 列使其变为 0。
  - 换基后 $x_(B(e))$ 出基、$x_e$ 入基；新 $macron(A),macron(b),macron(c)$ 由消元自动得到。
  - 矩阵视角 $macron(x)_B = A_B^(-1) b$（ $macron(·)$ 表示迭代后的，没有则表示迭代前的）
  $
  macron(A)_N = A_B^(-1) A_N,quad macron(c)_N^T = c_N^T - c_B^T A_B^(-1) A_N,quad macron(b) = A_B^(-1) b
  $
  $
  macron(A)_B=I, quad macron(c)_B=0,quad Delta"目标值"= -c_B^T A_B^(-1) b
  $

  == 单纯形法基本步骤
  给定基 $B$ 的 BFS $x$，重复：
  + 算检验数 $macron(c)_j$；若全 $>= 0 -> $ 最优，停止迭代。
  + 否则选某 $macron(c)_j < 0$ 的 $x_j$ *入基*。
  + 算基方向 $d = [-A_B^(-1) A_j; e_j]$；若 $A_j <= 0 -> $ 无界（$-infinity$）。
  + 否则最小比值 $theta^* = min_(i, A_(i j)>0) {b_i / (A_(i j) )}$，取到者*出基*。
  + 对单纯形表做一次枢轴，回步骤 1。
  - 优先选最大负检验数减少迭代次数；退化时 $theta^*=0$ 可能循环。

  == 参数单纯形表判别
  - 当前*可行*：RHS（$macron(b)$）全 $>= 0$。
  - 当前*最优*（min）：可行 + 所有检验数 $macron(c) >= 0$。
  - *无界*：存在 $macron(c)_j < 0$ 且该列所有 $macron(a)_(i j) <= 0$。

  == 找初始 BFS
  - 大 M 法：$min c^T x + M sum a_i$；$a^*>0 => $ 无可行解。。
  - 两阶段法：阶段一 $min 1^T a$（最优 0 $<=> $ 可行）；阶段二删人工列、换回原 $macron(c)$。
  #figure(
    image("2-大M法与两阶段法.png", width: 40%),
  )
  == 从阶段一恢复到原问题
  阶段一最优值 $=0$（$a=0$）时，阶段一末的 BFS 即原问题的一个初始 BFS，按以下步骤切换到阶段二：
  + *删人工变量列*：把所有人工变量 $a_i$ 的列从单纯形表中去掉（它们已归零，不再参与）。
  + *目标行换回原目标*：用原系数 $c$ 重算检验数 $macron(c)_j = c_j - c_B^T A_B^(-1) A_j$，当前值 $z = -c_B^T A_B^(-1) b$（$c_B$ = 当前基变量在*原*目标里的系数）。
  + *基里仍留人工变量则替换*（退化情形）：若某人工变量仍在基中且取 0，找其行中非零的原始变量转轴换出它；若整行为 0（冗余约束）则直接删行。
  - 随后对换回原目标的表继续单纯形迭代，直至 $macron(c)>=0$ 得原问题最优。
  == 算例：两阶段法解
  #figure(
    image("4-两阶段法案例.png", width: 100%),
  )
]

// ============ 2. 对偶 & 灵敏度 ============
= LP 对偶 & 灵敏度

#container[
  == 对偶构造
  // #table(
  //   columns: 2,
  //   [*原*], [*对偶*],
  //   [$max c^T x, A x<=b, x>=0$], [$min b^T y, A^T y>=c, y>=0$],
  //   [$min c^T x, A x=b, x>=0$], [$max b^T y, A^T y<=c, y "free"$],
  // )
  #figure(
    image("6-原转对偶.png", width: 50%),
  )

  == 三大定理
  - *弱对偶*：$max$ 问题 $c^T x <= b^T y$（对偶给界）。
  $
  c^T x <= (A^T y)^T x = y^T (A x) <= y^T b = b^T y
  $
  - *强对偶*：有限最优 $=> p^* = d^*$（无对偶间隙）。
    - 等号可达来自 *Farkas 引理* / 支撑超平面定理 / KKT......
  - *互补松弛*：$y_i^*(b_i - a_i^T x^*)=0$，$x_j^*((A^T y^*)_j - c_j)=0$。

  #figure(
    image("5-原问题与对偶问题.png", width: 25%),
  )

  == 对偶状态判定（易考）
  + 一方有最优 $arrow.r$ 另一方有最优且 $p^* = d^*$。
  + 一方*无界* $arrow.r$ 另一方*无可行解*（不可逆：另一边可能无界或无可行）。
  + 两边都*无可行解*可共存。

  == 用互补松弛判 LP 最优（步骤）
  
  对最优 $x^*$判断是否最优：$y_i^*(b_i - a_i^T x^*)=0$，$x_j^*((A^T y^*)_j - c_j)=0$.
  + 写出原、对偶问题；
  + 据互补松弛定零：$b_i - a_i^T x^* = 0 ->$ 约束紧 $y_j$ 可以不为0；约束 $i$ 松（$a_i^T x^*<b_i$）$-> y_i=0$。
  + 解剩余的线性方程组定出未知的 $y^*$。
  + 验证对偶可行性，$y$ 在对偶约束内；若成立则 $x^*$ 最优。
  - 约束紧时乘子*可以*为 0（正确表述是"乘积为零"，非"紧则乘子正"）。

  == 影子价格
  - $y^* = c_B^T A_B^(-1) = nabla V(b)$：资源 $i$ 增 1 单位，最优值边际变化（局部，最优基不变时）。
  - 互补松弛：紧约束（资源用尽）$arrow.r y_i^*$ 可正；非紧 $arrow.r y_i^* = 0$（过剩资源多给无用）。

  == 局部灵敏度（最优基不变）
  $c$、$b$ 小幅扰动、最优基不变时：
  #table(
    columns: 3,
    [*改动*], [*$Delta V$*], [*条件*],
    [$c_i -> c_i + Delta c_i$], [$Delta c_i times x_i^*$], [$nabla V(c) = x^*$（唯一最优）],
    [$b_i -> b_i + Delta b_i$], [$Delta b_i times y_i^*$], [$nabla V(b) = y^*$（对偶唯一）],
  )

  == 全局灵敏度（保基范围）
  最优基 $B$ 须同时：可行性 $x_B = A_B^(-1) b >= 0$ + 最优性 $macron(c)_N = c_N^T - c_B^T A_B^(-1) A_N >= 0$。

  *改单个 $b_i$*（$Delta b = lambda e_i$）：扰动后 $x_B = x_B^* + lambda A_B^(-1) e_i >= 0$（$A_B^(-1) e_i$ = $A_B^(-1)$ 第 $i$ 列），解不等式组得 $lambda$ 范围；范围内基不变、$y^*$ 不变、$Delta V = lambda y_i^*$。

  *改单个 $c_j$*（可行性不动，只看最优性）：
  + $j in N$（非基）：仅 $macron(c)_j + lambda >= 0 arrow.l.r lambda >= -bar(c)_j$（单边）。
  + $j in B$（基）：$macron(c)_N^T - lambda e_j^T A_B^(-1) A_N >= 0$（一组不等式），解出区间。

  *加新变量*：原解仍可行、$macron(c)$ 不变，只算新列 $macron(c)_("new") = y^T a_("new") - c_("new")$；$>= 0$ 不生产，$< 0$ 入基迭代。

  *加新约束*：先验原最优解是否满足；满足 $arrow.r$ 仍最优，不满足 $arrow.r$ 对偶单纯形热启动。

  *改 $A$*：改非基列 $a_j arrow.r$ 重算该列 $macron(c)_j$；改基列 $arrow.r$ 整表重算。

  == Farkas 引理
  ${A x=b, x>=0}$ 与 ${A^T y>=0, b^T y<0}$ 择一有解；后者是不可行证书。应用：资产定价无套利 $<=> $ 存在状态价格 $y>=0$。

  == 外汇套利识别
  - 汇率 $r_(i j)$（1 单位 $i arrow.r j$）。取 $w_(i j) = -log r_(i j)$。
  - *套利 $arrow.l.r$ 存在负权有向环* $sum_(c in C) w_(i j) < 0 arrow.l.r product r_(i j) > 1$；用 Bellman-Ford 检负环。
  - LP 流模型：$x_(i j)$ = 兑换金额，非美元节点流量守恒；美元净流入 $>$ 初始美元流出 $arrow.r$ 有套利。

  == 对偶单纯形法
  - 保持 $macron(c)>=0$（对偶可行），修 $macron(b)$（$->>=0$）。
  - 选 $macron(b)_ell<0$ 行出基；入基 $min_(v_i<0) macron(c)_i\/|v_i|$。
  - 转轴行全 $v_i>=0 => $ 对偶无界 $=> $ 原不可行。
]

// ============ 3. 凸分析基础 ============
= 凸集 · 凸函数 · 凸优化

#container[
  == 凸集
  - $theta x_1 + (1-theta) x_2 in C$。
  - 保凸：交、Minkowski 和、平移、线性像/原像。
  - 凸包 $"conv"(S)$ = 所有点凸组合 = 最小凸集。
  - 分离/支撑超平面定理：对偶、KKT 的几何基础。

  == 凸函数
  - $f(theta x+(1-theta)y) <= theta f(x)+(1-theta)f(y)$。( 严格凸时不取等)
  - $mu$-强凸：$f(y)>=f(x)+nabla f^T(y-x)+mu/2||y-x||^2$。
  - *一阶*：$f$ 凸 $<=> f(y) >= f(x)+nabla f^T (y-x)$。
  - *二阶*：$f$ 凸 $<=> nabla^2 f >= 0$。
  - 上图 $f$ 凸 $<=> "epi" f$ 凸；下水平集凸 $<=> $ *拟凸*。
  - 常见凸：仿射、范数、正定二次型、$max_i f_i$、$e^x$、log-sum-exp。
  - 保凸：非负加权和、逐点最大值、仿射复合。

  == 凸优化
  $min f_0(x)$ s.t. $f_i(x)<=0, h_i(x)=0$，$f_0, f_i$ 凸，$h_i$ 仿射
  - *局部最优 = 全局最优*。
  - 一阶最优：$nabla f(x^*)^T (y-x^*) >= 0 forall y in C$。

  == 谱系（锥优化）
  $"LP" subset "QP" subset "QCQP" subset "SOCP" subset "SDP"$.
  - QP：$1/2 x^T P x + q^T x (P " PSD")$。
  - SOCP：$||A_i x+b_i||_2 <= c_i^T x+d_i$。
  - 鲁棒 LP（$a$ 落椭球）$<=> $ SOCP：$||P^T x||_2 <= b - bar(a)^T x$。
]

// ============ 4. KKT & 拉格朗日对偶 ============
= KKT & 拉格朗日对偶

#container[
  == 无约束最优性
  - 一阶必要：$nabla f(x^*)=0$（只筛驻点，如 $x^3$ 非极小）。
  - 二阶必要：$nabla^2 f >= 0$；充分：$nabla^2 f succ 0$。
  - 凸：$nabla f=0$ $<=> $ 全局最优（充要）。

  == KKT 四件套
  $min f$ s.t. $h_i=0, g_j<=0$，$L = f + sum lambda_i h_i + sum mu_j g_j$（$lambda$ 自由，$mu>=0$）：
  + 原始可行 $h_i=0, g_j<=0$；
  + 对偶可行 $mu_j>=0$；
  + 平稳性 $nabla f + sum lambda_i nabla h_i + sum mu_j nabla g_j = 0$；
  + 互补松弛 $mu_j g_j = 0$。

  - 非活跃约束（$g_j<0$）$=> mu_j=0$。
  - *凸问题*（$f,g$ 凸、$h$ 仿射）KKT $=>$ 全局最优（既必要又充分）。

  == 约束资格 (CQ)
  - LICQ：活跃约束梯度线性无关。
  - MFCQ：弱于 LICQ。
  - *Slater*（凸）：存在严格可行点 $g_j<0 => $ 强对偶 + KKT。

  == 拉格朗日对偶
  - 对偶函数 $g(lambda, nu) = inf_x L$，*恒凹*，$lambda>=0 => g <= p^*$（下界）。
  - 对偶问题 $max_(lambda>=0) g$，$d^* <= p^*$（弱对偶总成立）。
  - 强对偶 $d^*=p^*$：凸 + Slater 时成立。

]

// ============ 5. 无约束迭代法 ============
= 梯度下降 · 动量 · Newton

#container[
  == 梯度下降 (GD)
  $x^(k+1) = x^k - alpha_k nabla f(x^k)$.
  - 最速下降方向：$d = -nabla f \/ ||nabla f||$（Cauchy-Schwarz 取等）。
  - *$L$-光滑*：$f(y) <= f(x) + nabla f^T (y-x) + L/2 ||y-x||^2$。
  - 充分下降：$f(x^+) <= f(x) - alpha(1 - L alpha\/2)||nabla f||^2$；$alpha < 2\/L$ 下降，取 $1\/L$。
  - 步长：常数 $1\/L$（需估 $L$）、精确线搜索（二次 $alpha = g^T g\/g^T Q g$）、Armijo/回溯（免估 $L$）、递减 $alpha_0\/sqrt(k)$（SGD）。
  - *回溯线搜索*：$t=1$；while $f(x+t d) > f(x) + c_1 t g^T d$ do $t = beta t$（$d=-nabla f$）。常用 $c_1=0.1, beta=0.7$。

  == 收敛速度
  - 强凸 GD *最优步长* $alpha = 2\/(L+mu)$，*收敛因子* $rho = (L-mu)\/(L+mu) = (kappa-1)\/(kappa+1)$；HB $rho = (sqrt(kappa)-1)\/(sqrt(kappa)+1)$（$kappa arrow.r sqrt(kappa)$）。
  #table(
    columns: 3,
    [*假设*], [*度量*], [*速率*],
    [非凸+$L$-光滑], [$min||nabla f||^2$], [$O(1\/k)$],
    [凸+$L$-光滑], [$f-f^*$], [$O(1\/k)$],
    [$mu$-强凸+$L$-光滑], [$f-f^*$], [$(1-1\/kappa)^k$ 线性],
  )
  - 条件数 $kappa = L\/mu$；大 $-> $ zig-zag、慢。

  == 动量 & Nesterov
  - *Heavy-ball*：$x^(k+1) = x^k - alpha nabla f(x^k) + beta(x^k - x^(k-1))$（梯度在 $x^k$）。
  - *NAG*：$y^k = x^k + beta_k(x^k - x^(k-1))$，$x^(k+1) = y^k - alpha nabla f(y^k)$（梯度在*前瞻点* $y^k$）。
  - 强凸因子：$(sqrt(kappa)-1)\/(sqrt(kappa)+1)$（$kappa -> sqrt(kappa)$）。
  - 光滑凸函数值率：GD $O(1\/k) -> $ NAG $O(1\/k^2)$（一阶最优率）。

  == Newton & 拟牛顿
  - Newton 方向：$G_k d^k = -g_k$，$d = -nabla^2 f^-1 nabla f$。$G_k succ 0 => $ 下降。
  - Newton 减量 $lambda_k^2 = g_k^T G_k^-1 g_k$（停止准则）。
  - 全局化：阻尼 Newton（Armijo 步长）、Hessian 修正 $G + tau I$、信赖域 $||d|| <= Delta$。
  - *局部二次收敛*（不依 $kappa$）；每步 $O(n^3)$。
  - 拟牛顿：割线条件 $B_(k+1) s_k = y_k$（$s = Delta x, y = Delta nabla f$）。
  - *BFGS*（逆更新，$rho = 1\/y^T s$）：$H_(k+1) = (I - rho s y^T) H_k (I - rho y s^T) + rho s s^T$；$y^T s > 0$（Wolfe）保正定；超线性。
  - *L-BFGS*：只存最近 $m$ 对 $(s, y)$，$O(m n)$，大规模。
  - *Wolfe 线搜索*（$d$ 下降方向，$0<c_1<c_2<1$）：① 充分下降 $f(x+t d)<=f(x)+c_1 t g^T d$；② 曲率 $nabla f(x+t d)^T d >= c_2 g^T d$。二分法找 $t$；保 $y^T s>0$ 使 BFGS 正定。

  #table(
    columns: 4,
    [*方法*], [*信息*], [*代价*], [*收敛*],
    [GD], [梯度], [低], [凸 $O(1\/k)$],
    [NAG], [梯度+历史], [低], [$O(1\/k^2)$],
    [Newton], [+Hessian], [$O(n^3)$], [局部二次],
    [BFGS], [+曲率近似], [$O(n^2)$], [超线性],
    [L-BFGS], [$m$ 对曲率], [$O(m n)$], [实践高效],
  )
]

// ============ 6. 约束 / 近端 / 随机 ============
= 投影 · 近端 · SGD · Adam

#container[
  == 投影梯度 (PGD)
  $x^(k+1) = Pi_C (x^k - alpha nabla f(x^k))$，$Pi_C(z) = argmin_(x in C) 1\/2 ||x-z||^2$.
  - 投影最优性：$(z-x)^T(y-x) <= 0 forall y in C$。
  - 常见投影：$[l,u]$ 截断；非负 $max(z_i, 0)$；欧氏球 $z$ 或 $R z\/||z||$；仿射 $z - A^T(A A^T)^-1(A z - b)$；单纯形 $max(z_i - tau, 0)$（$tau$ 由和 $=1$ 定）。

  == 近端梯度
  复合优化 $min F = f + g$（$f$ 光滑，$g$ 不可导但结构简单）：
  $x^(k+1) = "prox"_(alpha g)(x^k - alpha nabla f(x^k))$，
  $"prox"_(alpha g)(z) = argmin_x {g(x) + 1\/(2 alpha) ||x-z||^2}$.
  #table(
    columns: 2,
    [*$g$*], [*$"prox"_(alpha g)(z)$*],
    [指示 $I_C$], [$Pi_C(z)$ ⇒ PGD 是特例],
    [$lambda||x||_1$], [软阈值 $"sign"(z) max(|z|-alpha lambda, 0)$],
    [$lambda\/2||x||_2^2$], [$z\/(1+alpha lambda)$],
    [核范数], [对奇异值软阈值 (SVT)],
  )
  - *ISTA*：$O(1\/k)$；*FISTA*（加 Nesterov 外推 $y^k = x^k + beta_k(x^k - x^(k-1))$）：$O(1\/k^2)$，可能不单调。

  == SGD / Mini-batch / Adam
  - 有限和 $f(w) = 1\/n sum f_i$；SGD $w^(k+1) = w - alpha nabla f_(i_k)$，*无偏* $E[nabla f_(i_k)] = nabla f$。
  - 方差 $approx O(1\/|B|)$；batch 大方差小但每 epoch iteration 少。
  - iteration = 一次更新；epoch $approx ceil(n\/B)$ iter。
  - *Momentum*：$v = beta v + (1-beta) g$，$w -= alpha v$。
  - *RMSProp*：$s = rho s + (1-rho) g^2$，$w -= alpha g\/sqrt(s)$。
  - *Adam*：$m_k = beta_1 m_(k-1) + (1-beta_1) g_k$，$v_k = beta_2 v_(k-1) + (1-beta_2) g^2$，偏差修正 $hat m = m\/(1-beta_1^k)$，$w -= alpha hat m\/(sqrt(hat v)+epsilon)$。默认 $beta_1=0.9, beta_2=0.999$。
  - *AdamW*：解耦权重衰减 $w -= alpha hat m\/sqrt(hat v) - alpha lambda w$。
  - 学习率最关键；warmup + 衰减常显著改善。
]

// ============ 7. 整数规划 ============
= 整数规划 · 建模 & 求解

#container[
  == 三类集合模型
  #table(
    columns: 3,
    [*模型*], [*约束*], [*含义*],
    [集合覆盖], [$sum a_(i j) x_j >= 1$], [至少满足一次],
    [集合划分], [$sum a_(i j) x_j = 1$], [恰好一次],
    [集合打包], [$sum a_(i j) x_j <= 1$], [至多一次],
  )

  == 逻辑线性化（0-1 + Big-M）
  - 开关 $y=1 => a^T x<=b$：$a^T x <= b + M(1-y)$。
  - 至少 K 个成立：$z_i$ 激活 + $sum z_i >= K$。
  - 多前提蕴含：$+ M sum(1-y_i)$。
  - 有限取值 $x in {v_1,..,v_K}$：$x = sum v_k z_k, sum z_k = 1$。
  - 0-1×连续 $z = x y$（$0<=x<=U$）：$z<=U y, z<=x, z>=x-U(1-y), z>=0$。

  == VRP / 下料
  - 弧变量：流平衡 $sum x_(i j k) = y_(i k) = sum x_(j i k)$；容量 $sum d_i y_(i k) <= Q$；时间窗 Big-M；子回路消除 $sum_(i,j in S) x_(i j k) <= |S|-1$（指数级，动态加）。
  - 下料：模式 $a_r$（$sum l_i a_(i r) <= L$），$min sum x_r$ s.t. $sum a_(i r) x_r >= d_i$。模式爆炸 $-> $ 列生成。

  == 求解：松弛 + 分支定界 + 割平面
  - LP 松弛：$min$ 给*下界*，$max$ 给*上界*；整数解给另一侧界。
  - *MIP gap* $= |z_("inc") - z_("bd")| \/ (|z_("inc")| + epsilon)$。
  - 分支：$x_j^* = 3.7 -> x_j <= 3$ 与 $x_j >= 4$。剪枝：不可行 / 界 / 整数。
  - *割平面*：保留所有整数解、切掉分数解。Cover cut：$sum_(i in C) w_i > W => sum_(i in C) x_i <= |C|-1$。
  - *Branch-and-Cut*：解 LP→加割→分支。
  - presolve：固定必然取值变量、收紧界、删冗余。
  - 启发式：舍入、Diving、Local search、Feasibility Pump 找 incumbent。

  #table(
    columns: 2,
    [*坑*], [*纠正*],
    [松弛界方向反], [$min$ 下界，$max$ 上界],
    [找到好解=最优], [需界证明],
    [割删了整数解], [有效不等式保留整数解],
    [Big-M 随便取大], [取紧，否则节点爆炸],
  )
]

// ============ 8. 列生成 & 网络流 ============
= 列生成 · 网络流

#container[
  == 列生成
  变量 = 完整方案（切割模式/车辆路线/排班），数量指数级。
  - *核心循环*：① 解 RMP（限制主问题）；② 取对偶价格 $pi$；③ 解*定价子问题*找最小 reduced cost 列；④ 有负检验数列则加入，否则 RMP = 完整 LP 松弛最优。
  - 下料定价 = 整数背包 $max sum pi_i a_i$ s.t. $sum l_i a_i <= L$；最优值 $>1 => $ 加列。
  - VRP 定价 = 资源约束最短路（reduced cost = route cost $- sum pi_i$）。
  - *DW LP 松弛比直接 LP 松弛更强*：保留局部整数结构，只放松方案组合权重。
  - 列生成停 $!= $ 整数最优；需 *Branch-and-Price*（分支规则须与定价子问题兼容，常按弧分支）。

  == 最大流
  $max F$ s.t. 节点平衡（$s$ 净出 $F$，中间 $0$，$t$ 净入 $F$），$0 <= x_(i j) <= u_(i j)$.
  - *最大流-最小割定理*：$max F = min u(S, T)$，$u(S,T) = sum_(i in S, j in T) u_(i j)$（只算 $S->T$ 弧）。
  - 整数容量 $=> $ 整数最优解（节点-弧矩阵全酉模）。
  - Ford-Fulkerson 增广路：残量网络找 $s$-$t$ 路，增广 $delta = min$ 残量；停时 $s$ 可达集即最小割。Edmonds-Karp $O(|N||A|^2)$。

  == 最小费用流
  $min sum c_(i j) x_(i j)$ s.t. 节点供需 $b_i$ + 容量。$sum b_i = 0$。
  - 整数 $b, u => $ 整数最优。*最优性*：残量网络无*负费用环*。
  - 统一最短路/运输/指派/最大流。
  - 算法：逐次最短路、负环消去、网络单纯形。

  == 时空网络流
  - 节点 $(i, t)$（地点×时间）；弧 = 等待 $(i,t)->(i,t+1)$、运输 $(i,t)->(j,t+tau_(i j))$、服务、外部。
  - 本质仍是最小费用流；库存平衡 $I_t = I_(t-1) + q_t - d_t$ 即流守恒。

  == 何时变 NP-hard
  单商品线性流多项式可解；加*固定启用成本*（$x <= u y$）、*多商品*、*路径数限制*、*时间窗/资源* $-> $ 整数规划。
  - 列生成的"列"常 = 网络中一条可行路径；网络流为定价子问题提供算法基础。
]
