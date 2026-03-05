# 第一章：C++ 概览 (Overview of C++) 学习笔记

## 1. C++ 简介与历史 (Introduction & History)

### 1.1 语言背景
*   **起源**：C++ 是在 C 语言的基础上发展而来的。C 语言由 Dennis Ritchie 于 1972 年在贝尔实验室设计。
*   **演变**：Bjarne Stroustrup 在 20 世纪 80 年代初期开发了 C++，引入了**面向对象编程 (Object-Oriented Paradigm)** 的概念。
*   **范式 (Paradigm)**：
    *   **过程式编程 (Procedural)**：程序由操作数据的过程和函数集合组成（旧秩序）。
    *   **面向对象编程 (Object-Oriented)**：程序被视为包含特性和行为的数据对象的集合（新模型）。
    *   C++ 支持多种范式，包括过程式和面向对象式。

### 1.2 编译过程 (The Compilation Process)
C++ 是编译型语言，执行过程通常分为三个步骤：
1.  **源文件 (Source file)**：程序员编写的文本文件。
2.  **编译 (Compiler)**：将源文件翻译成包含机器语言指令的**目标文件 (Object file)**。
3.  **链接 (Linker)**：将目标文件与库文件结合，生成可执行文件 (Executable file)。

---

## 2. C++ 程序基本结构 (Structure of a C++ Program)

一个典型的 C++ 程序包含注释、库包含、函数原型和主程序。

### 2.1 "Hello World" 示例
这是所有语言学习的起点：

```cpp
/*
 * File: HelloWorld.cpp
 * --------------------
 * 这是一个标准的 C++ 注释块。
 */

#include <iostream> // 库包含 (Library Inclusion)
using namespace std; // 使用标准命名空间

int main() { // 主程序入口
   cout << "hello, world" << endl; // 输出语句
   return 0; // 返回状态码，0 表示成功
}
```

### 2.2 关键组成部分
*   **注释 (Comments)**：编译器会忽略。
    *   多行注释：`/* ... */`
    *   单行注释：`//`
*   **库包含 (Library Inclusions)**：
    *   `#include <iostream>`：引入输入输出流库，提供 `cin` 和 `cout`。
    *   系统库用尖括号 `< >`，用户自定义库通常用引号 `" "`。
*   **命名空间 (Namespaces)**：
    *   标准库使用 `std` 命名空间。
    *   `using namespace std;` 允许直接使用 `cout` 而不是 `std::cout`。
*   **主函数 (Main Function)**：
    *   所有 C++ 程序必须有一个名为 `main` 的函数，它是程序的执行起点。
    *   `return 0;` 按照惯例表示程序成功结束。

### 2.3 函数原型 (Function Prototypes)
在调用函数之前，必须先声明它。**原型 (Prototype)** 是函数定义的缩略形式（函数头+分号），告诉编译器函数的参数和返回类型。

**示例代码 (PowersOfTwo.cpp 片段)**：
```cpp
/* 函数原型 */
int raiseToPower(int n, int k);

/* 主程序 */
int main() {
    // ... 可以调用 raiseToPower，即使定义在后面 ...
    int val = raiseToPower(2, 3);
    return 0;
}

/* 函数定义 */
int raiseToPower(int n, int k) {
    // ... 具体实现 ...
}
```

---

## 3. 变量与常量 (Variables & Constants)

### 3.1 变量声明
*   **语法**：`type namelist;` (例如: `int limit;` 或 `double n1, n2, n3;`)。
*   **初始化**：变量在声明时可以被初始化，例如 `int result = 1;`。
*   **作用域 (Scope)**：
    *   **局部变量 (Local)**：在函数体内声明，仅在该函数内有效。
    *   **全局变量 (Global)**：在函数体外声明，极其不推荐使用（常量除外）。

### 3.2 命名规则 (Identifiers)
*   必须以字母或下划线开头。
*   只能包含字母、数字和下划线。
*   区分大小写 (ABC 不同于 abc)。
*   **惯例**：变量名小写开头 (e.g., `limit`)，常量全大写 (e.g., `PI`)。

### 3.3 常量 (Constants)
使用 `const` 关键字声明，值不可修改。推荐使用常量代替“魔术数字”以提高可读性和可维护性。

```cpp
const double PI = 3.14159265358979323846;
```

---

## 4. 数据类型 (Data Types)

C++ 定义了基本类型 (Atomic/Primitive types) 和复合类型。

### 4.1 基本类型
*   **整数 (Integer)**：
    *   `int` (标准整数，至少 16 位，现代机器通常更大)。
    *   `short`, `long` (不同范围的整数)。
    *   范围大小关系：`short` <= `int` <= `long`。
*   **浮点数 (Floating-point)**：
    *   `double` (双精度，标准用法)。
    *   `float` (单精度)。
    *   写法：`2.0` 或科学计数法 `3.0E+8`。
*   **布尔型 (Boolean)**：
    *   `bool`，取值为 `true` 或 `false`。
*   **字符 (Character)**：
    *   `char`，存储单个字符的 ASCII 码。
    *   常量用单引号，如 `'A'`。转义字符如 `\n` (换行)。

### 4.2 字符串 (Strings)
*   **类型**：`string` (需要 `#include <string>`)。
*   区别于 C 语言的字符数组，C++ 的 string 是一个库类型，更易用。
*   常量用双引号，如 `"hello"`。

### 4.3 枚举 (Enumerated types)
允许定义由标识符列表组成的新类型。
```cpp
enum Direction { NORTH, EAST, SOUTH, WEST };
// 默认 NORTH=0, EAST=1... 也可以手动赋值
```

---

## 5. 运算符与表达式 (Expressions)

### 5.1 算术运算符
*   `+`, `-`, `*`, `/`。
*   **整数除法**：如果两个操作数都是整数，`/` 执行截断除法 (5 / 2 = 2)。
*   **取余运算符 (%)**：返回除法的余数 (9 % 4 = 1)。

### 5.2 赋值与简写
*   赋值：`=` (将右边的值赋给左边)。
*   简写运算：`x += y` 等同于 `x = x + y` (同样适用于 `-=`, `*=`, `/=`, `%=`)。
*   **自增/自减**：
    *   `x++` (后置)：先返回值，再加 1。
    *   `++x` (前置)：先加 1，再返回值。

### 5.3 布尔运算符
*   **关系运算**：`==` (等于), `!=` (不等于), `>`, `<`, `>=`, `<=`。
    *   *注意*：不要将 `==` (比较) 误写为 `=` (赋值)。
*   **逻辑运算**：
    *   `!` (非/NOT)
    *   `&&` (与/AND) - 具有**短路求值 (Short-circuit evaluation)** 特性：如果左侧为假，不计算右侧。
    *   `||` (或/OR) - 如果左侧为真，不计算右侧。
*   **三元运算符**：`(condition) ? exp1 : exp2`。

---

## 6. 控制流语句 (Statements)

### 6.1 条件语句
*   **if 语句**：
    ```cpp
    if (condition) {
        // statements
    } else {
        // statements
    }
    ```
*   **switch 语句**：用于多分支选择（通常用于枚举或字符）。必须在每个 case 后加 `break`，否则会发生“贯穿 (fall-through)”。

### 6.2 循环语句
*   **while 循环**：先判断再执行。
*   **for 循环**：`for (init; test; step)`。
    ```cpp
    for (int i = 0; i < n; i++) { ... }
    ```
*   **"循环半"问题 (Loop-and-a-half)**：
    有些循环的退出条件在循环体中间。C++ 中常用的模式是 `while (true)` 配合 `break`。
    
    **代码模式 (Read-until-sentinel pattern)**：
    ```cpp
    while (true) {
        // 提示并读取输入
        cout << "Enter value: ";
        int val;
        cin >> val;
        if (val == SENTINEL) break; // 哨兵值退出
        // 处理数据
    }
    ```

---

## 7. Stanford C++ 库简介 (Stanford Libraries)

为了简化教学，本书提供了一套斯坦福定制库。

*   **头文件**：使用引号包含，如 `#include "simpio.h"`。
*   **console.h**：创建一个控制台窗口，方便查看输出。
*   **simpio.h**：简化用户输入，处理输入错误。
    *   `getInteger("Prompt: ")`：读取整数。
    *   `getReal("Prompt: ")`：读取浮点数。
    *   `getLine("Prompt: ")`：读取一行字符串。

**对比示例 (读取整数)**：
*   **标准 C++**:
    ```cpp
    int n;
    cout << "Enter n: ";
    cin >> n; // 需要处理非数字输入的错误，较麻烦
    ```
*   **Stanford 库**:
    ```cpp
    #include "simpio.h"
    int n = getInteger("Enter n: "); // 自动处理错误并重新提示
    ```

---

## 总结 (Summary)
C++ 是一种强类型、编译型语言，结合了高效的底层操作（继承自 C）和高级的抽象能力（类和库）。第一章重点在于掌握基础语法结构、变量类型、表达式规则以及控制流，特别是如何利用库（如 `iostream` 和 Stanford 库）进行基本的输入输出操作。