# 随机过程|笔记整理（D）——鞅的极限性质的应用，布朗运动概述

上一节笔记：

大家好！

从这一节开始，我们结束上一节没说完的，关于鞅的极限性质的一个应用，然后就会正式开始介绍**布朗运动**（Brownian Motion）的相关概念。布朗运动在**[随机微分方程](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E9%9A%8F%E6%9C%BA%E5%BE%AE%E5%88%86%E6%96%B9%E7%A8%8B&zhida_source=entity)**（Stochastic Differential Equations，SDE）内是一个非常重要的前置内容，但是考虑到难度和内容量，在这一部分我们**不会对它做过多地展开**。也就是说我们对布朗运动的介绍**更多像是一个概述**，在不重要的细节上会略有跳过。

那么我们开始吧。

## **目录**

- 鞅的极限性质举例：[波利亚之瓮](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E6%B3%A2%E5%88%A9%E4%BA%9A%E4%B9%8B%E7%93%AE&zhida_source=entity)
- 布朗运动概述
  - 联合概率和条件概率
  - 简单分析性质
  - 伸缩变换
  - 数量性质
  - 离出分布和离出时间

## **鞅的极限性质举例：波利亚之瓮**

**波利亚之瓮**（Polya's Urn）的例子和概率论里的波利亚球的例子是同源的。不过在那里我们介绍的是[条件概率](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=2&q=%E6%9D%A1%E4%BB%B6%E6%A6%82%E7%8E%87&zhida_source=entity)的计算和应用，而这里我们主要是来介绍它关于鞅的一个例子。

> Example 1: Polya's Urn\
> 考虑一个波利亚的瓮，一开始的时候，瓮里有$k$个球，它们中间有红球有蓝球，但是保证这$k$个球里至少有1个红球和1个蓝球。每一次的时候，都会等概率的从中取出一个球，放回之后，再放进这一个颜色的一个球，使得总数变成$k + 1$个。定义$X_n$是红球的占比，那么极限情况下，$X_n$服从什么样的分布？

既然这是一个关于鞅的例子，那么很自然的我们要说明$X_n$是一个鞅。注意到

> $$E(X_{n + 1} | X_0, \ldots, X_n) = (1 - X_n) \frac {(n + k) X_n}{n + 1 + k} + X_n \frac {(n + k) X_n + 1}{n + 1 + k} = X_n$$

这个计算是考虑到在第$n + 1$步的时候，取到红球（概率为$X_n$）和取到蓝球（概率为$1 - X_n$）的情况，然后分别做了一个讨论。如果它是一个鞅，我们上一节有说过，就是它的极限是存在的。当然如果极限不存在，这个问题本身也就站不住脚了，毕竟我们问的就是“极限情况下”的$X_n$的表现。

这个问题讨论起来不是很容易，我们只考虑最简单的情况，也就是一开始整个瓮只有一个红球和一个蓝球的情况，也就是$k = 2, X_0 = \frac 12$。这个时候，首先我们可以知道的是，$X_n$对应的是瓮里有$n + 2$个球的情况，所以这样的话，我们就希望讨论，这个时候有$j$个红球的概率是多少？

如果一开始有1个红球，那么相当于这$n$步操作中，一共有$j - 1$次抽到了红球。但是这里要注意的是，虽然这里的$n$步操作中，在哪$j - 1$次抽到红球我们完全不知道，但是大家如果计算一下就会发现，不管是哪一个情况，对应的概率都是

> $$\frac{1 \cdots (j - 1) \cdot 1 \cdots (n - j + 1)}{2 \cdots (n + 1)}$$

这个如果想清楚逻辑了就是一个非常显然的事情，这里我们画一张$n = 5$的示意图，读者可以借这张图，思考一下这个结论为什么成立？

![img](https://pica.zhimg.com/v2-a889d1696ad6149e9a4d0e1414455c2a_1440w.jpg)

这样之后，我们就能知道

> $$P(X_n = \frac j {n + 2}) = \binom{n }{j -1}\frac{1 \cdots (j - 1) \cdot 1 \cdots (n - j + 1)}{2 \cdots (n + 1)} = \frac 1 {n + 1}$$

这就相当于说，每一个[离散点](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E7%A6%BB%E6%95%A3%E7%82%B9&zhida_source=entity)的概率都是相同的，因此极限状态下这就是一个均匀分布（因为相当于把$[0,1]$区间等分成了$n + 2$份，然后令$n \to \infty$）。这也就说明了$X_\infty \sim U(0, 1)$。

当然了，直观上也确实是一个比较显然的事情，因为一开始就是一个公平的情况，中间等概率也挺公平的，那么算到最后得到一个“公平的”均匀分布，也不是很让人意外。

读者感兴趣其实也可以计算1个红球和2个蓝球的情况，这个时候对应的极限状态下的分布函数为$F(x) = 2x - x^2, 0 < x < 1$。

好的，关于鞅的内容，我们就写到这里。

## **布朗运动概述**

欢迎来到现实世界！现实世界就是这么让人摸不着头脑！

正如上面所说，**布朗运动**（Brownian Motion，又叫**[维纳过程](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E7%BB%B4%E7%BA%B3%E8%BF%87%E7%A8%8B&zhida_source=entity)**，Weiner Process）是一种连续情况下的随机过程，它确实已经很像一些现实生活中的随机现象了。比方说花粉飘在水上的时候所移动的轨迹就是一种布朗运动。

回到正题。布朗运动的严格定义如下。

> Definition 1: Brownian Motion\
> 如果$\{B_t\}_{t \ge 0}$满足\
> (1) $B_0 = 0$\
> (2) $B_t$具备独立增量，也就是说$\forall t_0 < t_1 < \cdots < t_n$，都有$B_{t_1} - B_{t_0}, \ldots, B_{t_n} - B_{t_{n -1}}$独立。\
> (3) $B_t$具备平稳增量，也就是说$B_{t+s} - B_s \sim N(0, \sigma^2 t)$。\
> 则称其是一个方差为$\sigma^2$的布朗运动。

当然如果$\sigma^2 =1$，那么就称它是**[标准布朗运动](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E6%A0%87%E5%87%86%E5%B8%83%E6%9C%97%E8%BF%90%E5%8A%A8&zhida_source=entity)**。我们后面所说的$B_t$，**如果没有特殊说明，或者没有标清楚[方差](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=2&q=%E6%96%B9%E5%B7%AE&zhida_source=entity)，都是标准布朗运动**。

可以看出，其实它和泊松过程是非常相似的，区别就在于离散和连续。所以它也可以理解为是一个马尔科夫链。

当然了，还有一些其它的性质，这里简单叙述。

> Proposition 1:\
> 布朗运动是一个连续时间鞅。

这里“连续时间鞅”的意思就是$E(B_{t_1} | B_s, 0 < s < t) = B_t$。这个很容易验证，注意到

> $$E(B_{t_1} | B_s, 0 \le s \le t) = E(B_{t_1} - B_t + B_t | B_s, 0 \le s \le t)$$
> $$= E(B_{t_1} - B_t) + B_t = B_t$$

一个比较好直观理解布朗运动的方式是把它理解为一种**[随机游走](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E9%9A%8F%E6%9C%BA%E6%B8%B8%E8%B5%B0&zhida_source=entity)的极限**。具体来说，设

> $$S_n = \sum_{i = 1}^n X_k, E(X_k) = 0, D(X_k) = 1$$

那么有一个性质就是$(n \delta, \sqrt {\delta} S_n) \xrightarrow[\delta \to 0]{D}BM$，这里$BM$就是布朗运动的意思，使用[中心极限定理](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E4%B8%AD%E5%BF%83%E6%9E%81%E9%99%90%E5%AE%9A%E7%90%86&zhida_source=entity)，设$n \delta = 1$可以看出来这一点。下面这张图说明了这一点。

![img](https://pica.zhimg.com/v2-7eb5bb1fc711dda901e329be9f6e8be2_1440w.jpg)

左边是一个$S_n$所画出来的图，这里$X_n$可以取正负1且概率相同。右边是一个实际的布朗运动的描述图，可以看出，**两张图还是具有很强的相似度的**。

## **联合概率和条件概率**

布朗运动与[正态分布](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E6%AD%A3%E6%80%81%E5%88%86%E5%B8%83&zhida_source=entity)的紧密联系就暗示了联合概率和条件概率必然会被拿出来说，毕竟多元正态分布在多元统计，[回归分析](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E5%9B%9E%E5%BD%92%E5%88%86%E6%9E%90&zhida_source=entity)里面都是**重中之重的知识点**。

联合概率和条件概率的性质，大概可以描述为下面几个

> Proposition 2:\
> 设$(B_{t_1}, \ldots, B_{t_n})$是多元布朗运动，每一个$B_{t_i}$都是一个那么它是一个[多元正态分布](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=2&q=%E5%A4%9A%E5%85%83%E6%AD%A3%E6%80%81%E5%88%86%E5%B8%83&zhida_source=entity)，[概率密度](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E6%A6%82%E7%8E%87%E5%AF%86%E5%BA%A6&zhida_source=entity)为$$f(x_1 \cdots, x_n) = \prod_{k = 1}^n \frac {\exp(-\frac{(x_k - x_{k - 1})^2}{2(t_k - t_{k - 1})})}{\sqrt {2 \pi (t_k - t_{k - 1})}}, x_0 = t_0 = 0$$，并且均值为0，$Cov(B_s, B_t) = E(B_s B_t) = s \land t$。

这里友情提醒一下，$s \land t = \min(s, t)$。$x_i$对应的就是布朗运动中的$B_{t_i}$。

这个看似是一个很复杂的问题，但是如果利用上增量独立性，就十分显然。注意到

> $$f_{B_{t_1}, \ldots, B_{t_n}}(x_1, \cdots, x_n) = f_{B_{t_1}, B_{t_2} - B_{t_1}, \ldots, B_{t_n} - B_{t_{n - 1}}}(x_1, x_2 - x_1, \cdots, x_n - x_{n - 1})|J|$$

这相当于一个[变量代换](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E5%8F%98%E9%87%8F%E4%BB%A3%E6%8D%A2&zhida_source=entity)

> $$\begin{cases}y_1= x_1 \\ y_2 = x_2 - x_1 \\ y_3 = x_3 - x_2 \\ \ldots \\ y_n = x_n - x_{n - 1}\end{cases}$$

那么很容易看出来，[Jacobi行列式](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=Jacobi%E8%A1%8C%E5%88%97%E5%BC%8F&zhida_source=entity)$|J|$是一个[三角阵](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E4%B8%89%E8%A7%92%E9%98%B5&zhida_source=entity)，所以计算行列式就是把对应的对角线元素相乘，也就是$1$。而写到这里，其实就已经够了，因为增量相互之间独立，所以可以把这个联合密度函数拆开。这其实就对应上了之前密度上所对应的连乘积，这一部分就交给读者完成了。

事实上，通过这个密度函数的分量独立性就应该知道，我们推导$Cov(B_s, B_t)$也肯定是利用独立性，**而不是**通过密度函数的直接计算。事实上，不妨设$s < t$，那么我们有

> $$Cov(B_s, B_t) = Cov(B_s, B_s) = s$$

（这是因为$B_s - B_0 = B_s \sim N(0, \sigma^2 s)$），事实上，如果设$s \ge t$，那么对应的协方差就是$t$，所以最终可以得到$Cov(B_s, B_t) = s \land t$。

说完联合概率密度，再来看看条件概率。

> Proposition 3:\
> 设$s < t$，那么$B_s | B_t \sim N(\frac s t B_t, \frac {s (t - s)} t)$, $B_t | B_s \sim N(B_s, t - s)$

第二个结论挺简单的，第一个结论却不太显然，我们仔细看一下。

对于第二个结论，因为$s < t$，所以老样子，利用独立性，有

> $$B_t | B_s = B_t - B_s + B_s | B_s \sim N(B_s, t - s)$$

当然这里的方差是由$B_t - B_s$带来的，$B_s$作为了条件，所以是一个[常量](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E5%B8%B8%E9%87%8F&zhida_source=entity)。

对于$B_s | B_t$，其实根据结论我们可以反推一下，它的均值是$\frac s t B_t$，所以一个很重要的想法是做一个裂项

> $$B_s = B_s - \frac s t B_t + \frac s t B_t$$

这个裂项自然是为了把一个“常数”$\frac s t B_t$分离出来。

之后的做法其实也很相似了，就是利用增量的独立性，但这里的独立性不太显然。我们补一个小结论

> Lemma 1:\
> 当$s < t$的时候，有$B_s - \frac st B_t$和$B_t$相互独立。

这里要注意到的是，虽然这两个我们说是布朗运动，但同时**它们也只是两个正态分布**。所以要说明独立性，**只需要说明[协方差](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=2&q=%E5%8D%8F%E6%96%B9%E5%B7%AE&zhida_source=entity)为0就可以**，这是概率论里提到过的，正态分布独特的特性。

注意到

> $$Cov(B_t, B_s - \frac s t B_t) = Cov(B_t, B_s) - \frac s t Cov(B_t, B_t) = s - \frac s t t = 0$$

所以这就得到结论了。

有了这个独立性之后，我们知道

> $$Var(B_s - \frac s t B_t) = Var((1- \frac s t) B_s - \frac s t (B_t - B_s))$$
> $$= (1- \frac st)^2 s + \frac {s^2}{t^2}(t - s) = \frac {s ( t-s)} t$$

所以这个条件概率我们也可以得到。

关于这个裂项是怎么考虑到的，下面这一张图有一个大致的解释。

![img](https://pic4.zhimg.com/v2-421b491227998d9e3b14ca7c12af072f_1440w.jpg)

所以这个结论倒也不算是灵光乍现出来的，画张图可以看出，还是与一些几何图像有一定的关联的。一个$B_s$到直线的纵轴距离，确实应该和$B_t$没啥关系。不过这**不太严格**，就当个辅助理解就好了。

## **简单分析性质**

说“简单”的含义是，遇到分析的东西，就妥妥的逃不开纯数的魔爪了（希望学pure math的不要打我……）。因此这里我们只介绍一些直观的结论，而不会介绍其背后的证明。

第一个性质与它的连续性有关系。

> Proposition 4:\
> 布朗运动满足$\sup_{x \ne y} \frac { | f(x) - f(y)|}{| x - y |^\alpha}, \alpha < 1$，这里$f(x) = B_x$。

看似看不明白啥意思，但是如果取$\alpha = 1$，这个结论就可以推导出**可导性**。但是很明显的一个事情是，这个完全也可以推导出**连续性**，因此结合在一起，其实相当于说，布朗运动所形成的曲线**是一条连续的曲线，但是处处不可导**。一个好的例子就是**[威尔斯特拉斯曲线](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E5%A8%81%E5%B0%94%E6%96%AF%E7%89%B9%E6%8B%89%E6%96%AF%E6%9B%B2%E7%BA%BF&zhida_source=entity)**，这一条曲线也具备这样的性质。

事实上，这里的$\alpha$可以理解为是一种**光滑性**的衡量，这里它“处处连续但不可导”，其实就暗示了布朗运动的曲线**崎岖，不光滑**的特性。

第二个性质依然和连续性有关系，但是是站在[实分析](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E5%AE%9E%E5%88%86%E6%9E%90&zhida_source=entity)角度上去说的。如果没有学过实分析，可以跳过这里。

> Proposition 5:\
> 布朗运动具有有限的[二阶变差](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E4%BA%8C%E9%98%B6%E5%8F%98%E5%B7%AE&zhida_source=entity)，但是一阶变差并不有限。

这个结论也不难看出来，注意到

> $$\left < B, B\right >_t = \lim_{\Delta t \to 0}\sum_i (B_{t_{i + 1}} - B_{t_i})^2 = t, a.s.$$

所以自然这是一个有限的数，这里的求和相当于把$[0, t]$这一段时间做了划分，划分成了一串区间，然后再令区间的最大长度$\Delta t$趋于0。因为是实分析的细节，这里不着墨太多。

那么为什么一阶变差是无限的呢？其实也不难，注意到

> $$\sum_i (B_{t_{i + 1}} - B_{t_i})^2 \le \sum_i |B_{t_{i + 1}} - B_{t_i}| \sup (B_{t_{i + 1}} - B_{t_i}) = \Delta t \sum_i |B_{t_{i + 1}} - B_{t_i}|$$

求和就是变差，但是注意到$\Delta t \to 0$，所以变差必须是一个无限的数，否则乘在一起就是0了。

学过实分析的就知道，这个性质其实就说明了布朗运动的**不可导的**性质。

## **[伸缩变换](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=2&q=%E4%BC%B8%E7%BC%A9%E5%8F%98%E6%8D%A2&zhida_source=entity)**

因为我们这里是“布朗运动概述”，所以这里只是列一下这些性质。

> Proposition 6:\
> 设$B_t$是一个布朗运动，那么\
> (1) $\sigma B_t$是一个方差为$\sigma^2$的布朗运动。\
> (2) $B_{ct}$是一个方差为$c$的布朗运动。\
> (3) $\sqrt c B_{t / c}$是一个布朗运动。\
> (4) $t B_{1 /t}$是一个布朗运动。\
> (5) $B_1 - B_{1 -t}$对于$t \in [0, 1]$是一个布朗运动。\
> (6) $- B_t$是一个布朗运动\
> (7) 设$T$是一个停时，那么$X_t = \begin{cases}B_t & t \le T \\ 2 B_T - B_t & t > T\end{cases}$是一个布朗运动。

这些性质要验证都不算困难，除了第7个性质直观来看不是很显然。这里我们画一张图。

![img](https://pic1.zhimg.com/v2-43edf581ee9d73cf091ef83f7fbb7270_1440w.jpg)

可以看出，相当于取了一个$T$，这之前和之后的曲线，相当于是**沿着$B_T$的横轴做了一个[反射变换](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E5%8F%8D%E5%B0%84%E5%8F%98%E6%8D%A2&zhida_source=entity)**。至于为什么要选择一个停时，主要的原因在于**停时的信息只会依赖到这个时间之前的**。也就是说如果$T$只是一个常数，那肯定不会有问题，但如果$T$是一个随机变量，那么这个时候只要保证它**不会影响到之后的增量性质**，那么反射之后得到的东西就依然还是一个布朗运动。

我们到后面会看到，这个性质可以为证明一些布朗运动特有的数量性质提供非常有趣的解法。当然如果有人要问为什么之后的一段看起来并不像是对称的，我只能说，**你手画一个布朗运动试试**……

## **数量性质**

这一部分会相对硬核一些。大白话来说，就是关注**布朗运动究竟会移动到哪里**，毕竟如果只是单纯的理解它的离散情况（一个随机游走过程），那么似乎一个直观的感觉是，布朗运动不会跑的过远。**这些想法合理吗**？这一部分可能没办法特别好的回答，但是介绍的性质，其实也算是很有趣的一些小结论。

第一个性质衡量的是布朗运动最远能够跑到的距离对应的概率。

> Proposition 7:\
> $P(\max_{0 \le s \le t} B_s \ge a) = 2 P(B_t > a), a \ge 0$

（这里个人认为$\ge$和$>$的差距不大，因为布朗运动是连续的。不过这里我是抄的书上的定理，就没改了）

这个性质事实上说明了，在$[0, t]$这一段时间内，其最大值$\ge a$的概率，恰好是最后一个时间上，最大值$ > a$的概率的两倍，相当于说**一段时间的结果可以直接被最后一个点给预测出来**。

这个证明有两个思路，但我们其实都会利用到停时$T_a = \inf \{t \ge 0: B_t = a\}$，那么这样的话，就会有

> $$P(\max_{0 \le s \le t} B_s \ge a) = P(T_a \le t)$$

那么这样的话，就有

> $$P(B_t > a) = P(B_t > a, T_a < t) = P(T_a < t)P(B_t - B_{T_a} > 0 | T_a < t) = \frac 12 P(T_a < t)$$

这就证明结论了。

第一个等号是因为，如果$B_t > a$，那么一定会有$T_a < t$，相当于对于一个事件$A$来说，我添加了一个条件事件$B$，但是它是$A$的子集。[概率论](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=3&q=%E6%A6%82%E7%8E%87%E8%AE%BA&zhida_source=entity)告诉我们，这个时候对应的概率是不变的。

第二个要注意的点是，$B_t - B_{T_a}$本质上就是一个均值为$0$的正态分布，所以[密度函数](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=4&q=%E5%AF%86%E5%BA%A6%E5%87%BD%E6%95%B0&zhida_source=entity)是一个[偶函数](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E5%81%B6%E5%87%BD%E6%95%B0&zhida_source=entity)，因此$P(B_t - B_{T_a} > 0) = \frac 12$。

还有一个证明方法其实就是利用之前的结论，可以注意到

> $$P(\max_{0 \le s \le t} B_s \ge a) = P(\max_{0 \le s \le t} B_s \ge a, B_t > a) + P(\max_{0 \le s \le t} B_s \ge a, B_t \le a)$$
> $$= P(B_t > a) + P(\max_{0 \le s \le t} X_s \ge a, X_t \ge a) = P(B_t > a) + P(X_t \ge a) = 2P(B_t > a)$$

这里的思路其实也是根据已有的结论，活生生的造出一些式子（分$B_t$的取值讨论）。然后注意到$t$是一个常数，当然也就是一个停时，所以用$X_t$作为$B_t$的一个反射（对应Proposition 6的第7个），它依然还是一个布朗运动。这样的话，注意到反射之前和反射之后，**在停时这个点的随机变量情况是一致的**，所以结合连续性，就可以得到最后的结论。

下一个结论关注的是[布朗运动](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=42&q=%E5%B8%83%E6%9C%97%E8%BF%90%E5%8A%A8&zhida_source=entity)过程中的**零点特性**。

> Proposition 8:\
> 设$L_t = \max \{s < t: B_s = 0\}$，则$P(L_t < s) = \frac 2 \pi \arcsin(\sqrt {\frac st})$

这个性质相当于说，给定一个时间点$t$，那么它之前出现零点的最晚的时刻$< s$的概率是**可以计算出来的**，并且是一个[反三角函数](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=1&q=%E5%8F%8D%E4%B8%89%E8%A7%92%E5%87%BD%E6%95%B0&zhida_source=entity)。

这个结论就不是很好证明了，涉及到复杂的推理和计算，不希望的话，可以跳过这一部分细节。

因为$L_t$并不是一个停时（因为最后一个零点出现的位置很明显会**受制于这个时间之后的信息**）。但也正是因为如此，可以给我提供一个转换的思路。换句话说，就是

> $$P(L_t < s) = P(\forall B_r, r \in [s, t], B_r \ne 0) = 2 P(\forall B_r, r \in [s, t], B_r > 0)$$
> $$= 2 P(B_s > 0, B_r > 0, s < r \le t) = 2 P(B _s > 0, W_{r -s} > -B_s, s < r \le t)$$
> $$= 2 P(B_s > 0, W_u > - B_s, 0 < u \le t - s)$$

这里$W_{r -s} = B_r - B_s$。它依然还是一个布朗运动。之后的换元自然就是设$u = t -s$，这里做这样的一个拆分，本质上还是希望利用增量独立性。

拆分完之后，下一个点自然是希望利用独立性。这里的$W_u > -B_s$其实也就是$-W_u < B_s$的意思，而这一步实质上在说，$-W_u$在时间$ t- s$之前都不会超过$B_s$。那么如果利用上之前定义的停时$T_a$，实际上的意思就是

> $$T_{B_s}^{-W} > t - s$$

当然了在这之后，独立性保证了我们还是可以把这个式子拆分看来，只是现在我们只需要把$B_s$看作某一个变量。这样的话，接着上面写，就有

> $$2 P(B_s > 0, W_u > - B_s, 0 < u \le t - s) = 2\int_0^\infty P(T_x^{-W} > t- s) f_{B_s}(x) dx$$
> $$=2 \int_0^\infty (1 - P(T_x^{-W} \le t - s)) \frac 1 {\sqrt {2 \pi s}}e^{-\frac {x^2}{2s}}dx = 1 - 2 \int_0^\infty 2 P(\tilde W_{t - s} > x)\frac 1 {\sqrt {2 \pi s}}e^{-\frac {x^2}{2s}} dx$$

这里的$\tilde W_{t -s}$是首达时间，也是一个布朗运动，并且有$P(T_x^{-W} \le t - s) = 2 P(\tilde W_{t - s} > x)$。

因为现在的[随机变量](https://zhida.zhihu.com/search?content_id=166455426&content_type=Article&match_order=3&q=%E9%9A%8F%E6%9C%BA%E5%8F%
