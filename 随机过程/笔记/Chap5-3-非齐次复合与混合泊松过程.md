---
type: course-note
course: 随机过程
created: 2026-10-27
updated: 2026-11-11
reviewed: false
source_file: wiki/raw/随机过程/chap5-3.pdf
tags:
  - 随机过程
  - 非齐次泊松过程
  - 复合泊松过程
  - 混合泊松过程
  - 排队论
aliases:
  - 第五章 第三讲 非齐次复合与混合泊松过程
  - Chap5-3 完整笔记
title: 第五章（三） 非齐次、复合与混合泊松过程
---
# 非齐次、复合与混合泊松过程

## 1 非齐次泊松过程

### 1.1 从常数速率到强度函数

考虑一家门店。上午开门时到达的人较少，中午到达的人较多。若仍假设不重叠区间的到达数相互独立，应如何修改原来的泊松过程？可以把常数速率 $\lambda$ 换成随时刻变化的强度。

设 $\lambda(t)\geq0$ 是一个**确定的**强度函数（intensity function），并假设它在每个有限区间上可积：

$$
\int_0^t\lambda(u)\,du<\infty,\qquad t<\infty.
$$

这保证有限时间内的平均到达数有限。若用小区间微分形式描述，通常在强度连续或适当右连续的位置理解相应的一阶展开。

### 1.2 定义 5.3 与均值函数

对具有强度 $\lambda(t)$ 的过程，时刻 $t$ 后长度为 $h$ 的区间中，一次到达概率的一阶项为 $\lambda(t)h$。相应地，若计数过程 $\{N(t),t\geq0\}$ 满足下列条件，则称它为**非齐次泊松过程**（nonhomogeneous Poisson process）。

$$
\begin{aligned}
&N(0)=0;\\
&\{N(t),t\geq0\}\text{ 具有独立增量};\\
&P(N(t+h)-N(t)\geq2)=o(h);\\
&P(N(t+h)-N(t)=1)=\lambda(t)h+o(h).
\end{aligned}
\tag{1.1}
$$

相应地，零次到达的局部概率为

$$
P(N(t+h)-N(t)=0)=1-\lambda(t)h+o(h).
$$

定义**均值函数**（mean value function，也称累计强度）

$$
m(t)=\int_0^t\lambda(u)\,du.
\tag{1.2}
$$

$\lambda(t)$ 的单位是“次/单位时间”，而 $m(t)$ 的单位是“次数”。$m(t)$ 是速率曲线下的累计面积，不能用端点速率 $\lambda(t)$ 直接代替。

当 $\lambda(t)\equiv\lambda$ 时，$m(t)=\lambda t$，模型退化为齐次泊松过程。非齐次过程一般没有平稳增量，但仍有独立增量。

### 1.3 引理 5.3：零次事件的概率

先求最简单的计数概率。令 $p_0(t)=P(N(t)=0)$。截至 $t+h$ 没有事件，等价于前后两个区间均没有事件。由独立增量和 (1.1)，

$$
p_0(t+h)=p_0(t)[1-\lambda(t)h+o(h)].
$$

因此

$$
p_0'(t)=-\lambda(t)p_0(t),\qquad p_0(0)=1.
$$

两边除以 $p_0(t)$ 并积分，

$$
\log p_0(t)-\log p_0(0)
=-\int_0^t\lambda(u)\,du=-m(t).
$$

于是

$$
P(N(t)=0)=e^{-m(t)}.
\tag{1.3}
$$

因为 $\{T_1>t\}=\{N(t)=0\}$，首次到达时间的尾概率为

$$
P(T_1>t)=e^{-m(t)}.
$$

除非强度为常数，这通常不是指数分布。首次到达时间的失效率恰好为 $\lambda(t)$。

### 1.4 引理 5.4（平移时间原点）

若从固定时刻 $s\geq0$ 开始观察，令平移后的计数过程为

$$
N_s(t)=N(s+t)-N(s),\qquad t\geq0.
$$

它仍是非齐次泊松过程，但强度函数变为

$$
\lambda_s(t)=\lambda(s+t).
$$

相应均值函数为

$$
\begin{aligned}
m_s(t)
&=\int_0^t\lambda(s+u)\,du\\
&=\int_s^{s+t}\lambda(v)\,dv
=m(s+t)-m(s).
\end{aligned}
\tag{1.4}
$$

与齐次情形不同，改变观察起点后，局部速率曲线通常发生平移，因此新过程并不与原过程具有相同分布。

### 1.5 定理 5.3（计数分布）

有了零次到达的概率，再求任意次数的概率。**定理 5.3。** 对任意固定 $t\geq0$，

$$
N(t)\sim\operatorname{Poisson}(m(t)),
$$

即

$$
p_n(t):=P(N(t)=n)
=e^{-m(t)}\frac{m(t)^n}{n!},
\qquad n=0,1,2,\ldots.
\tag{1.5}
$$

**证明。** $n=0$ 已由引理 5.3 证明。对 $n\geq1$，为了在 $t+h$ 时累计达到 $n$ 次，可分为：$t$ 时已有 $n$ 次、之后零次；$t$ 时已有 $n-1$ 次、之后一次；以及短时间内出现至少两次的其余情形。最后一类总概率为 $o(h)$。所以

$$
p_n(t+h)
=p_n(t)[1-\lambda(t)h]
+p_{n-1}(t)\lambda(t)h+o(h).
$$

整理得到递推微分方程

$$
p_n'(t)=-\lambda(t)p_n(t)+\lambda(t)p_{n-1}(t),
\qquad p_n(0)=0.
\tag{1.6}
$$

假设对 $n-1$ 已有结论，乘以积分因子 $e^{m(t)}$，由于 $m'(t)=\lambda(t)$，

$$
\frac{d}{dt}[e^{m(t)}p_n(t)]
=\lambda(t)\frac{m(t)^{n-1}}{(n-1)!}.
$$

从 0 积分到 $t$：

$$
\begin{aligned}
e^{m(t)}p_n(t)
&=\int_0^t\lambda(u)\frac{m(u)^{n-1}}{(n-1)!}\,du\\
&=\frac{m(t)^n}{n!},
\end{aligned}
$$

从而得到式（1.5），归纳完成。强度分段连续时，可在各段求解并连接；有限个分界点不改变累计积分。

### 1.6 任意区间、矩与多时刻分布

对平移后的过程应用定理 5.3，得到任意区间内的计数分布

$$
N(b)-N(a)\sim
\operatorname{Poisson}\left(m(b)-m(a)\right),
\qquad 0\leq a<b.
\tag{1.7}
$$

因此

$$
E[N(t)]=\operatorname{Var}(N(t))=m(t),
$$

$$
E[N(b)-N(a)]=\operatorname{Var}(N(b)-N(a))
=\int_a^b\lambda(u)\,du.
$$

不重叠区间的计数仍可独立相乘。对于 $0=t_0<t_1<\cdots<t_k$ 和 $0=n_0\leq n_1\leq\cdots\leq n_k$，

$$
P(N(t_j)=n_j,\ j=1,\ldots,k)
=\prod_{j=1}^k
e^{-\Delta m_j}\frac{(\Delta m_j)^{n_j-n_{j-1}}}
{(n_j-n_{j-1})!},
$$

其中 $\Delta m_j=m(t_j)-m(t_{j-1})$。作为补充，累计计数的协方差为

$$
\operatorname{Cov}(N(s),N(t))=m(\min\{s,t\}).
$$

### 1.7 独立伯努利变量和的泊松极限

还可以把长区间分成许多短区间，每段只记录是否发生到达。这样，区间计数的泊松分布可由独立伯努利变量之和的极限得到。

将 $(a,b]$ 划为很多小段，在第 $j$ 段选择代表时刻 $u_j$。该段出现事件的概率近似为

$$
p_j\approx\lambda(u_j)\Delta u_j.
$$

这些概率可以不同，因此有限分割下的总和一般不是普通二项分布，而是独立、不同成功概率的伯努利变量之和。当网格越来越细，满足

$$
\max_jp_j\to0,
\qquad
\sum_jp_j\to\int_a^b\lambda(u)\,du,
$$

就得到参数为累计强度的泊松极限。它是第一篇中相同成功概率的二项极限的推广。

## 2 例 5.24（热狗摊的时变客流）

### 2.1 题设与强度函数

Siegbert 的热狗摊在上午 8 点开门，下午 5 点关门。8 点至 11 点，到达速率从每小时 5 人均匀增至 20 人。11 点至下午 1 点，速率保持每小时 20 人。下午 1 点至 5 点，速率均匀降至每小时 12 人。假设不相交时间区间内的到达数独立。建立客流模型，并求上午 8:30—9:30 没有顾客到达的概率与到达人数的期望。

以当天上午 8 点为时间 0，以小时为单位，则三个转折点为 $t=3,5,9$。分段线性强度函数为

$$
\lambda(t)=
\begin{cases}
5+5t,&0\leq t\leq3,\\
20,&3<t\leq5,\\
20-2(t-5),&5<t\leq9.
\end{cases}
\tag{2.1}
$$

首段斜率为 $(20-5)/(11-8)=5$，末段斜率为 $(12-20)/(17-13)=-2$。在给定独立增量和这种平均速率变化的基础上，采用非齐次泊松过程作为模型。

### 2.2 累计强度

用时刻 8 点作原点。将 (2.1) 分段积分，并把之前各段的累计强度相加，得到 $m(t)$

$$
m(t)=
\begin{cases}
5t+\dfrac52t^2,&0\leq t\leq3,\\
\dfrac{75}{2}+20(t-3),&3<t\leq5,\\
\dfrac{155}{2}+20(t-5)-(t-5)^2,&5<t\leq9.
\end{cases}
\tag{2.2}
$$

各段起点的常数必须包含此前已经累计的面积。因此

$$
m(3)=37.5,\qquad m(5)=77.5,\qquad m(9)=141.5.
$$

最后一个数表示当天 9 小时营业时间内的预期总到达人数；实际人数仍是整数随机变量，其均值可以是非整数。

### 2.3 指定区间的计数

上午 8:30—9:30 对应 $(0.5,1.5]$。由 (1.7)，该区间泊松计数的参数是 (2.2) 在两个端点的差

$$
\begin{aligned}
\theta
&=\int_{0.5}^{1.5}(5+5u)\,du\\
&=\left[5u+\frac52u^2\right]_{0.5}^{1.5}
=10.
\end{aligned}
$$

所以

$$
N(1.5)-N(0.5)\sim\operatorname{Poisson}(10),
$$

$$
P(N(1.5)-N(0.5)=0)=e^{-10}\approx0.000045400,
$$

$$
E[N(1.5)-N(0.5)]=10.
$$

只有因为这一段的速率是线性的，才可以用区间两端速率的平均值 $[7.5+12.5]/2=10$ 乘以 1 小时得到相同面积。对一般非线性强度，不能直接使用端点平均。

### 2.4 营业时间与日历时间（教材补充）

若时间只在营业时累积，则可将速率曲线按 9 个营业小时重复。若沿日历时间计量，则关门期间的强度为 0，整个曲线按 24 小时重复。

## 3 时变分裂与无限服务台的离开过程

### 3.1 时变抽样得到非齐次泊松过程

设到达原本按速率 $\lambda$ 的齐次泊松过程发生。若在不同时间对到达作不同概率的分类，各类过程的强度如何确定？假设时刻 $t$ 的到达独立地以概率 $p_i(t)$ 进入第 $i$ 类，其中 $\sum_i p_i(t)=1$。

第二篇的时变抽样结论给出固定时刻计数

$$
N_i(t)\sim\operatorname{Poisson}\left(\lambda\int_0^tp_i(u)\,du\right),
$$

且各类计数独立。进一步检查不同区间：各区间原到达数与随机标记独立，因此各子过程具有独立增量；在短区间内，第 $i$ 类恰好发生一次的概率为

$$
\lambda h\,p_i(t)+o(h),
$$

两次及以上概率仍为 $o(h)$。于是各类过程是相互独立的非齐次泊松过程，强度为

$$
\lambda_i(t)=\lambda p_i(t).
\tag{3.1}
$$

### 3.2 例 5.25（无限服务台的输出）

一个 $M/G/\infty$ 服务系统起初为空。顾客按速率 $\lambda$ 的泊松过程到达，且到达后立即接受服务。服务时间相互独立、同分布，分布函数为 $G$，并与到达过程独立。用 $D(t)$ 表示截至时刻 $t$ 完成服务的人数。证明 $\{D(t),t\geq0\}$ 是非齐次泊松过程，其强度为

$$
\lambda_D(t)=\lambda G(t)
$$

的非齐次泊松过程。

**先求单时刻分布。** 在 $u\leq t$ 时到达的人，到 $t$ 已经离开的概率为 $G(t-u)$。由时变抽样，

$$
D(t)\sim\operatorname{Poisson}(m_D(t)),
\qquad
m_D(t)=\lambda\int_0^tG(t-u)\,du
=\lambda\int_0^tG(v)\,dv.
\tag{3.2}
$$

但单时刻分布还不足以证明它是泊松过程，仍需证明增量独立及正确的区间分布。

### 3.3 离开计数的独立增量

先检验独立增量。任取互不相交的离开区间 $I_1,\ldots,I_k$，按各顾客的离开时刻属于哪个区间来分类，并将未落入这些区间的顾客归为另一类。

若最晚区间的右端点为 $T$，只需考虑 $(0,T]$ 内的到达，因为服务时间非负。对一位在 $u$ 到达、服务时间为 $V$ 的顾客，第 $i$ 类概率是

$$
p_i(u)=P(u+V\in I_i).
$$

各人的服务时间独立，所以这就是确定时间区间上的独立时变分类。时变分裂定理说明各类数量相互独立，而这些数量恰好是各离开区间的计数。这证明了 $D$ 的独立增量。

证明不能只说“原到达过程有独立增量，所以离开过程也有”；不同到达区间的顾客可能在同一个离开区间离开。需要按离开区间重新分类。

### 3.4 区间均值和瞬时输出强度

对 $0\leq a<b$，在 $u\leq a$ 到达的顾客落入离开区间 $(a,b]$ 的概率为

$$
G(b-u)-G(a-u),
$$

在 $a<u\leq b$ 到达的顾客，其相应概率为 $G(b-u)$。故区间离开数的均值为

$$
\begin{aligned}
E[D(b)-D(a)]
&=\lambda\int_0^a[G(b-u)-G(a-u)]\,du\\
&\quad+\lambda\int_a^bG(b-u)\,du\\
&=\lambda\int_0^bG(v)\,dv-\lambda\int_0^aG(v)\,dv\\
&=\lambda\int_a^bG(v)\,dv.
\end{aligned}
\tag{3.3}
$$

由抽样结论，该增量本身就是具有此均值的泊松变量。结合独立增量，已经确定了整个离开过程的非齐次泊松分布。

特别地，当 $b=t+h$、$a=t$ 时，利用分布函数的右连续性，

$$
\theta_h:=\lambda\int_t^{t+h}G(v)\,dv
=\lambda G(t)h+o(h).
$$

于是

$$
P(D(t+h)-D(t)=1)=\theta_he^{-\theta_h}
=\lambda G(t)h+o(h),
$$

$$
P(D(t+h)-D(t)\geq2)=1-e^{-\theta_h}(1+\theta_h)=o(h).
$$

因此输出强度确为 $\lambda G(t)$。

### 3.5 初始状态与输出强度

如果服务时间几乎必然有限，则 $G(t)\to1$，因此 $\lambda_D(t)\to\lambda$。最初系统为空时，离开流尚未积累到稳定水平；随着时间增加，输出速率趋近输入速率。

若服务时间为固定的 $d>0$，则

$$
\lambda_D(t)=
\begin{cases}
0,&t<d,\\
\lambda,&t\geq d.
\end{cases}
$$

若服务时间服从 $\operatorname{Exp}(\mu)$，则

$$
\lambda_D(t)=\lambda(1-e^{-\mu t}),
$$

$$
m_D(t)=\lambda\left[t-\frac{1-e^{-\mu t}}\mu\right].
$$

若系统从无限久以前就在运行并处于稳态，则需要使用对应的稳态初始配置，不能直接套用初始为空时的过渡公式。

## 4 非齐次过程的到达时刻（补充）

### 4.1 从固定时刻起等待下一次到达

设从固定时刻 $s$ 起的下一次等待为 $W_s$。在 $(s,s+x]$ 中没有到达的概率为

$$
P(W_s>x)
=\exp\left\{-\int_s^{s+x}\lambda(u)\,du\right\}.
\tag{4.1}
$$

它通常随起点 $s$ 改变。因而非齐次过程的到达间隔通常不再是独立同分布的指数变量；特别是下一个间隔的分布会通过当前到达时刻依赖之前的间隔。

### 4.2 第 $n$ 次到达的分布

仍有事件等价关系 $\{S_n\leq t\}=\{N(t)\geq n\}$，所以

$$
P(S_n>t)=e^{-m(t)}\sum_{j=0}^{n-1}\frac{m(t)^j}{j!}.
$$

在可微的位置，

$$
f_{S_n}(t)=\lambda(t)e^{-m(t)}
\frac{m(t)^{n-1}}{(n-1)!}.
\tag{4.2}
$$

若 $m(\infty)<\infty$，则总到达数可能不足 $n$，此时 $S_n$ 在 $+\infty$ 处有正概率；式（4.2）只描述有限时刻的密度部分。

### 4.3 给定总次数时的到达时刻

第 5 章第二部分中，给定齐次过程的总次数后，未排序的到达时刻服从均匀分布。现在不同时段的强度不同，怎样修改这组时刻的密度？当 $m(T)>0$，给定 $N(T)=n$ 时，未排序到达点可由 $n$ 个独立变量表示，其密度为

$$
f_U(u)=\frac{\lambda(u)}{m(T)},\qquad0<u<T.
\tag{4.3}
$$

相应排序后的联合密度为

$$
f(s_1,\ldots,s_n\mid N(T)=n)
=\frac{n!}{m(T)^n}\prod_{i=1}^n\lambda(s_i),
\quad 0<s_1<\cdots<s_n<T.
$$

强度大的时段更容易包含到达点。只有强度为常数时，式（4.3）才退化为 $1/T$，即第二篇的均匀分布结论。

## 5 复合泊松过程

### 5.1 定义

若每次到达带来一个随机数量，只统计到达次数便不足以描述总量。设 $\{N(t),t\geq0\}$ 是速率 $\lambda$ 的泊松过程，令 $Y_1,Y_2,\ldots$ 为各次到达的随机贡献，独立同分布，且整个序列与到达过程独立。定义

$$
X(t)=\sum_{i=1}^{N(t)}Y_i,\qquad t\geq0,
\tag{5.1}
$$

其中 $N(t)=0$ 时空和为 0。则称 $\{X(t),t\geq0\}$ 为**复合泊松过程**（compound Poisson process，CPP）。固定 $t$ 时，$X(t)$ 是复合泊松随机变量。

其中 $N(t)$ 决定求和项数，$Y_i$ 决定第 $i$ 次到达时的跳跃大小。

- 若 $Y_i\equiv1$，则 $X(t)=N(t)$，退化为普通泊松过程。
- 若 $Y_i$ 是正整数，可以表示每次到达一批人的累计人数。
- 若 $Y_i$ 是非负金额，可以表示累计索赔金额或累计销售额。
- 一般定义也允许 $Y_i$ 取负值，此时 $X(t)$ 可能下降，不再是计数过程。

### 5.2 给定事件次数后的随机和

先给定到达次数。若 $N(t)=n$，则总量可写成固定项数之和

$$
X(t)\mid N(t)=n\overset d=Y_1+\cdots+Y_n.
$$

若 $Y_i$ 的分布为 $F_Y$，则 $X(t)$ 的分布是不同卷积阶数的泊松混合：

$$
P(X(t)\leq x)
=\sum_{n=0}^\infty
e^{-\lambda t}\frac{(\lambda t)^n}{n!}F_Y^{*n}(x),
\tag{5.2}
$$

其中 $F_Y^{*0}$ 表示 0 处的点质量。这个表达也说明：随机事件数为泊松，不意味着随机金额之和还是泊松变量。

### 5.3 期望与方差

设

$$
\mu_Y=E[Y_1],\qquad
\sigma_Y^2=\operatorname{Var}(Y_1).
$$

求期望时要求 $E[|Y_1|]<\infty$；求方差时要求 $E[Y_1^2]<\infty$。给定 $N(t)$，

$$
E[X(t)\mid N(t)]=N(t)\mu_Y,
$$

$$
\operatorname{Var}(X(t)\mid N(t))=N(t)\sigma_Y^2.
$$

由全期望公式，

$$
E[X(t)]=E[N(t)]\mu_Y=\lambda t\mu_Y.
\tag{5.3}
$$

由全方差公式，

$$
\begin{aligned}
\operatorname{Var}(X(t))
&=E[N(t)\sigma_Y^2]
+\operatorname{Var}(N(t)\mu_Y)\\
&=\lambda t\sigma_Y^2+\lambda t\mu_Y^2\\
&=\lambda tE[Y_1^2].
\end{aligned}
\tag{5.4}
$$

第一项来自各次贡献的波动，第二项来自到达次数的波动。即使贡献恒为 $c$，次数仍随机，于是 $\operatorname{Var}(X(t))=c^2\lambda t$。因此在 (5.4) 中需要使用 $Y_1$ 的二阶矩。

### 5.4 独立平稳增量与变换（补充）

不重叠区间的泊松事件数独立，对应的标记也彼此独立，因此复合泊松过程仍有独立增量。由于原过程速率恒定、标记分布不随时间变化，增量分布只依赖区间长度，也具有平稳增量。

若 $M_Y(\theta)=E[e^{\theta Y_1}]$ 在相应 $\theta$ 处有限，对 $N(t)$ 条件化可得

$$
\begin{aligned}
E[e^{\theta X(t)}]
&=E[M_Y(\theta)^{N(t)}]\\
&=\exp\{\lambda t[M_Y(\theta)-1]\}.
\end{aligned}
\tag{5.5}
$$

若矩母函数不存在，特征函数始终可用：

$$
\varphi_{X(t)}(u)
=\exp\{\lambda t[\varphi_Y(u)-1]\}.
$$

这些表达可用于计算分布或证明极限，但期望与方差的推导只需全期望、全方差公式。

## 6 例 5.26（按家庭迁入的人口）

设家庭按每周 $\lambda=2$ 户的泊松速率迁入某地区。各户人口数相互独立，并与家庭到达过程独立。每户人口数为 $1,2,3,4$ 的概率依次为 $1/6,1/3,1/3,1/6$。求固定五周内迁入总人数的期望与方差。

令 $N(t)$ 为 $t$ 周内迁入的家庭数，$Y_i$ 为第 $i$ 户人数，则

$$
X(t)=\sum_{i=1}^{N(t)}Y_i
$$

是累计迁入人数。先计算单户的前两阶矩：

$$
E[Y_i]
=1\cdot\frac16+2\cdot\frac13+3\cdot\frac13+4\cdot\frac16
=\frac52,
$$

$$
E[Y_i^2]
=1^2\cdot\frac16+2^2\cdot\frac13+3^2\cdot\frac13+4^2\cdot\frac16
=\frac{43}{6}.
$$

所以 $\operatorname{Var}(Y_i)=43/6-25/4=11/12$。五周内家庭数 $N(5)\sim\operatorname{Poisson}(10)$，从而

$$
E[X(5)]=2\times5\times\frac52=25,
$$

$$
\operatorname{Var}(X(5))
=2\times5\times\frac{43}{6}
=\frac{215}{3}\approx71.6667.
\tag{6.1}
$$

若错误地只用单户方差，得到 $10\times11/12=55/6$，它仅包含给定家庭数后的波动。缺少的部分为

$$
\operatorname{Var}(N(5))E[Y_i]^2
=10\times\frac{25}{4}=62.5.
$$

同一家庭的人同时进入，所以人数过程允许大于 1 的跳跃；总人数均值为 25，但它不服从 $\operatorname{Poisson}(25)$，方差也不等于 25。

## 7 例 5.27（单服务台忙期）

### 7.1 忙期的定义

考虑一个单服务台系统，顾客按速率 $\lambda$ 的泊松过程到达。空闲时到达的顾客立即接受服务，忙时到达的顾客加入队列。各次服务时间相互独立、同分布，并与到达过程独立。系统只要有人便继续服务。从一位顾客进入空系统起，到系统下一次变空为止，称为一个**忙期**。记其长度为 $B$，求 $E[B]$ 和 $\operatorname{Var}(B)$。

这是 $M/G/1$ 排队系统，其中最后的 1 表示一个服务台。设一个普通服务时间为 $S$，记

$$
m=E[S],\qquad v=\operatorname{Var}(S),\qquad \rho=\lambda m.
$$

要得到有限均值，要求 $m<\infty$ 且 $\rho<1$。要得到有限方差，还要求 $E[S^2]<\infty$。$\rho$ 表示平均工作量到达速率与单位服务能力之比。

第一位顾客的服务过程中还会有新顾客到来。计算忙期时，需要把这些顾客以及他们服务期间继续到来的顾客都计入。

### 7.2 对第一位顾客的服务时间条件化

把第一位顾客开始服务的时刻作为新的时间 0，其服务时长为 $S$。给定 $S=s$，服务期间的到达数为

$$
N(S)\mid S=s\sim\operatorname{Poisson}(\lambda s).
\tag{7.1}
$$

由 (7.1)，服务时间越长，期间到达数的条件均值 $\lambda s$ 越大。若要计算 $N(S)$ 的边缘分布，需再对 $S$ 的分布取平均。

如果 $N(S)=0$，第一位顾客服务结束时系统立即变空，故 $B=S$。

如果 $N(S)=1$，时间 $S$ 时恰有一位顾客等待，之后直到清空的时间具有一个新忙期的分布。因此可写成

$$
B\overset d=S+B_1.
$$

若 $N(S)=n$，第一段服务结束时有 $n$ 人等待。可以把每位等待者和在清理其服务工作量时引入的后续顾客依次处理。每组从一人开始，所需时间具有一个忙期的分布。

只要服务台持续处理等待的工作，服务次序的选择不改变系统清空的时刻。每处理完一组，之后的泊松到达与已处理的工作独立，服务时间也重新独立取值。因而这几组的处理时长可用独立的忙期副本表示。

所以得到分布递推式

$$
B\overset d=S+\sum_{i=1}^{N(S)}B_i,
\tag{7.2}
$$

在 (7.2) 中，可取 $B_i$ 相互独立，且独立于首段服务时间及该段的到达数。首段服务时间 $S$ 与该段到达数 $N(S)$ 的依赖由 (7.1) 给出。

### 7.3 忙期均值

令 $b=E[B]$。给定 $S=s$，式（7.2）中的附加项是次数为 $\operatorname{Poisson}(\lambda s)$、标记为 $B_i$ 的复合泊松随机和，因此

$$
E[B\mid S=s]
=s+\lambda s b=(1+\lambda b)s.
$$

再取期望，

$$
b=(1+\lambda b)m=m+\rho b.
$$

当 $\rho<1$ 时，

$$
E[B]=\frac m{1-\rho}
=\frac{E[S]}{1-\lambda E[S]}.
\tag{7.3}
$$

有限性的依据也可从各代服务工作量看出：初代平均为 $m$，下一代平均为 $m\rho$，此后依次为 $m\rho^2,\ldots$。当 $\rho<1$ 时，几何级数之和为 $m/(1-\rho)$，因此不是在未经验证有限性的情况下随意移项。

### 7.4 忙期方差

记 $V_B=\operatorname{Var}(B)$。给定 $S=s$，首段 $s$ 是常数，附加工作是复合泊松随机和，故

$$
\operatorname{Var}(B\mid S=s)
=\lambda sE[B^2]
=\lambda s(V_B+b^2).
\tag{7.4}
$$

即使给定 $S$，子忙期的个数仍然随机。由复合泊松方差公式，此处的方差取决于 $E[B^2]$。

全方差公式给出

$$
\begin{aligned}
V_B
&=E[\operatorname{Var}(B\mid S)]
+\operatorname{Var}(E[B\mid S])\\
&=\lambda m(V_B+b^2)+(1+\lambda b)^2v\\
&=\rho(V_B+b^2)+(1+\lambda b)^2v.
\end{aligned}
$$

由 $b=m/(1-\rho)$ 得

$$
1+\lambda b=\frac1{1-\rho}.
$$

于是

$$
(1-\rho)V_B
=\frac{\rho m^2+v}{(1-\rho)^2},
$$

最终得到

$$
\operatorname{Var}(B)
=\frac{v+\rho m^2}{(1-\rho)^3}
=\frac{\operatorname{Var}(S)+\lambda(E[S])^3}
{(1-\lambda E[S])^3}.
\tag{7.5}
$$

相应二阶矩可写成

$$
E[B^2]=\frac{E[S^2]}{(1-\rho)^3}.
\tag{7.6}
$$

### 7.5 条件与边界情形

若 $\lambda=0$，没有后续到达，忙期就等于一个服务时间；公式相应给出 $E[B]=m$、$\operatorname{Var}(B)=v$。

若服务时间服从 $\operatorname{Exp}(\mu)$，则 $m=1/\mu$、$v=1/\mu^2$，稳定条件为 $\lambda<\mu$，且

$$
E[B]=\frac1{\mu-\lambda},
\qquad
\operatorname{Var}(B)=\frac{\mu+\lambda}{(\mu-\lambda)^3}.
$$

忙期仍一般不服从指数分布；拥有简洁的均值不意味着整个分布无记忆。

当 $\rho\uparrow1$ 时，忙期均值按 $(1-\rho)^{-1}$ 增大，方差中的分母则为 $(1-\rho)^3$。若 $\rho\geq1$，不能继续将式（7.3）解释为有限均值，更不能接受负的“期望时间”。在通常非退化的临界情形，忙期可以几乎必然结束而均值无穷；超临界情形还可能永不结束。

## 8 复合泊松过程的分类表示与正态近似

### 8.1 可数标记下的表示

假设每次标记取有限或可数多个值 $\alpha_j$，且

$$
P(Y_i=\alpha_j)=p_j,\qquad \sum_jp_j=1.
$$

令 $N_j(t)$ 表示截至 $t$ 标记值为 $\alpha_j$ 的事件数。由独立分裂，$N_j$ 是相互独立、速率为 $\lambda p_j$ 的泊松过程。每次这类事件对总量贡献 $\alpha_j$，因此

$$
X(t)=\sum_j\alpha_jN_j(t).
\tag{8.1}
$$

有限 $t$ 时原事件总数有限，只有有限次实际贡献。若要交换期望与无限求和，仍应核对 $E[|Y_1|]<\infty$ 等可积性条件。

利用表示式可再次验证

$$
E[X(t)]=\sum_j\alpha_j\lambda p_jt=\lambda tE[Y_1],
$$

$$
\operatorname{Var}(X(t))
=\sum_j\alpha_j^2\lambda p_jt=\lambda tE[Y_1^2].
$$

课件的标记概率应理解为“任意第 $i$ 次标记取第 $j$ 个可能值”，即 $P(Y_i=\alpha_j)=p_j$；事件编号与标记类别编号是两个不同下标。

### 8.2 复合泊松过程的正态极限

当 $t$ 增大时，总量的均值和方差也随之变化。可以先中心化、标准化，再讨论极限。若

$$
E[|Y_1|]<\infty,
\qquad 0<E[Y_1^2]<\infty,
$$

则

$$
\frac{X(t)-\lambda tE[Y_1]}
{\sqrt{\lambda tE[Y_1^2]}}
\xrightarrow{d}\mathcal N(0,1),
\qquad t\to\infty.
\tag{8.2}
$$

相应的大时间近似为

$$
X(t)\approx
\mathcal N\left(\lambda tE[Y_1],\lambda tE[Y_1^2]\right).
$$

式 (8.2) 所述的极限是对中心化并除以标准差后的变量而言。若标记的二阶矩无限，上述标准化公式不适用。

**证明思路。** 把总时间按单位区间分开，$X(k)-X(k-1)$ 是独立同分布的增量，每个增量均值为 $\lambda E[Y_1]$、方差为 $\lambda E[Y_1^2]$。对整数个增量使用中心极限定理，再证明末尾不足一个单位区间的余项在 $\sqrt t$ 尺度下可以忽略，即得到式（8.2）。这种证明也适用于可数标记；不必把无穷多个近似正态变量不加条件地相加。

### 8.3 二项、泊松与正态分布的关系

以下三个极限分别对应有限均值的稀有事件计数、大均值的泊松计数和大样本二项计数。

**二项到泊松。** 若 $B_n\sim\operatorname{Bin}(n,p_n)$，且

$$
n\to\infty,\qquad p_n\to0,\qquad np_n\to\theta\in(0,\infty),
$$

则 $B_n\xrightarrow d\operatorname{Poisson}(\theta)$。

**泊松到正态。** 若 $K_\theta\sim\operatorname{Poisson}(\theta)$，则

$$
\frac{K_\theta-\theta}{\sqrt\theta}
\xrightarrow d\mathcal N(0,1),\qquad\theta\to\infty.
$$

**二项到正态。** 若 $B_n\sim\operatorname{Bin}(n,p_n)$ 且 $np_n(1-p_n)\to\infty$，则

$$
\frac{B_n-np_n}{\sqrt{np_n(1-p_n)}}
\xrightarrow d\mathcal N(0,1).
$$

固定 $p\in(0,1)$、令 $n\to\infty$ 是第三种情况的常见特例。第一种情况中均值趋于有限常数，第二种情况中均值趋于无穷，它们不能混用。

### 8.4 分布之间的关系

![常见概率分布的关系](.assets/chap5-note3-distribution-map.png)

图中的关系包括参数取特殊值、独立变量求和、变量变换、参数混合以及极限近似。本章用到的例子包括独立伯努利之和为二项、稀有事件的二项极限为泊松、大均值泊松的标准化极限为正态、同速率独立指数之和为 Gamma，以及 Gamma 混合泊松得到负二项分布。

例如，$\operatorname{Bin}(1,p)$ 与 $\operatorname{Bernoulli}(p)$ 是同一分布。泊松的正态近似则要在均值变大后使用。图中的 Gamma 分布若采用尺度参数，换算到本文的速率记号时应取尺度的倒数。

### 8.5 家庭移民的正态近似（教材补充例）

家庭按每周 2 户的泊松速率迁入。每户人数为 $1,2,3,4$ 的概率依次为 $1/6,1/3,1/3,1/6$，各户人数相互独立，且与到达过程独立。近似求 50 周内至少有 240 人迁入的概率。这是教材例 5.28。

前面已算得 $E[Y]=5/2$、$E[Y^2]=43/6$，所以

$$
E[X(50)]=250,
\qquad
\operatorname{Var}(X(50))=\frac{2150}{3}.
$$

人数为整数，使用连续性校正，

$$
\begin{aligned}
P(X(50)\geq240)
&\approx1-\Phi\left(\frac{239.5-250}{\sqrt{2150/3}}\right)\\
&=\Phi(0.3922)\approx0.6526.
\end{aligned}
$$

这里 $\Phi$ 是标准正态分布函数。近似适用于累计了较多独立贡献的情形；它并未把精确的复合泊松分布变成正态分布。

## 9 条件或混合泊松过程

### 9.1 随机速率的定义

若每天的客流速率在开门前已经确定，但不同天的速率有所变化，怎样求随机选取一天后的到达分布？设 $L$ 是几乎必然有限的非负随机变量。先抽取一次 $L$，并在整条轨迹上保持该速率。给定 $L=\ell$，到达过程为速率 $\ell$ 的齐次泊松过程。

$$
\{N(t),t\geq0\}\mid L=\ell
\sim\text{速率 }\ell\text{ 的泊松过程}.
\tag{9.1}
$$

则称 $N$ 为**条件泊松过程或混合泊松过程**（conditional or mixed Poisson process）。课件取正的 $L$；允许 $L=0$ 时只增加“整条路径无到达”的退化情形。

这样，每一条轨迹内部共享同一个 $L$。由此可从条件模型推导随机选取一条轨迹时的边缘计数分布。

### 9.2 边缘分布是泊松概率的混合

设 $H$ 为 $L$ 的分布，则对 $n=0,1,\ldots$，

$$
P(N(t)=n)
=E\left[e^{-Lt}\frac{(Lt)^n}{n!}\right]
=\int_{[0,\infty)}e^{-\ell t}\frac{(\ell t)^n}{n!}\,dH(\ell).
\tag{9.2}
$$

若 $L$ 有密度 $h$，可把积分写成对 $h(\ell)\,d\ell$ 的普通积分。不能把 $L$ 直接换成 $E[L]$，因为泊松质量函数是 $L$ 的非线性函数。

在有关矩有限时，全期望与全方差公式给出

$$
E[N(t)]=tE[L],
$$

$$
\begin{aligned}
\operatorname{Var}(N(t))
&=E[Lt]+\operatorname{Var}(Lt)\\
&=tE[L]+t^2\operatorname{Var}(L).
\end{aligned}
\tag{9.3}
$$

若 $\operatorname{Var}(L)>0$，则方差严格大于均值。额外的 $t^2\operatorname{Var}(L)$ 来自不同环境之间速率的差异。

### 9.3 平稳增量

给定 $L=\ell$，对任意 $s,t\geq0$，

$$
N(s+t)-N(s)\mid L=\ell
\sim\operatorname{Poisson}(\ell t).
$$

积分掉 $L$ 后，

$$
P(N(s+t)-N(s)=n)
=E\left[e^{-Lt}\frac{(Lt)^n}{n!}\right].
$$

右侧只依赖区间长度 $t$，不依赖起点 $s$，所以混合过程有平稳增量。

### 9.4 不相交区间计数的依赖

取两个不重叠区间，长度分别为 $a,b$，计数记为 $K_1,K_2$。给定 $L$，它们独立，因此

$$
\operatorname{Cov}(K_1,K_2\mid L)=0,
\qquad
E[K_1\mid L]=aL,\quad E[K_2\mid L]=bL.
$$

当 $E[L^2]<\infty$ 时，全协方差公式给出

$$
\begin{aligned}
\operatorname{Cov}(K_1,K_2)
&=E[\operatorname{Cov}(K_1,K_2\mid L)]
+\operatorname{Cov}(aL,bL)\\
&=ab\operatorname{Var}(L).
\end{aligned}
\tag{9.4}
$$

若速率并非常数，该协方差为正，所以增量不独立。直观上，第一个区间出现很多事件，会使“这条路径的潜在速率较高”更有可能，从而也提高另一个区间出现很多事件的可能性。

即使不假设有限二阶矩，也可以用零事件概率看依赖：

$$
P(K_1=0,K_2=0)=E[e^{-(a+b)L}],
$$

$$
P(K_1=0)P(K_2=0)=E[e^{-aL}]E[e^{-bL}],
$$

二者对非退化 $L$ 一般不同。条件独立并不推出无条件独立。

### 9.5 例（两种随机速率）

设每天开始时以各 $1/2$ 的概率选择 $L=1$ 或 $L=3$，单位为每小时，整天保持该速率。给定 $L$，顾客按泊松过程到达。求首小时到达数的均值和方差，以及第一、第二小时到达数之间的协方差。

因为

$$
E[L]=2,\qquad \operatorname{Var}(L)=1,
$$

所以首小时计数的均值为 2，方差为 $2+1=3$；两个小时增量的协方差为 $1\times1\times1=1$。首小时零到达的概率为

$$
\frac12e^{-1}+\frac12e^{-3}\approx0.20883,
$$

而速率固定为平均值 2 的泊松过程，其零到达概率是 $e^{-2}\approx0.13534$。两者均值相同，但分布和依赖结构不同。

### 9.6 Gamma 混合与负二项分布（教材补充）

令随机速率服从形状 $r>0$、速率 $\beta>0$ 的 Gamma 分布：

$$
h(\ell)=\frac{\beta^r}{\Gamma(r)}\ell^{r-1}e^{-\beta\ell},
\qquad \ell>0.
$$

代入式（9.2），

$$
\begin{aligned}
P(N(t)=n)
&=\frac{\beta^rt^n}{n!\Gamma(r)}
\int_0^\infty\ell^{n+r-1}e^{-(\beta+t)\ell}\,d\ell\\
&=\frac{\Gamma(n+r)}{n!\Gamma(r)}
\left(\frac{\beta}{\beta+t}\right)^r
\left(\frac{t}{\beta+t}\right)^n.
\end{aligned}
\tag{9.5}
$$

这是定义在 $n=0,1,\ldots$ 上的负二项分布；当 $r$ 是整数时，可以对应“第 $r$ 次成功前的失败次数”的参数约定。这里直接写出概率质量函数，可以避免不同教材对负二项参数和支持集的不同约定。

其均值、方差为

$$
E[N(t)]=\frac{rt}\beta,
\qquad
\operatorname{Var}(N(t))
=\frac{rt}\beta+\frac{rt^2}{\beta^2}.
$$

作为依赖性的进一步说明，观察到 $N(t)=n$ 后，后验密度正比于

$$
\ell^ne^{-t\ell}\cdot\ell^{r-1}e^{-\beta\ell},
$$

故

$$
L\mid N(t)=n\sim\operatorname{Gamma}(r+n,\beta+t).
$$

下一段长为 $s$ 的区间的条件期望计数为

$$
E[N(t+s)-N(t)\mid N(t)=n]
=s\frac{r+n}{\beta+t}.
\tag{9.6}
$$

它明确依赖过去观测到的 $n$，这正是无条件增量不独立的表现。

## 10 四种模型的比较

| 模型 | 随机对象及参数 | 固定时刻的均值与方差 | 独立增量 | 平稳增量 |
|---|---|---|---|---|
| 齐次泊松 | 次数；固定速率 $\lambda$ | 均为 $\lambda t$ | 有 | 有 |
| 非齐次泊松 | 次数；确定强度 $\lambda(t)$ | 均为 $m(t)$ | 有 | 一般没有 |
| 复合泊松 | 随机贡献之和；速率 $\lambda$、标记 $Y$ | $\lambda tE[Y]$；$\lambda tE[Y^2]$ | 有 | 有 |
| 混合泊松 | 次数；整条路径共享随机速率 $L$ | $tE[L]$；$tE[L]+t^2\operatorname{Var}(L)$ | 一般没有 | 有 |

表中的矩公式均要求相应矩有限。复合过程不一定是计数过程，而混合过程和非齐次过程仍统计单位事件数。

判断题目时，先看它改变了哪一项：若按确定时段改变到达快慢，考虑非齐次；若每次事件带来随机大小，考虑复合；若先随机选择一个环境速率并整段共享，考虑混合。实际模型也可同时具有多个变化，但需要重新写出完整条件，不能只凭“泊松”二字套用某一张公式表。
