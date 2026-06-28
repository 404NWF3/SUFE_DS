#import "homework-template.typ": homework_template, solution

#import "algorithm-block.typ": *

#show: homework_template.with(
  course: [算法设计与分析],
  homework_title: [第 3 次作业],
  student_name: [倪伟丰],
  student_id: [2024110089],
  class_name: [24 大数据 2 班],
  teacher: [韩凯],
  due_date: [2026 年 3 月 19 日],
)
#show: style-algorithm



= 第1题

Draw a depth-first search tree and a breadth-first search tree of the graph in Figure~1. You can start from an arbitrary node while building these trees.


#solution[
  #figure(
    image("1_BFS.png", width: 50%),
    caption: [
      从 $v_1$ 开始的广度优先搜索树 
    ],
  )
    #figure(
    image("1_DFS.png", width: 30%),
    caption: [
      从 $v_1$ 开始的深度优先搜索树 
    ],
  )
]

= 第 2 题

Give a topological ordering of the graph in Figure~2.


#solution[
一个合法的拓扑排序是：$v_6, v_5, v_3, v_1, v_9, v_10, v_8, v_7, v_2, v_4$。
]

= 第 3 题

 (Exercise 3.10 from the textbook) Suppose we are given an undirected graph $G=(V,E)$, and we identify two nodes $v$ and $w$ in $G$. Give an algorithm that computes the number of shortest $v$-$w$ paths in $G$. (The algorithm should not list all the paths; just the number suffices.) The running time of your algorithm should be $O(m+n)$ for a graph with $n$ nodes and $m$ edges.

#solution[
我们使用 BFS 统计从 $v$ 到 $w$ 的最短路径条数。

#algorithm-figure(
  [],
  Function(
    "CountShortestPaths",
    ("G, v, w"),

    For([each vertex $x in V$ ],
      Assign([distance[$x$]], [$infinity$]),
      Assign([count[$x$]], [0]),
      
    ),
    Assign([distance[$v$]], [0]),
    Assign([count[$v$]], [1]),
    Line([Queue $Q$]),
    Line([Q.enqueue(v)]),

    While([Q is not empty],
      Assign([u], [Q.dequeue()]),
      For([each vertex $x$ in $u$.adj],
        If([distance[$x$] = infinity],
          Assign([distance[$x$]], [distance[$u$] + 1]),
          Assign([count[$x$]], [count[$u$]]),
          Line([Q.enqueue(x)]),
        ),
        ElseIf([distance[$x$] = distance[$u$] + 1],
          Assign([count[$x$]], [count[$x$] + count[$u$]]),
        ),
      ),
    ),
    Return([count[$w$]]),
  ),
)
]

#solution[
上述算法的正确性可由 BFS 的分层性质证明。设 $d(x)$ 表示图中从 $v$ 到顶点 $x$ 的最短距离；若 $x$ 不可达，则记为 $infinity$。

首先证明数组 `distance` 是正确的。BFS 会按照与源点距离从小到大的顺序访问各层顶点。当顶点 $x$ 第一次被某个顶点 $u$ 访问到时，算法令 `distance[x] = distance[u] + 1`。由于此时已经存在一条从 $v$ 到 $u$ 的长度为 `distance[u]` 的路径，再接上边 $(u, x)$ 就得到一条从 $v$ 到 $x$ 的长度为 `distance[u] + 1` 的路径，因此可得 $d(x) <= "distance"[x]$。另一方面，如果存在一条更短的从 $v$ 到 $x$ 的路径，那么这条路径上紧邻 $x$ 的前驱顶点必然会在更早的一层被访问，从而 $x$ 应该更早就被发现，这与“$x$ 此时第一次被访问到”矛盾。因此对每个可达顶点都有 `distance[x] = d(x)`；对不可达顶点，`distance[x]` 始终保持为 $infinity$，也同样正确。

接着证明数组 `count` 是正确的。源点 $v$ 到自身的最短路径只有一条，因此初始化 `count[v] = 1` 是正确的。下面按 BFS 层数归纳：假设对所有满足 `distance[u] <= k` 的顶点 $u$，`count[u]` 都已经等于从 $v$ 到 $u$ 的最短路径条数。考虑任意满足 `distance[x] = k + 1` 的顶点 $x$。任意一条从 $v$ 到 $x$ 的最短路径，其倒数第二个顶点必为某个邻接点 $u$，并且满足 `distance[u] = k`；反过来，任意满足 `distance[u] = k` 且与 $x$ 相邻的顶点 $u$，都可以把每一条从 $v$ 到 $u$ 的最短路径后接边 $(u, x)$，得到一条从 $v$ 到 $x$ 的最短路径。算法第一次发现 $x$ 时，将 `count[x]` 设为该前驱的 `count`；之后每遇到一个新的前驱 $u$ 满足 `distance[x] = distance[u] + 1`，就执行 `count[x] += count[u]`。因此，所有能够作为最短路径倒数第二个顶点的前驱都会被恰好计入一次，而不能满足该条件的邻点不会被计入。由归纳假设可知，这些加总起来恰好就是从 $v$ 到 $x$ 的全部最短路径条数。

因此，当 BFS 结束时，`count[w]` 恰好等于从 $v$ 到 $w$ 的最短路径数；如果 $w$ 从 $v$ 不可达，则 `count[w]` 保持为 $0$，这也与题意一致。

上述算法的时间复杂度为 $O(m+n)$。初始化 `distance` 和 `count` 两个数组时，需要对每个顶点访问一次，因此这一部分耗时为 $O(n)$。在 BFS 过程中，每个顶点至多入队一次、出队一次，所以所有队列操作的总时间为 $O(n)$。同时，我们对每个顶点只遍历一次它的邻接表，因此所有邻接表的遍历总时间与边数成正比；由于图是无向图，每条边至多被它的两个端点各检查一次，因此这一部分总耗时为 $O(m)$。综上，算法的总运行时间为 $O(m+n)$。
]

= 第 4 题

(Exercise 3.12 from the textbook) You're helping a group of ethnographers analyze some oral history data they've collected by interviewing members of a village to learn about the lives of people who've lived there over the past two hundred years.

From these interviews, they've learned about a set of $n$ people (all of them now deceased), whom we'll denote $P_1, P_2, dots, P_n$. They've also collected facts about when these people lived relative to one another. Each fact has one of the following two forms:

- For some $i$ and $j$, person $P_i$ died before person $P_j$ was born; or
- for some $i$ and $j$, the life spans of $P_i$ and $P_j$ overlapped at least partially.

Naturally, they're not sure that all these facts are correct; memories are not so good, and a lot of this was passed down by word of mouth. So what they'd like you to determine is whether the data they've collected is at least internally consistent, in the sense that there could have existed a set of people for which all the facts they've learned simultaneously hold. Give an efficient algorithm to do this: either it should produce proposed dates of birth and death for each of the $n$ people so that all the facts hold true, or it should report (correctly) that no such dates can exist---that is, the facts collected by the ethnographers are not internally consistent.


#solution[
 设 $H = (U, F)$ 为表示全部时间约束的有向图。对每个人 $P_i$ 建立两个节点 $B_i$ 与 $D_i$，分别表示其出生事件和死亡事件。若在图中加入一条边 $x -> y$，则表示约束“事件 $x$ 必须严格早于事件 $y$”。

 建图规则如下：

 1. 对每个 $i$，加入边 $B_i -> D_i$，表示每个人都必须先出生后死亡。
 2. 对每条“$P_i$ 死于 $P_j$ 出生之前”的情报，加入边 $D_i -> B_j$。
 3. 对每条“$P_i$ 与 $P_j$ 的生命至少部分重叠”的情报，加入边 $B_i -> D_j$ 和 $B_j -> D_i$。这正对应于 $P_i$ 在 $P_j$ 死亡前出生，且 $P_j$ 在 $P_i$ 死亡前出生。

 #algorithm-figure(
   [],
   Function(
     "CheckConsistency",
     ("n, type-1 facts, type-2 facts"),
     Line([Construct a directed graph $H$ with vertices $B_i, D_i$ for all $1 <= i <= n$]),
     For([each $i = 1, 2, dots, n$],
       Line([add edge $B_i -> D_i$]),
     ),
     For([each type-1 fact $(i, j)$],
       Line([add edge $D_i -> B_j$]),
     ),
     For([each type-2 fact $(i, j)$],
       Line([add edges $B_i -> D_j$ and $B_j -> D_i$]),
     ),
     Assign([$L$], [TopologicalOrder($H$)]),
     If([$L$ does not exist],
       Return([inconsistent]),
     ),
     For([each event $x$ in $L$ in order],
       Assign([$tau(x)$], [the position of $x$ in $L$]),
     ),
     For([each $i = 1, 2, dots, n$],
       Line([output $(tau(B_i), tau(D_i))$]),
     ),
     Return([the constructed dates]),
   ),
 )
]

#solution[
 若拓扑排序失败，则 $H$ 中存在有向环，算法报告不一致；若拓扑排序成功，记 $tau(x)$ 为事件节点 $x$ 在拓扑序中的位置编号，则对每个人 $P_i$ 输出 $(tau(B_i), tau(D_i))$ 即得到一组候选出生和死亡日期。

 下面证明算法正确。

 先证必要性。若算法报告不一致，则拓扑排序失败，因此 $H$ 中存在一个有向环
 $x_1 -> x_2 -> ... -> x_t -> x_1$。
 由边的语义可知，沿环依次必须满足
 $x_1 < x_2 < ... < x_t < x_1$，
 这与严格先后关系的反自反性矛盾。因此，只要 $H$ 中存在环，就不存在任何一组出生和死亡日期能够同时满足全部情报。

 再证充分性。设算法得到的拓扑序为 $L$，并令 $tau(x)$ 表示节点 $x$ 在 $L$ 中的位置。由拓扑序的定义，对任意边 $(x, y) in F$ 都有 $tau(x) < tau(y)$。于是：

 1. 对每个 $i$，由边 $B_i -> D_i$ 得 $tau(B_i) < tau(D_i)$，故 $P_i$ 一定先出生后死亡。
 2. 对每条第一类情报，由边 $D_i -> B_j$ 得 $tau(D_i) < tau(B_j)$，故 $P_i$ 的死亡时间早于 $P_j$ 的出生时间。
 3. 对每条第二类情报，由边 $B_i -> D_j$ 和 $B_j -> D_i$ 得
 $tau(B_i) < tau(D_j)$ 且 $tau(B_j) < tau(D_i)$。
 这正是两个生命区间 $[tau(B_i), tau(D_i)]$ 与 $[tau(B_j), tau(D_j)]$ 至少部分重叠的充要条件。

 综上，拓扑排序失败当且仅当原情报不一致；若拓扑排序成功，则按拓扑序中的位置编号赋值得到的日期一定满足全部约束，因此算法正确。

 最后分析时间复杂度。图中共有 $2n$ 个节点。若第一类情报有 $k$ 条、第二类情报有 $l$ 条，则边数为 $n + k + 2l$。建图需要 $O(n + k + l)$ 时间，拓扑排序需要 $O(|U| + |F|) = O(n + k + l)$ 时间，最后输出所有人的出生和死亡日期需要 $O(n)$ 时间。因此算法总时间复杂度为 $O(n + k + l)$。

]
