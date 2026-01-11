#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int DefaultSize = 10; // 缺省顶点个数

// 前向引用声明
template <class NameType, class DistType>
class Graph;

// 边结点的类定义
template <class DistType>
class EdgeNode
{
    template <class N, class D>
    friend class Graph; // 声明Graph为友元
private:
    int dest;                 // 边的另一顶点位置 (在顶点表中的下标)
    DistType cost;            // 边上的权值
    EdgeNode<DistType> *link; // 边结点后继指针
public:
    EdgeNode() : dest(-1), link(nullptr) {}
    EdgeNode(int d, DistType c) : dest(d), cost(c), link(nullptr) {}
};

// 顶点结点的类定义
template <class NameType, class DistType>
class VertexNode
{
    template <class N, class D>
    friend class Graph; // 声明Graph为友元
private:
    NameType data;           // 顶点名字
    EdgeNode<DistType> *adj; // 出边表的头指针
public:
    VertexNode() : adj(nullptr) {}
    VertexNode(NameType d) : data(d), adj(nullptr) {}
};

// 图的类定义
template <class NameType, class DistType>
class Graph
{
private:
    VertexNode<NameType, DistType> *NodeTable; // 顶点表（各边链表的头结点）
    int VerticesNum;                           // 当前顶点数
    int VerticesMaxNum;                        // 最大顶点数
    int EdgesNum;                              // 当前边数

    // 辅助函数：根据顶点名字获取其在顶点表中的下标
    int GetVertexPos(const NameType &vertex) const
    {
        for (int i = 0; i < VerticesNum; i++)
        {
            if (NodeTable[i].data == vertex)
            {
                return i;
            }
        }
        return -1;
    }

public:
    Graph(int size = DefaultSize); // 构造函数
    ~Graph();                      // 析构函数

    bool GraphEmpty() const { return VerticesNum == 0; }
    bool GraphFull() const { return VerticesNum == VerticesMaxNum; }
    int NumberOfVertices() const { return VerticesNum; }
    int NumberOfEdges() const { return EdgesNum; }

    DistType GetWeight(const NameType &v1, const NameType &v2); // 返回边上的权值
    int GetFirstNeighbor(int v);                                // 取顶点v的第一个邻接顶点下标
    int GetNextNeighbor(int v1, int v2);                        // 取顶点v1的某邻接顶点v2的下一个邻接顶点下标

    bool InsertVertex(const NameType &vertex);                                // 在图中插入一个新顶点
    bool InsertEdge(const NameType &v1, const NameType &v2, DistType weight); // 在图中插入一条新边

    bool RemoveVertex(const NameType &vertex);               // 在图中删除一个顶点
    bool RemoveEdge(const NameType &v1, const NameType &v2); // 在图中删除一条边

    void PrintGraph(); // 打印图结构

    // 修改：参数顺序改为 (起点, 终点)，符合直觉
    // void dfs(const NameType &startNode, const NameType &endNode);
    // void dfsNonrecursive(const NameType &startNode, const NameType &endNode);
    vector<NameType> dfsTraverse(const NameType &startNode);

    void displayTrack(const vector<NameType> &track);

private:
    // 递归查找路径：u 是当前节点下标，target 是目标节点值
    // bool dfsRecursive(const NameType &target, int u, vector<NameType> &track, vector<bool> &visited);
};

// 构造函数
template <class NameType, class DistType>
Graph<NameType, DistType>::Graph(int size)
{
    VerticesNum = 0;
    EdgesNum = 0;
    VerticesMaxNum = size;
    NodeTable = new VertexNode<NameType, DistType>[size];
}

// 析构函数
template <class NameType, class DistType>
Graph<NameType, DistType>::~Graph()
{
    for (int i = 0; i < VerticesNum; i++)
    {
        EdgeNode<DistType> *p = NodeTable[i].adj;
        while (p != nullptr)
        {
            EdgeNode<DistType> *q = p;
            p = p->link;
            delete q;
        }
    }
    delete[] NodeTable;
}

template <class NameType, class DistType>
DistType Graph<NameType, DistType>::GetWeight(const NameType &v1, const NameType &v2)
{
    int p1 = GetVertexPos(v1);
    int p2 = GetVertexPos(v2);

    if (p1 == -1 || p2 == -1)
        return 0;
    EdgeNode<DistType> *p = NodeTable[p1].adj;

    while (p != nullptr)
    {
        if (p->dest == p2)
            return p->cost;

        p = p->link;
    }
    return 0;
}

// 找到第v个节点的第一个邻接点的下表
template <class NameType, class DistType>
int Graph<NameType, DistType>::GetFirstNeighbor(int v)
{
    if (v != -1 && NodeTable[v].adj)
        return NodeTable[v].adj->dest;
    return -1;
}

// 找到v1节点的某个邻接点v2的下一个邻接点的下标
template <class NameType, class DistType>
int Graph<NameType, DistType>::GetNextNeighbor(int v1, int v2)
{
    if (v1 == -1)
        return -1;

    EdgeNode<DistType> *p = NodeTable[v1].adj;
    while (p)
    {
        if (p->dest == v2 && p->link)
            return p->link->dest;
        p = p->link;
    }
    return -1;
}

template <class NameType, class DistType>
bool Graph<NameType, DistType>::InsertVertex(const NameType &vertex)
{
    if (GraphFull())
        return false;
    NodeTable[VerticesNum].data = vertex;
    NodeTable[VerticesNum++].adj = nullptr;
    return true;
}

template <class NameType, class DistType>
bool Graph<NameType, DistType>::InsertEdge(const NameType &v1, const NameType &v2, DistType weight)
{
    int p1 = GetVertexPos(v1);
    int p2 = GetVertexPos(v2);
    if (p1 == -1 || p2 == -1)
        return false;

    EdgeNode<DistType> *p = NodeTable[p1].adj;
    while (p)
    {
        if (p->dest == p2)
        {
            p->cost = weight;
            return true;
        }
        p = p->link;
    }

    EdgeNode<DistType> *newEdge = new EdgeNode<DistType>(p2, weight);
    newEdge->link = NodeTable[p1].adj;
    NodeTable[p1].adj = newEdge;
    EdgesNum++;
    return true;
}

template <class NameType, class DistType>
bool Graph<NameType, DistType>::RemoveEdge(const NameType &v1, const NameType &v2)
{
    int p1 = GetVertexPos(v1), p2 = GetVertexPos(v2);

    if (p1 == -1 || p2 == -1)
        return false;

    EdgeNode<DistType> *p = NodeTable[p1].adj;
    EdgeNode<DistType> *q = nullptr; // p的前驱

    while (p && p->dest != p2)
    {
        q = p;
        p = p->link;
    }
    if (!p)
        return false;
    if (!q)
        NodeTable[p1].adj = p->link;
    else
        q->link = p->link;
    if (p)
        delete p;
    EdgesNum--;
    return true;
}

template <class NameType, class DistType>
bool Graph<NameType, DistType>::RemoveVertex(const NameType &vertex)
{
    int pos = GetVertexPos(vertex);
    if (pos == -1)
        return false;

    // 1. 删除从该顶点出发的所有边
    EdgeNode<DistType> *p = NodeTable[pos].adj;
    while (p)
    {
        EdgeNode<DistType> *q = p;
        p = p->link;
        delete q;
        EdgesNum--;
    }
    NodeTable[pos].adj = nullptr;

    // 2. 遍历整个图，删除指向该顶点的边，并更新受影响的索引
    // 这是一个关键步骤：因为删除了一个顶点，后面的顶点索引会前移，
    // 所以所有指向 >pos 的边的 dest 都要减 1
    for (int i = 0; i < VerticesNum; i++)
    {
        if (i == pos)
            continue; // 跳过被删除的行

        EdgeNode<DistType> *curr = NodeTable[i].adj;
        EdgeNode<DistType> *prev = nullptr;

        while (curr)
        {
            if (curr->dest == pos)
            {
                // 删除指向被删顶点的边
                if (prev == nullptr)
                {
                    NodeTable[i].adj = curr->link;
                    delete curr;
                    curr = NodeTable[i].adj;
                }
                else
                {
                    prev->link = curr->link;
                    delete curr;
                    curr = prev->link;
                }
                EdgesNum--;
            }
            else
            {
                // 修复：如果指向的顶点在被删顶点之后，索引需要减1
                if (curr->dest > pos)
                {
                    curr->dest--;
                }
                prev = curr;
                curr = curr->link;
            }
        }
    }

    // 3. 移动顶点数组填补空缺
    for (int i = pos; i < VerticesNum - 1; i++)
        NodeTable[i] = NodeTable[i + 1];

    NodeTable[VerticesNum - 1].adj = nullptr; // 安全起见清空

    VerticesNum--;
    return true;
}

template <class NameType, class DistType>
void Graph<NameType, DistType>::PrintGraph()
{
    for (int i = 0; i < VerticesNum; i++)
    {
        cout << NodeTable[i].data << " -> ";
        EdgeNode<DistType> *p = NodeTable[i].adj;
        while (p != nullptr)
        {
            cout << "(" << NodeTable[p->dest].data << ", " << p->cost << ") ";
            p = p->link;
        }
        cout << endl;
    }
}

int main()
{
    Graph<char, int> g(10);

    g.InsertVertex('A');
    g.InsertVertex('B');
    g.InsertVertex('C');
    g.InsertVertex('D');

    g.InsertEdge('A', 'B', 10);
    g.InsertEdge('A', 'C', 20);
    g.InsertEdge('B', 'D', 30);
    g.InsertEdge('C', 'D', 40);
    g.InsertEdge('D', 'A', 50); // 有向图

    cout << "\n初始图:" << endl;
    g.PrintGraph();

    // cout << "\n删除A->C" << endl;
    // g.RemoveEdge('A', 'C');
    // g.PrintGraph();

    // cout << "\n删除顶点B" << endl;
    // g.RemoveVertex('B');
    // g.PrintGraph();

    // 遍历：起始点为A
    cout << "\n从A开始DFS遍历:" << endl;
    g.dfsTraverse('A');

    return 0;
}

template <class NameType, class DistType>
vector<NameType> Graph<NameType, DistType>::dfsTraverse(const NameType &startNode)
{
    vector<NameType> res;
    struct state
    {
        int u;
        EdgeNode<DistType> *cur;
    };

    int startPos = GetVertexPos(startNode);
    if (startPos == -1)
    {
        cout << "Start node (" << startNode << ") not found." << endl;
        return {};
    }

    vector<bool> visited(VerticesNum, false);
    stack<state> s;

    s.push({startPos, NodeTable[startPos].adj});
    visited[startPos] = true;
    res.push_back(NodeTable[startPos].data);
    cout << NodeTable[startPos].data << " ";

    while (!s.empty())
    {
        state &top = s.top();
        while (top.cur && visited[top.cur->dest])
            top.cur = top.cur->link;

        if (top.cur)
        {
            int v = top.cur->dest;

            visited[v] = true;
            res.push_back(NodeTable[v].data);
            cout << NodeTable[v].data << " ";

            top.cur = top.cur->link;
            s.push({v, NodeTable[v].adj});
        }
        else
        {
            s.pop();
        }
    }

    return res;
}
