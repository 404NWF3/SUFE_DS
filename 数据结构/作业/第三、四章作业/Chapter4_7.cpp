#include <iostream>
#include <stack>
using namespace std;

class Expression
{
private:
    string expr;
    stack<int> values;
    stack<char> ops;

    void showStacks()
    {
        cout << "操作数栈: ";
        stack<int> tempValues = values;
        while (!tempValues.empty())
        {
            cout << tempValues.top() << " ";
            tempValues.pop();
        }
        cout << endl;

        cout << "操作符栈: ";
        stack<char> tempOps = ops;
        while (!tempOps.empty())
        {
            cout << tempOps.top() << " ";
            tempOps.pop();
        }
        cout << endl;
    }
    int applyOp(int a, int b, char op)
    {
        switch (op)
        {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        }
        return 0;
    }
    int precedence(char op)
    {
        if (op == '+' || op == '-')
            return 3;
        if (op == '*' || op == '/')
            return 2;
        if (op == '(')
            return 999; // 特殊处理，永不弹出直到遇到
        return INT_MAX;
    }
    int stringToInt(const string &s)
    {
        int res = 0;
        for (char c : s)
        {
            res *= 10;
            res += c - '0';
        }
        return res;
    }

public:
    Expression(const string &i) : expr(i) {};
    int solve();
};

int Expression::solve()
{
    cout << endl;
    cout << "表达式: " << expr << "\n\n";
    for (int i = 0; i < expr.length(); i++)
    {
        // 1. 数字，读出多位数字后进入操作数栈
        if (isdigit(expr[i]))
        {
            string num_string = "";
            while (i < expr.length() && isdigit(expr[i]))
                num_string += expr[i++];
            i--;
            int cur = stringToInt(num_string);
            values.push(cur);
            cout << "读取到数字: " << cur << endl;
            showStacks();
        }

        // 2. 左括号直接进栈
        else if (expr[i] == '(')
        {
            ops.push(expr[i]);
            cout << "读取到左括号: " << expr[i] << endl;
            showStacks();
        }
        // 3. 右括号则开始计算，直到读到左括号
        else if (expr[i] == ')')
        {
            // char op = ops.top();
            // ops.pop();
            while (!ops.empty() && ops.top() != '(')
            {
                char op = ops.top();
                ops.pop();
                int b = values.top();
                values.pop();
                int a = values.top();
                values.pop();
                int res = applyOp(a, b, op);
                cout << "计算 " << a << op << b << " = " << res << endl;
                values.push(res);
                showStacks();
            }
            ops.pop();
            showStacks();
        }

        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/')
        {
            cout << "读取到操作符" << expr[i] << " ，优先级为" << precedence(expr[i]) << endl;
            while (!ops.empty() && precedence(ops.top()) <= precedence(expr[i]) && ops.top() != '(')
            {
                char op = ops.top();
                ops.pop();
                cout << "操作符栈顶操作符为" << op << " ，优先级为" << precedence(op) << endl;

                int b = values.top();
                values.pop();
                int a = values.top();
                values.pop();
                int res = applyOp(a, b, op);
                cout << "先计算 " << a << op << b << " = " << res << endl;
                values.push(res);

                showStacks();
            }
            ops.push(expr[i]);
            cout << "操作符" << expr[i] << "进栈" << endl;
            showStacks();
        }
    }

    // 处理剩余表达式
    cout << "表达式读取完毕，处理剩余运算" << endl;
    while (!ops.empty())
    {
        char op = ops.top();
        ops.pop();
        int b = values.top();
        values.pop();
        int a = values.top();
        values.pop();
        int res = applyOp(a, b, op);
        cout << "计算 " << a << op << b << " = " << res << endl;
        values.push(res);
        showStacks();
    }

    return values.top();
}

string getExpression(int a, int b, int c, int d, int e)
{
    string expr = "a-b*(c+d)/e+5";
    string res = "";
    for (char &ch : expr)
    {
        if (ch == 'a')
            res += to_string(a);
        else if (ch == 'b')
            res += to_string(b);
        else if (ch == 'c')
            res += to_string(c);
        else if (ch == 'd')
            res += to_string(d);
        else if (ch == 'e')
            res += to_string(e);
        else
            res += ch;
    }
    return res;
}

int main()
{
    int a = 10, b = 2, c = 3, d = 4, e = 7;
    // cin >> a >> b >> c >> d >> e;
    string input = getExpression(a, b, c, d, e);
    Expression expression(input);
    int result = expression.solve();
    cout << "Expression: " << input << endl;
    cout << "Result: " << result << endl;
    return 0;
}
