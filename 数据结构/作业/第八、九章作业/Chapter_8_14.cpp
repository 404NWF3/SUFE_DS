#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <map>
using namespace std;

const int MaxValue = 2147483647;

// 节点名称NameType，权值类型DistType
template <class NameType, class DistType>
class UndirectedGraph
{
private:
    int VerticesNum, EdgesNum;
    map<NameType, int> NameMap;
    DistType **adj;
    bool Unioned(int i, int j, const vector<int> &UnionFound){
        return Found(i, UnionFound) == Found(j, UnionFound);
    }
    bool ToUnion(int i, int j, vector<int> &UnionFound);
    int Found(int i, const vector<int> &UnionFound);
    void insertEdge(int i, int j, const DistType &d)
    {
        adj[i][j] = d;
    }

    void showResult(const vector<vector<DistType>>& result);

public:
    UndirectedGraph(int size = 4) : VerticesNum(size), EdgesNum(0)
    {
        adj = new DistType *[size];
        for (int i = 0; i < size; i++)
        {
            adj[i] = new DistType[size];
            for (int j = 0; j < size; j++)
                adj[i][j] = MaxValue;
        }
    }

    UndirectedGraph(const vector<NameType> &N)
    {
        int size = N.size();
        VerticesNum = size;
        EdgesNum = 0;
        adj = new DistType *[size];
        for (int i = 0; i < size; i++)
        {
            adj[i] = new DistType[size];
            for (int j = 0; j < size; j++)
                adj[i][j] = MaxValue;
        }

        int i = 0;
        for (const NameType &n : N)
            NameMap[n] = i++;
    }

    ~UndirectedGraph()
    {
        for (int i = 0; i < EdgesNum; i++)
            delete[] adj[i];
        delete[] adj;
    }

    bool insertEdge(const NameType &n1, const NameType &n2, const DistType &d);

    vector<vector<DistType>> Kruskal();
};

template <class NameType, class DistType>
bool UndirectedGraph<NameType, DistType>::insertEdge(const NameType &n1, const NameType &n2, const DistType &d)
{
    int p1 = NameMap[n1];
    int p2 = NameMap[n2];
    if (p1 == -1 || p2 == -1)
        return false;
    if (adj[p1][p2] != MaxValue)
        return false;
    insertEdge(p1, p2, d);
    insertEdge(p2, p1, d);
    return true;
}

template <class NameType, class DistType>
vector<vector<DistType>> UndirectedGraph<NameType, DistType>::Kruskal()
{
    vector<vector<DistType>> result(VerticesNum, vector<DistType>(VerticesNum, MaxValue));
    int EdgeNumInResult = 0;
    // map<NameType, int> NameMap;
    vector<int> UnionFound(VerticesNum);
    for (int i = 0; i < VerticesNum; i++)
        UnionFound[i] = i;

    struct Edge
    {
        int i, j;
        DistType data;
    };
    struct CompareEdge
    {
        bool operator()(const Edge &a, const Edge &b) { return a.data > b.data; }
    };

    // 使用优先级队列找到最小边
    priority_queue<Edge, vector<Edge>, CompareEdge> pq;
    for (int i = 0; i < VerticesNum; i++)
        for (int j = 0; j < i; j++)
            pq.push({i, j, adj[i][j]});

    while (EdgeNumInResult < VerticesNum - 1 && !pq.empty())
    {
        Edge top = pq.top();
        int rootI = Found(top.i, UnionFound);
        int rootJ = Found(top.j, UnionFound);
        if (rootI != rootJ)
        {
            // result中更新边
            result[top.i][top.j] = top.data;
            result[top.j][top.i] = top.data;
            // 更新UnionFound
            UnionFound[rootJ] = rootI;
            EdgeNumInResult++;
        }
        pq.pop();
    }

    showResult(result);
    return result;
}

template <class NameType, class DistType>
int UndirectedGraph<NameType, DistType>::Found(int i, const vector<int> &UnionFound){
    int cur = i;
    do
    {
        cur = UnionFound[cur];
    } while (UnionFound[cur] != cur);
    return cur;
}

template<class NameType, class DistType>
void UndirectedGraph<NameType, DistType>::showResult(const vector<vector<DistType>>& result){
    cout << "Kruskal最小生成树结果：" << endl;
    cout << " \t";
    for (const auto &pair : NameMap)
        cout << pair.first << "\t";
    cout << endl;
    auto pair = NameMap.begin();
    for (int i = 0; i < result.size(); i++)
    {
        cout << (pair++)->first << "\t";
        for (int j = 0; j < result[i].size(); j++)
        {
            if (result[i][j] != MaxValue)
                cout << result[i][j] << "\t";
            else
                cout << "∞\t";
        }
        cout << endl;
    }
}

int main(){
    UndirectedGraph<string, int> graph({"A", "B", "C", "D"});
    graph.insertEdge("A", "B", 1);
    graph.insertEdge("A", "C", 3);
    graph.insertEdge("B", "C", 2);
    graph.insertEdge("B", "D", 4);
    graph.insertEdge("C", "D", 5);

    graph.Kruskal();

    return 0;
}