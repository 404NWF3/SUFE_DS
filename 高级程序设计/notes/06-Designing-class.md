# 第六章：类设计 (Designing Classes) 学习笔记

本章的核心目标是掌握如何定义新的**类 (Classes)**。类不仅能将相关的数据组合在一起，还能定义作用于这些数据的操作。

## 1. 数据的封装：从 Struct 到 Class

### 1.1 结构体 (Structure)
在 C++ 中，最基础的组合数据方式是使用 `struct`。
*   **定义**：将相关的变量（称为字段或成员）组合成一个单一的类型。
*   **访问**：使用点运算符 (`.`) 访问成员。
*   **局限**：结构体主要用于数据的聚合，通常不包含行为（方法），且默认所有成员都是公开的。

**示例 (点坐标)**：
```cpp
struct Point {
    int x;
    int y;
};
// 使用
Point p;
p.x = 2;
p.y = 3;
```

### 1.2 类 (Class)
类是面向对象编程的基础。它与 `struct` 类似，但引入了**可见性控制**和**方法**。
*   **Public (公开)**：对所有客户端可见。通常包含构造函数和方法。
*   **Private (私有)**：仅对类内部可见。通常包含实例变量（数据），以实现**信息隐藏 (Information Hiding)**。
*   **Struct vs Class**：在 C++ 中，两者的唯一区别在于默认访问权限。`struct` 默认为 `public`，`class` 默认为 `private`。

### 1.3 Point 类的演进
为了更好的封装，将 `Point` 定义为类：

```cpp
class Point {
public:
    // 构造函数 (Constructors)
    Point() { x = 0; y = 0; } // 默认构造函数
    Point(int xc, int yc) { x = xc; y = yc; }

    // Getter 方法 (Accessors)
    int getX() { return x; }
    int getY() { return y; }

    // toString 方法 (用于调试和显示)
    string toString() {
        return "(" + integerToString(x) + "," + integerToString(y) + ")";
    }

private:
    // 实例变量 (Instance Variables)
    int x;
    int y;
};
```
*   **构造函数**：与类同名，无返回类型。用于初始化对象。
*   **不可变性 (Immutability)**：如果一个类没有提供修改私有数据的方法（Setter），则该类的对象创建后不可更改。这通常能提高代码的安全性和简单性。

### 1.4 接口与实现的分离
为了创建可复用的组件，通常将类定义分为两个文件：
1.  **接口文件 (`.h`)**：包含类定义、方法原型（Prototypes）。
2.  **实现文件 (`.cpp`)**：包含方法的具体代码。

在 `.cpp` 文件中实现方法时，必须使用**作用域解析运算符 (`::`)** 来指明方法属于哪个类（例如 `int Point::getX() { ... }`）。

---

## 2. 运算符重载 (Operator Overloading)

C++ 允许重新定义标准运算符（如 `+`, `==`, `<<`），使其适用于自定义类型。这能让代码更直观。

### 2.1 重载输出运算符 (`<<`)
为了能直接使用 `cout << point`，需要重载 `<<`。
*   **函数原型**：`ostream & operator<<(ostream & os, Point pt);`
*   **注意**：必须返回 `ostream &` 以支持链式调用（如 `cout << p1 << p2;`）。

```cpp
ostream & operator<<(ostream & os, Point pt) {
    return os << pt.toString();
}
```

### 2.2 重载相等运算符 (`==`)
有两种实现方式：
1.  **成员函数**：作为类的一部分。编译器会将左操作数视为接收者 (Receiver)，右操作数视为参数。
2.  **自由函数 (Free function)**：定义在类外部。为了能访问类的私有变量，需要在类定义中将其声明为 **`friend` (友元)**。

**推荐方式 (自由函数 + friend)**：
这样对待两个操作数更对称（Symmetric）。

**在类定义中 (point.h)**:
```cpp
class Point {
    // ... public methods ...
    friend bool operator==(Point p1, Point p2); // 友元声明
private:
    int x, y;
};
```

**在实现文件中 (point.cpp)**:
```cpp
bool operator==(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y; // 可以直接访问私有成员 x 和 y
}
```

### 2.3 枚举类型的运算符重载
也可以为 `enum` 重载运算符。例如为 `Direction` 枚举重载 `++` 运算符，使其能用于 `for` 循环。
*   **后缀 `++`**：为了区分前缀 (`++d`) 和后缀 (`d++`)，后缀版本的重载函数需要一个额外的 `int` 参数（不使用）。

```cpp
Direction operator++(Direction & dir, int) {
    Direction old = dir;
    dir = Direction(dir + 1); // 需要处理循环回绕等逻辑
    return old;
}
```

---

## 3. 案例研究：有理数类 (Rational Numbers)

本节通过设计一个表示有理数（分数）的类 `Rational`，展示了完整的类设计流程。

### 3.1 设计策略
1.  **从客户端视角出发**：思考用户希望如何使用这个类（例如：`a + b + c` 应该能正常工作）。
2.  **确定私有状态**：需要两个整数 `num` (分子) 和 `den` (分母)。
3.  **定义构造函数**：处理初始化逻辑。
    *   **不变量 (Invariants)**：
        *   分数应始终化简为最简形式 (使用 GCD)。
        *   分母始终为正数 (符号存储在分子中)。
        *   0 表示为 0/1。
4.  **定义公共方法**：算术运算 (`+`, `-`, `*`, `/`)。

### 3.2 实现细节
*   **构造函数**：
    ```cpp
    Rational::Rational(int x, int y) {
        if (y == 0) error("Division by zero");
        int g = gcd(abs(x), abs(y)); // 计算最大公约数用于化简
        num = x / g;
        den = abs(y) / g;
        if (y < 0) num = -num; // 确保分母为正
    }
    ```
*   **算术运算**：重载 `operator+` 等作为友元函数，直接应用数学公式。
    *   例如：$\frac{a}{b} + \frac{c}{d} = \frac{ad + bc}{bd}$
    ```cpp
    Rational operator+(Rational r1, Rational r2) {
        return Rational(r1.num * r2.den + r2.num * r1.den, r1.den * r2.den);
    }
    ```

---

## 4. 案例研究：Token Scanner 类

这是一个处理文本处理的实用工具类，用于将字符串分割成逻辑单元（Token，如单词、数字、运算符）。

### 4.1 客户端需求
*   **输入源**：可以是字符串或文件流 (`setInput`)。
*   **迭代**：检查是否有更多 Token (`hasMoreTokens`)，获取下一个 Token (`nextToken`)。
*   **配置**：忽略空格 (`ignoreWhitespace`)，识别数字 (`scanNumbers`) 等。

### 4.2 接口设计 (TokenScanner)
*   **构造函数**：`TokenScanner(string str);`
*   **核心方法**：
    *   `string nextToken();`：返回下一个逻辑单元。
    *   `void saveToken(string token);`：将 Token 放回流中（这对解析器非常重要）。
*   **实现原理**：内部维护一个缓冲区字符串 (`buffer`) 和一个当前位置索引 (`cp`)。

---

## 5. 将程序封装为类

随着程序变复杂，全局变量和参数传递会变得混乱。一种好的做法是将**整个程序封装为一个类**。

### 5.1 策略
*   将主程序中的**全局变量**或**主要局部变量**转换为类的**实例变量 (Private fields)**。
*   将**辅助函数**转换为类的**私有方法 (Private methods)**。
*   `main` 函数变得非常简单，只需创建一个对象并调用其 `run` 方法。

**示例 (CheckoutLine 模拟)**：
如果不使用类，需要传递 `nServed`, `totalWait` 等多个变量。封装为 `CheckoutLineSimulation` 类后，这些变为类成员，所有方法都可以直接访问它们，无需传参。

```cpp
class CheckoutLineSimulation {
public:
    void runSimulation();
    void printReport();
private:
    int nServed;
    int totalWait;
    // ... 其他状态变量
};

int main() {
    CheckoutLineSimulation simulation;
    simulation.runSimulation();
    simulation.printReport();
    return 0;
}
```

---

## 总结
*   **类 (Class)** 是 C++ 中定义抽象数据类型 (ADT) 的主要机制。
*   **构造函数**负责初始化对象，建立不变量。
*   **私有 (Private)** 部分封装了数据的表示细节，**公开 (Public)** 部分定义了行为接口。
*   **运算符重载**让自定义类型的使用像内置类型一样自然。
*   **友元 (Friend)** 机制允许特定的非成员函数访问类的私有数据。
*   将复杂程序逻辑封装在类中，可以有效管理状态和简化函数签名。