---
type: practice-solutions
course: 随机过程
created: 2026-10-27
reviewed: false
title: Chap5-2 泊松过程综合训练题参考解答
---
# Chap5-2 泊松过程综合训练题：参考解答

本页对应[[Chap5-2-泊松过程综合训练题|10 道综合训练题]]。题目中的速率、独立性和初始状态均在题目页完整列出；以下按照各题分问推导。

## 第 1 题：车辆分类与条件独立性

车辆到达速率为 12，四类概率为 $(0.4,0.3,0.2,0.1)$。按独立分类性质，四类车辆分别形成相互独立的泊松过程，速率为

$$
12(0.4,0.3,0.2,0.1)=(4.8,3.6,2.4,1.2).
$$

**1. 联合分布。** 对非负整数 $n_1,\ldots,n_4$，

$$
P(N_j(1)=n_j,\ j=1,\ldots,4)
=\prod_{j=1}^{4} e^{-12p_j}\frac{(12p_j)^{n_j}}{n_j!},
$$

其中 $(p_1,p_2,p_3,p_4)=(0.4,0.3,0.2,0.1)$。四个计数相互独立，均为参数分别为 $4.8,3.6,2.4,1.2$ 的泊松变量。

**2. 前三类各至少一次、第四类为零。** 由独立性，

$$
\begin{aligned}
&P(N_1(1)\geq1,N_2(1)\geq1,N_3(1)\geq1,N_4(1)=0)\\
&\quad=(1-e^{-4.8})(1-e^{-3.6})(1-e^{-2.4})e^{-1.2}
\approx0.2642.
\end{aligned}
$$

**3. 给定前两类的总数。** 在一辆属于类型 1 或 2 的车中，它属于类型 1 的条件概率为

$$
\frac{0.4}{0.4+0.3}=\frac47.
$$

因此，给定前两类一共有 6 辆，其中类型 1 的数量为 $\operatorname{Bin}(6,4/7)$，所求概率为

$$
\binom64\left(\frac47\right)^4\left(\frac37\right)^2
\approx0.2938.
$$

**4. 给定全部车辆总数。** 给定 $N(1)=10$，四类数量的联合条件分布为

$$
\begin{gathered}
(N_1(1),N_2(1),N_3(1),N_4(1))\mid N(1)=10\\
\sim\operatorname{Multinomial}(10;0.4,0.3,0.2,0.1).
\end{gathered}
$$

例如，当 $n_1+\cdots+n_4=10$ 时，其概率为

$$
\frac{10!}{n_1!n_2!n_3!n_4!}
0.4^{n_1}0.3^{n_2}0.2^{n_3}0.1^{n_4}.
$$

多项分布的协方差给出

$$
\operatorname{Cov}(N_1(1),N_2(1)\mid N(1)=10)
=-10(0.4)(0.3)=-1.2.
$$

不附加总数条件时，两类计数独立，协方差为 0。给定总数后，分给一种类型的车辆增加，会减少其余类型可分配的数量。

## 第 2 题：独立过程的叠加与到达竞争

记 A、B 的速率为 $\lambda_A=3$、$\lambda_B=2$。令

$$
p=\frac{\lambda_A}{\lambda_A+\lambda_B}=\frac35,
\qquad q=1-p=\frac25.
$$

合并后的报警类型构成独立同分布的标签序列，每次为 A 的概率是 $p$，为 B 的概率是 $q$。

**1. 速率与首次类型。** 合并过程是速率 $3+2=5$ 的泊松过程。第一次报警来自 A 的概率为 $p=3/5$。

**2. 前三次报警中恰有两次来自 A。** 由二项分布，

$$
\binom32p^2q
=3\left(\frac35\right)^2\frac25=0.432.
$$

**3. A 的第 3 次早于 B 的第 2 次。** 当第 3 次 A 出现时，此前的 B 只能有 0 次或 1 次。若有 $k$ 次 B，最后一次标签是 A，而此前 $k+2$ 个标签包含两次 A 和 $k$ 次 B，故

$$
\begin{aligned}
P(S_3^{(A)}<S_2^{(B)})
&=\sum_{k=0}^{1}\binom{k+2}{2}p^3q^k\\
&=p^3(1+3q)=0.4752.
\end{aligned}
$$

**4. 第 3 次 A 之前的 B 次数。** 对 $k=0,1,2,\ldots$，同样由最后一个标签为 A 得到

$$
P(K=k)=\binom{k+2}{2}p^3q^k.
$$

$K$ 是取得第 3 次 A 之前的 B 次数，服从负二项分布，其期望为

$$
E[K]=\frac{3q}{p}=2.
$$

第 3 问是 $P(K\leq1)$。也可把 $K$ 写成三次相邻 A 之间的 B 次数之和，每段期望均为 $q/p$。

## 第 3 题：给定总数与给定第 4 次到达时刻

**1. 给定 $N(T)=n$。** 由于两个不重叠区间内的到达数独立，

$$
\begin{aligned}
P(N(s)=i\mid N(T)=n)
&=\frac{P(N(s)=i)P(N(T)-N(s)=n-i)}{P(N(T)=n)}\\
&=\binom ni\left(\frac{s}{T}\right)^i
\left(1-\frac{s}{T}\right)^{n-i}.
\end{aligned}
$$

因此 $N(s)\mid N(T)=n\sim\operatorname{Bin}(n,s/T)$。

**2. 给定 $N(T)=4$。** 四个有序到达时刻对应四个独立 $\operatorname{Uniform}(0,T)$ 变量的次序统计量，所以

$$
E[S_1\mid N(T)=4]=\frac{T}{5}.
$$

事件 $S_2\leq T/2<S_4$ 等价于前半段有 2 次或 3 次到达。给定总数 4，前半段计数为 $\operatorname{Bin}(4,1/2)$，从而

$$
P(S_2\leq T/2<S_4\mid N(T)=4)
=\frac{\binom42+\binom43}{2^4}=\frac58.
$$

**3. 给定 $S_4=T$。** 此时第 4 次到达固定在 $T$，前面只有 3 个随机时刻；它们对应 3 个独立 $\operatorname{Uniform}(0,T)$ 变量的次序统计量。因此

$$
E[S_1\mid S_4=T]=\frac{T}{4}.
$$

对于所求事件，只需前 3 次中至少 2 次发生在 $T/2$ 之前，故

$$
P(S_2\leq T/2<S_4\mid S_4=T)
=P\!\left(\operatorname{Bin}\left(3,\frac12\right)\geq2\right)
=\frac12.
$$

$N(T)=4$ 只规定总数，4 个时刻均随机；$S_4=T$ 固定了最后一次到达，随机时刻只剩 3 个。后一条件使用条件密度，而不是把 $P(S_4=T)$ 当成正概率。

**4. 与到达次序有关的加权和。** 由四个均匀次序统计量的均值，

$$
E[S_1\mid N(T)=4]=\frac T5,\qquad
E[S_4\mid N(T)=4]=\frac{4T}{5}.
$$

因此

$$
E[2S_1+S_4\mid N(T)=4]
=2\cdot\frac T5+\frac{4T}{5}=\frac{6T}{5}.
$$

系数 2 专门作用于最早时刻，$S_4$ 则是最晚时刻；表达式会随交换而改变。正确表示是 $2U_{(1)}+U_{(4)}$，不能用 $2U_1+U_4$。若错误地用后者，期望会得到 $3T/2$。

## 第 4 题：折现索赔与衰减冲击

记

$$
h_1(t)=\frac1t\int_0^t e^{-\alpha u}\,du
=\frac{1-e^{-\alpha t}}{\alpha t},
\qquad
h_2(t)=\frac1t\int_0^t e^{-2\alpha u}\,du
=\frac{1-e^{-2\alpha t}}{2\alpha t}.
$$

**1. 条件期望。** 给定总数和到达时刻后，$E[C_i]=m$，所以

$$
E[D(t)\mid N(t)=n,S_1,\ldots,S_n]
=m\sum_{i=1}^n e^{-\alpha S_i}.
$$

这个和对到达时刻的排列不变。给定 $N(t)=n$，可以用 $n$ 个未排序独立均匀时刻来计算这个和，从而

$$
E[D(t)\mid N(t)=n]=nmh_1(t)
=\frac{nm}{\alpha t}(1-e^{-\alpha t}).
$$

对于 $n=0$，两边均为 0。

**2. 无条件期望与方差。** 在给定总数后，将到达时刻及其独立同分布的金额一起重新编号，可用独立的随机对 $(U_i,C_i)$ 表示；$U_i\sim\operatorname{Uniform}(0,t)$ 且与 $C_i$ 独立。令 $Z_i=C_i e^{-\alpha U_i}$，则

$$
E[Z_i]=mh_1(t),\qquad
E[Z_i^2]=v h_2(t),\qquad
\operatorname{Var}(Z_i)=v h_2(t)-m^2h_1(t)^2.
$$

所以

$$
\operatorname{Var}(D(t)\mid N(t)=n)
=n\left[v h_2(t)-m^2h_1(t)^2\right].
$$

由 $E[N(t)]=\operatorname{Var}(N(t))=\lambda t$ 和全期望、全方差公式，

$$
E[D(t)]=\lambda t\,m h_1(t)
=\frac{\lambda m}{\alpha}(1-e^{-\alpha t}),
$$

$$
\begin{aligned}
\operatorname{Var}(D(t))
&=\lambda t\left[v h_2-m^2h_1^2\right]
+\lambda t\left(mh_1\right)^2\\
&=\lambda t\,v h_2(t)
=\frac{\lambda v}{2\alpha}(1-e^{-2\alpha t}).
\end{aligned}
$$

第二个方差项来自到达总数本身的随机性，不能省略。

**3. 固定时刻的同分布。** 给定 $N(t)=n$，未排序时刻为独立的 $\operatorname{Uniform}(0,t)$ 点。将所有点 $u$ 映成 $t-u$ 后，所得点仍是同分布的独立均匀点；金额独立同分布，随各点一起保留。因此

$$
A(t)\mid N(t)=n\overset d=D(t)\mid N(t)=n.
$$

对 $n$ 求和可知 $A(t)\overset d=D(t)$。这不意味着在同一次试验中两个随机和逐项相等：同一次到达的两个系数分别是 $e^{-\alpha(t-S_i)}$ 与 $e^{-\alpha S_i}$。

**4. 两个过程的有限维分布。** 它们一般不同。由于 $C_i\geq0$，$D(t)$ 随时间不减；$A(t)$ 在两次到达之间按指数规律衰减。对于 $0<t_1<t_2$，有正概率在 $t_1$ 之前已经出现正金额且 $(t_1,t_2]$ 没有新到达，此时 $A(t_2)<A(t_1)$。而 $D(t_2)\geq D(t_1)$ 恒成立，所以两个过程的二时刻联合分布不同。

## 第 5 题：随时间变化的事件分类

服务 A 的保留概率为 $p(u)=u/2$，故其在时刻 $u$ 的强度为 $8p(u)=4u$；服务 B 的强度为 $8(1-u/2)$。

**1. 两类数量的分布。** 它们的均值分别为

$$
\theta_A=8\int_0^2\frac u2\,du=8,
\qquad
\theta_B=8\int_0^2\left(1-\frac u2\right)du=8.
$$

由独立时变分类，$N_A(2)$ 和 $N_B(2)$ 相互独立，均服从 $\operatorname{Poisson}(8)$。对 $a,b=0,1,\ldots$，

$$
P(N_A(2)=a,N_B(2)=b)
=e^{-16}\frac{8^a}{a!}\frac{8^b}{b!}.
$$

**2. 服务 A 的两个区间。**

$$
E[N_A(1)]=8\int_0^1\frac u2\,du=2,
\qquad
E[N_A(2)-N_A(1)]=8\int_1^2\frac u2\,du=6.
$$

所以两段计数分别为 $\operatorname{Poisson}(2)$ 和 $\operatorname{Poisson}(6)$，且相互独立。两个等长区间的分布不同，服务 A 过程没有平稳增量。

**3. 第一次 A 类到达。** 对 $0\leq x\leq2$，$\{\tau>x\}$ 等价于 $(0,x]$ 内没有 A 类到达，故

$$
P(\tau>x)=\exp\!\left[-8\int_0^x\frac u2\,du\right]
=e^{-2x^2}.
$$

整个观察期没有 A 类到达时规定 $\tau=\infty$，所以

$$
P(\tau=\infty)=P(N_A(2)=0)=e^{-8}.
$$

**4. 给定全部顾客数。** 给定 $N(2)=n$，未排序时刻均匀分布于 $(0,2)$。单个顾客选择 A 的平均概率为

$$
E[p(U)]=\frac12\int_0^2\frac u2\,du=\frac12,
\qquad U\sim\operatorname{Uniform}(0,2).
$$

各顾客的时刻与分类随机化相互独立，因此

$$
N_A(2)\mid N(2)=n\sim\operatorname{Bin}\left(n,\frac12\right),
\qquad N_B(2)=n-N_A(2).
$$

从而

$$
\operatorname{Cov}(N_A(2),N_B(2)\mid N(2)=n)
=-\operatorname{Var}(N_A(2)\mid N(2)=n)=-\frac n4.
$$

## 第 6 题：出售物品的阈值策略

报价速率为 $4$，报价 $X\sim\operatorname{Exp}(1/2)$，因此 $P(X>y)=e^{-y/2}$，$y\geq0$。

**1. 等待时间。** 按报价是否高于 $y$ 独立分类。合格报价的速率为 $4e^{-y/2}$，于是

$$
T_y\sim\operatorname{Exp}(4e^{-y/2}),
\qquad E[T_y]=\frac{e^{y/2}}4.
$$

**2. 成交金额和期望净收益。** 指数分布的无记忆性给出

$$
E[X\mid X>y]=y+2.
$$

等待成本为每小时 2 单位，因此

$$
V(y)=E[X\mid X>y]-2E[T_y]
=y+2-\frac12e^{y/2}.
$$

**3. 最优阈值。** 求导得到

$$
V'(y)=1-\frac14e^{y/2},\qquad
V''(y)=-\frac18e^{y/2}<0.
$$

唯一的驻点位于 $e^{y/2}=4$，即

$$
y^*=2\log4\approx2.7726.
$$

由于 $V$ 严格凹，这就是 $y\geq0$ 上的最大点；代入得

$$
V(y^*)=2\log4+2-\frac12\cdot4
=2\log4\approx2.7726.
$$

接受第一份报价相当于 $y=0$，此时 $V(0)=2-1/2=1.5$。

**4. 改为每小时成本 $c$。** 此时期望净收益为

$$
V_c(y)=y+2-\frac c4e^{y/2},\qquad
V_c'(y)=1-\frac c8e^{y/2}.
$$

因此，在必须等到售出的规则下，

$$
y^*=\begin{cases}
2\log(8/c),&0<c<8,\\
0,&c\geq8,
\end{cases}
\qquad
\max_{y\geq0}V_c(y)=\begin{cases}
2\log(8/c),&0<c<8,\\
2-c/4,&c\geq8.
\end{cases}
$$

$c\geq8$ 时接受第一份报价；最大期望净收益可以非正，因为题设要求卖方一直等待到售出，没有提供放弃交易的选项。

## 第 7 题：一次中途发货的选择

时刻 $t$ 和时刻 6 分别发出对应区间内的全部物品。

**1. 给定总数的期望等待。** 给定 $N(6)=n$，到达时刻可由 $n$ 个独立均匀点的次序统计量表示。所有物品的等待时间之和不受时刻排列影响，因此单个未排序均匀点 $U\sim\operatorname{Uniform}(0,6)$ 的平均等待时间为

$$
E[w(U)]
=\frac16\left[\int_0^t(t-u)\,du+\int_t^6(6-u)\,du\right]
=\frac{t^2+(6-t)^2}{12}.
$$

故

$$
E[W(t)\mid N(6)=n]=\frac n{12}\left[t^2+(6-t)^2\right].
$$

**2. 无条件期望与最优时刻。** $E[N(6)]=6\times6=36$，因此

$$
E[W(t)]=3\left[t^2+(6-t)^2\right].
$$

求导得 $E[W(t)]'=6(2t-6)$，二阶导数为 12，因此最优时刻是 $t=3$，最小期望总等待为

$$
E[W(3)]=3(3^2+3^2)=54\quad\text{件·小时}.
$$

若只在时刻 6 发货，

$$
E[W_0]=6\int_0^6(6-u)\,du=108\quad\text{件·小时}.
$$

**3. 两段到达数量。** 由独立增量，

$$
N(t)\sim\operatorname{Poisson}(6t),\qquad
N(6)-N(t)\sim\operatorname{Poisson}(6(6-t)),
$$

且两者独立。对非负整数 $i,j$，联合概率为

$$
e^{-6t}\frac{(6t)^i}{i!}\;
 e^{-6(6-t)}\frac{[6(6-t)]^j}{j!}.
$$

给定 $N(6)=n$ 后，

$$
N(t)\mid N(6)=n\sim\operatorname{Bin}\left(n,\frac t6\right).
$$

**4. 固定发货费用。** 以等待成本计，无中途发货的期望总成本为 108；若增加一次，最小时为 $54+K$。因此：$K<54$ 时应在时刻 3 增加一次发货；$K>54$ 时不增加；$K=54$ 时两种方案的最小期望成本相同。

## 第 8 题：独立个体的状态迁移

**1. 初始状态与下一状态的联合分类。** 对初始状态 1，按下一步的去向分裂；初始状态 2 同理。四个计数相互独立，且

$$
\begin{aligned}
Z_{11}&\sim\operatorname{Poisson}(4\cdot3/4)=\operatorname{Poisson}(3),\\
Z_{12}&\sim\operatorname{Poisson}(4\cdot1/4)=\operatorname{Poisson}(1),\\
Z_{21}&\sim\operatorname{Poisson}(6\cdot1/3)=\operatorname{Poisson}(2),\\
Z_{22}&\sim\operatorname{Poisson}(6\cdot2/3)=\operatorname{Poisson}(4).
\end{aligned}
$$

四者的联合概率质量函数是以上四个泊松质量函数的乘积。

**2. 时刻 1 的人数。**

$$
Z_1(1)=Z_{11}+Z_{21},\qquad
Z_2(1)=Z_{12}+Z_{22}.
$$

两式使用的是互不重叠的独立变量，因此

$$
Z_1(1)\sim\operatorname{Poisson}(5),\qquad
Z_2(1)\sim\operatorname{Poisson}(5),
$$

且它们相互独立。联合概率为

$$
P(Z_1(1)=a,Z_2(1)=b)
=e^{-10}\frac{5^a}{a!}\frac{5^b}{b!},\qquad a,b\geq0.
$$

**3. 不同时刻的人数。** 因为

$$
Z_1(0)=Z_{11}+Z_{12},\qquad
Z_1(1)=Z_{11}+Z_{21},
$$

两者共享 $Z_{11}$，故

$$
\operatorname{Cov}(Z_1(0),Z_1(1))
=\operatorname{Var}(Z_{11})=3.
$$

这不与第 2 问矛盾：第 2 问比较的是同一时刻的不同状态；本问比较的是不同时刻的同一状态。

**4. 给定初始状态 1 有 $n$ 个个体。** 其中仍留在状态 1 的人数为 $B\sim\operatorname{Bin}(n,3/4)$；从初始状态 2 转入状态 1 的人数仍为 $Z_{21}\sim\operatorname{Poisson}(2)$，且与 $B$ 独立。因此

$$
Z_1(1)\mid Z_1(0)=n\overset d=B+Z_{21},
$$

$$
E[Z_1(1)\mid Z_1(0)=n]=\frac{3n}{4}+2,
\qquad
\operatorname{Var}(Z_1(1)\mid Z_1(0)=n)=\frac{3n}{16}+2.
$$

**5. 任意固定时刻。** 第 $k$ 步从状态 $i$ 到状态 $j$ 的概率是 $(P^k)_{ij}$。初始两类泊松人数独立分类后再叠加，因此均值行向量为

$$
(\theta_1(k),\theta_2(k))=(4,6)P^k,
$$

且 $Z_1(k),Z_2(k)$ 相互独立，分别服从参数为 $\theta_1(k),\theta_2(k)$ 的泊松分布。

## 第 9 题：无限服务台的两个观察时刻

令 $\overline G(u)=P(V>u)$，其中 $V$ 是一位顾客的服务时间。

**1. 单个观察时刻。** 时刻 $u\in(0,t]$ 到达的顾客，到 $t$ 已完成服务的概率为 $G(t-u)$，仍在服务的概率为 $\overline G(t-u)$。独立时变分类给出

$$
X(t)\sim\operatorname{Poisson}\left(\lambda\int_0^tG(v)\,dv\right),
\qquad
Y(t)\sim\operatorname{Poisson}\left(\lambda\int_0^t\overline G(v)\,dv\right),
$$

并且 $X(t),Y(t)$ 独立。两个积分之和为 $\lambda t$，与总到达数的均值相符。

**2. 两个观察时刻。** 定义三类顾客：

- $A$：时刻 $t$ 和 $t+s$ 都在服务的人数；
- $B$：时刻 $t$ 在服务，但在 $(t,t+s]$ 内完成服务的人数；
- $C$：在 $(t,t+s]$ 到达，且在 $t+s$ 仍在服务的人数。

于是 $Y(t)=A+B$，$Y(t+s)=A+C$。设它们的均值分别为

$$
\begin{aligned}
a&=\lambda\int_0^t\overline G(t+s-u)\,du
=\lambda\int_s^{t+s}\overline G(v)\,dv,\\
b&=\lambda\int_0^t\left[G(t+s-u)-G(t-u)\right]du,\\
c&=\lambda\int_t^{t+s}\overline G(t+s-u)\,du
=\lambda\int_0^s\overline G(v)\,dv.
\end{aligned}
$$

早期到达可独立分类为 $A,B$ 等类别；后期到达来自独立的泊松增量。因此 $A,B,C$ 相互独立，且分别为参数 $a,b,c$ 的泊松变量。由共同部分 $A$，

$$
\operatorname{Cov}(Y(t),Y(t+s))=\operatorname{Var}(A)=a.
$$

若 $Y(t)=i$、$Y(t+s)=j$，共同人数 $A$ 可取 $k=0,\ldots,\min(i,j)$，因此

$$
P(Y(t)=i,Y(t+s)=j)
=e^{-(a+b+c)}
\sum_{k=0}^{\min(i,j)}
\frac{a^k}{k!}\frac{b^{i-k}}{(i-k)!}\frac{c^{j-k}}{(j-k)!}.
$$

**3. 给定当前人数。** 若 $a+b>0$，由独立泊松变量给定其总和的条件分布，

$$
A\mid A+B=n\sim\operatorname{Bin}\left(n,\frac{a}{a+b}\right).
$$

未来新到顾客人数 $C$ 独立于 $Y(t)$，所以

$$
Y(t+s)\mid Y(t)=n
\overset d=
\operatorname{Bin}\left(n,\frac{a}{a+b}\right)
+\operatorname{Poisson}(c),
$$

右侧两个变量相互独立。若 $a+b=0$，则 $Y(t)=0$ 几乎必然；题目所给正概率条件只允许 $n=0$，此时 $Y(t+s)=C$。

**4. 指数服务。** 若 $V\sim\operatorname{Exp}(\mu)$，则 $\overline G(v)=e^{-\mu v}$。令 $r=e^{-\mu s}$，有

$$
\frac{a}{a+b}=r,\qquad c=\frac\lambda\mu(1-r).
$$

因此

$$
E[Y(t+s)\mid Y(t)=n]=nr+\frac\lambda\mu(1-r),
$$

$$
\operatorname{Var}(Y(t+s)\mid Y(t)=n)
=nr(1-r)+\frac\lambda\mu(1-r).
$$

第一部分对应老顾客中的幸存者，第二部分对应后来到达且仍在服务的新顾客。

**5. 当前唯一顾客离开时系统为空。** 以当前时刻为新的时间起点，令该顾客的剩余服务时间为 $T$。由指数分布无记忆性，$T\sim\operatorname{Exp}(\mu)$，且独立于未来到达和新顾客的服务时间。

给定 $T=u$，此时未来新顾客中仍在服务的人数服从

$$
\operatorname{Poisson}\left(\frac\lambda\mu(1-e^{-\mu u})\right).
$$

当前顾客离开后系统为空，当且仅当上述人数为 0。因此

$$
\begin{aligned}
P(\text{该顾客离开后系统为空})
&=\int_0^\infty
\exp\!\left[-\frac\lambda\mu(1-e^{-\mu u})\right]
\mu e^{-\mu u}\,du\\
&=\int_0^1e^{-(\lambda/\mu)v}\,dv\\
&=\frac\mu\lambda\left(1-e^{-\lambda/\mu}\right),
\end{aligned}
$$

其中第二步令 $v=1-e^{-\mu u}$。这里允许新顾客在当前顾客离开前到达，只要求这些新顾客在观察时已经完成服务。

## 第 10 题：延迟显现与未观测数量的估计

延迟时间 $V\sim\operatorname{Exp}(1/2)$，其生存函数为 $\overline G(v)=e^{-v/2}$。设

$$
\begin{aligned}
B(t)&=\int_0^t e^{-v/2}\,dv=2(1-e^{-t/2}),\\
A(t)&=\int_0^t(1-e^{-v/2})\,dv=t-B(t).
\end{aligned}
$$

$A(t)$ 对应已经记录的平均暴露时间，$B(t)$ 对应尚未记录的平均暴露时间。

**1. 已记录与尚未记录的分布。** 在 $u$ 时刻发生的事件，到 $t$ 时已记录的概率为 $1-e^{-(t-u)/2}$，尚未记录的概率为 $e^{-(t-u)/2}$。时变分类给出

$$
R(t)\sim\operatorname{Poisson}(\lambda A(t)),\qquad
H(t)\sim\operatorname{Poisson}(\lambda B(t)),
$$

并且当 $\lambda$ 是固定参数时二者独立。对非负整数 $r,h$，联合概率为

$$
P(R(t)=r,H(t)=h)
=e^{-\lambda A(t)}\frac{[\lambda A(t)]^r}{r!}\;
 e^{-\lambda B(t)}\frac{[\lambda B(t)]^h}{h!}.
$$

**2. 利用观测数估计。** 在 $t=4$ 时，

$$
B(4)=2(1-e^{-2}),\qquad
A(4)=4-B(4)=2(1+e^{-2}).
$$

$R(4)\sim\operatorname{Poisson}(\lambda A(4))$。观测值为 30 时，似然关于 $\lambda$ 的最大点为

$$
\widehat\lambda=\frac{30}{A(4)}
=\frac{15}{1+e^{-2}}\approx13.2120\quad\text{次/小时}.
$$

把它代入 $E[H(4)]=\lambda B(4)$，得到未记录数量的期望的代入估计

$$
\widehat{E[H(4)]}
=\frac{30B(4)}{A(4)}
=30\frac{1-e^{-2}}{1+e^{-2}}
\approx22.8478.
$$

这不是说未记录事件一定有 $22.8478$ 个，而是对该计数的期望值作估计。

**3. 已知与未知的 $\lambda$。** 当 $\lambda$ 已知时，$H(4)$ 与 $R(4)$ 独立，所以

$$
H(4)\mid R(4)=30\sim\operatorname{Poisson}(\lambda B(4)),
\qquad
E[H(4)\mid R(4)=30]=\lambda B(4).
$$

若 $\lambda$ 未知且视为固定参数，这一条件期望仍是包含未知 $\lambda$ 的量。第 2 问只是将 $\lambda$ 替换为估计值，并未给出未知参数的概率分布，也没有由此自动得到一个贝叶斯条件期望。

**4. 给定事件总数。** 因为 $A(4)+B(4)=4$，记

$$
p=\frac{A(4)}4=\frac{1+e^{-2}}2,
\qquad 1-p=\frac{B(4)}4=\frac{1-e^{-2}}2.
$$

给定总数为 $n$，每个事件经平均后的记录概率为 $p$，因此

$$
R(4)\mid R(4)+H(4)=n\sim\operatorname{Bin}(n,p).
$$

此条件下 $H(4)=n-R(4)$，故

$$
\operatorname{Cov}(R(4),H(4)\mid R(4)+H(4)=n)
=-np(1-p)=-\frac n4(1-e^{-4}).
$$

不附加总数条件时，两类计数在固定 $\lambda$ 下独立；给定总数后，一个增加意味着另一个相应减少。
