#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 使用递归函数求解八皇后问题(求出所有解)
// 封装函数
vector<vector<string>> solveWrapping(int);
// 递归函数
void solveRecursive(vector<vector<string>> &res, vector<string> &grid, vector<int> &used, int n);

// 使用非递归函数求解八皇后问题(求出所有解)
vector<vector<string>> solveNonRecursive_1(int);
vector<vector<string>> solveNonRecursive(int);

void printSolutions(const vector<vector<string>> &solutions);
bool isValid(vector<string> &grid, int row, int col)
{
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (grid[i][j] == '1')
            return false;

    for (int i = row, j = col; i >= 0 && j < grid.size(); i--, j++)
        if (grid[i][j] == '1')
            return false;

    return true;
}

bool equalSolutions(const vector<vector<string>> &a, const vector<vector<string>> &b)
{
    if (a.size() != b.size())
        return false;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

int main()
{
    auto ansRec = solveWrapping(8);
    auto ansNonRec1 = solveNonRecursive_1(8);
    auto ansNonRec2 = solveNonRecursive(8);

    cout << "递归解数: " << ansRec.size() << ", 非递归解法1数: " << ansNonRec1.size() << endl;
    cout << "两种方法是否一致: " << (equalSolutions(ansRec, ansNonRec1) ? "是" : "否") << endl;

    cout << "递归解数: " << ansRec.size() << ", 非递归解法2数: " << ansNonRec2.size() << endl;
    cout << "两种方法是否一致: " << (equalSolutions(ansRec, ansNonRec2) ? "是" : "否") << endl;

    return 0;
}

void printSolutions(const vector<vector<string>> &solutions)
{
    cout << "一共有 " << solutions.size() << "个解。" << endl;
    for (const auto &solution : solutions)
    {
        for (const auto &row : solution)
            cout << row << endl;
        cout << endl;
    }
}

vector<vector<string>> solveWrapping(int n = 8)
{
    vector<vector<string>> res;
    vector<string> grid(n, string(n, '0'));
    vector<int> used(n);

    solveRecursive(res, grid, used, 0);

    return res;
}

void solveRecursive(vector<vector<string>> &res, vector<string> &grid, vector<int> &used, int n)
{
    if (n == grid.size())
    {
        res.push_back(grid);
        return;
    }
    for (int i = 0; i < used.size(); i++)
    {
        if (!used[i] && isValid(grid, n, i))
        {
            grid[n][i] = '1';
            used[i] = 1;
            solveRecursive(res, grid, used, n + 1);
            grid[n][i] = '0';
            used[i] = 0;
        }
    }
}

vector<vector<string>> solveNonRecursive(int n = 8)
{
    vector<vector<string>> res;
    vector<string> grid(n, string(n, '0'));
    vector<int> used(n);

    struct State
    {
        int row, i;
        bool returning;
    };

    stack<State> callStack;
    callStack.push({0, 0, 0});

    while (!callStack.empty())
    {
        State &cur = callStack.top();

        if (cur.row == n)
        {
            res.push_back(grid);
            callStack.pop();
            continue;
        }

        if (cur.returning)
        {
            grid[cur.row][cur.i] = '0';
            used[cur.i] = 0;
            cur.i++;
            cur.returning = false;
        }

        bool found = false;
        for (; cur.i < n; cur.i++)
        {
            if (!used[cur.i] && isValid(grid, cur.row, cur.i))
            {
                grid[cur.row][cur.i] = '1';
                used[cur.i] = 1;
                cur.returning = true;
                callStack.push({cur.row + 1, 0, 0});
                found = true;
                break;
            }
        }

        if (!found)
            callStack.pop();
    }

    return res;
}

vector<vector<string>> solveNonRecursive_1(int n = 8)
{
    vector<vector<string>> res;
    vector<string> grid(n, string(n, '0'));
    vector<int> used(n);
    struct State
    {
        int level;
        vector<string> grid;
        vector<int> used;
    };
    stack<State> callStack;
    callStack.push({0, grid, used});

    while (!callStack.empty())
    {
        vector<string> cur = callStack.top().grid;
        int cur_level = callStack.top().level;
        vector<int> cur_used = callStack.top().used;
        callStack.pop();

        if (cur_level == grid.size())
        {
            res.push_back(cur);
            continue;
        }

        for (int i = 0; i < cur_used.size(); i++)
        {
            if (!cur_used[i] && isValid(cur, cur_level, i))
            {
                vector<string> next = cur;
                vector<int> next_used = cur_used;
                next[cur_level][i] = '1';
                next_used[i] = 1;
                callStack.push({cur_level + 1, next, next_used});
            }
        }
    }

    return res;
}