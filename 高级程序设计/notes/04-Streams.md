这份笔记整理自《Programming Abstractions in C++》的第四章：Streams。本章详细介绍了 C++ 中用于管理数据输入输出（I/O）的流（Stream）机制，涵盖了控制台 I/O、文件操作、字符串流以及流类的继承结构。

---

# 第四章：流 (Streams) 学习笔记

## 1. 流的基本概念 (Overview)
*   **定义**：流 (Stream) 是 C++ 用于管理数据从源头（Source）到目的地（Destination）流动的数据结构。
*   **标准流**：`<iostream>` 库定义了三个标准流：
    *   `cin`：标准输入流 (console input)。
    *   `cout`：标准输出流 (console output)。
    *   `cerr`：标准错误流 (error output)。

---

## 2. 格式化输出 (Formatted Output)

### 2.1 插入运算符 `<<`
*   **作用**：将数据插入到输出流中。
*   **特性**：
    *   自动将非字符串类型（如 `int`, `double`）转换为字符串形式。
    *   **链式调用 (Chaining)**：`<<` 运算符返回流本身的引用，允许将多个输出操作连在一起。
        *   示例：`cout << "Total: " << total << endl;`,。

### 2.2 输出操纵符 (Manipulators)
操纵符用于控制输出格式，通常需要包含 `<iomanip>` 库。

| 操纵符 | 描述 | 持久性 |
| :--- | :--- | :--- |
| `endl` | 插入换行符并刷新缓冲区。 | - |
| `setw(n)` | 设置下一个输出字段的宽度为 `n` 个字符（右对齐）。 | **短暂 (Transient)** |
| `left` / `right` | 设置字段左对齐或右对齐。 | **持久 (Persistent)**, |
| `setprecision(n)` | 设置浮点数的精度（位数）。 | 持久 |
| `fixed` | 强制使用定点数表示法（如 3.14）。 | 持久 |
| `scientific` | 强制使用科学计数法（如 3.14E+00）。 | 持久 |
| `setfill(ch)` | 设置用于填充宽度的字符（默认为空格）。 | 持久 |
| `uppercase` | 十六进制或科学计数法中使用大写字母。 | 持久 |

**代码示例**：
```cpp
cout << right << setw(2) << i << setw(8) << result << endl; // 生成对齐的表格列
```

---

## 3. 格式化输入 (Formatted Input)

### 3.1 提取运算符 `>>`
*   **作用**：从输入流中提取格式化数据。
*   **行为**：默认情况下，`>>` 会**跳过起始的空白字符**（空格、Tab、换行），然后读取直到遇到下一个不符合目标类型的字符或空白符。
*   **局限性**：
    *   无法直接读取包含空格的字符串（会在空格处截断）。
    *   错误处理能力弱：如果用户输入非法格式（如在整数位置输入字母），流会进入错误状态，后续读取都会失败。

### 3.2 更好的输入策略
*   **`getline` 函数**：用于读取整行文本，不跳过空白。
*   **Stanford 库 `simpio.h`**：提供了更健壮的输入函数（如 `getInteger`, `getLine`），内部处理了错误检查和缓冲区清理,。

---

## 4. 数据文件 (Data Files)

### 4.1 文件流类
需要包含 `<fstream>` 库。
*   `ifstream` (Input File Stream)：用于从文件读取数据。
*   `ofstream` (Output File Stream)：用于向文件写入数据。

### 4.2 使用文件的步骤-
1.  **声明流变量**：`ifstream infile;`
2.  **打开文件**：`infile.open("filename.txt");`
    *   *注意*：`open` 方法通常接受 C 风格字符串 (`const char*`)，如果是 C++ `string` 对象，需调用 `.c_str()`。
    *   **检查失败**：使用 `infile.fail()` 检查文件是否成功打开。
3.  **传输数据**：使用读取/写入操作。
4.  **关闭文件**：`infile.close();` 断开流与文件的关联。

### 4.3 文件读取策略

#### A. 逐字符读取 (Single Character I/O)
*   **`get()`**：读取并返回下一个字符。
*   **`EOF`**：当到达文件末尾时，`get()` 返回特殊常量 `EOF`（通常为 -1，因此返回值类型为 `int` 而非 `char`）。
*   **`unget()`**：将读取的最后一个字符放回流中。

**模式 (Read-until-EOF)**:
```cpp
char ch;
while (infile.get(ch)) { // 或 while ((ch = infile.get()) != EOF)
    // 处理字符 ch
}
```

#### B. 逐行读取 (Line-oriented I/O)
*   **`getline(stream, stringVal)`**：从流中读取一行文本到字符串变量中，丢弃换行符。

**模式**:
```cpp
string line;
while (getline(infile, line)) {
    // 处理行 line
}
```

#### C. 格式化读取 (Formatted I/O)
*   使用 `>>` 运算符从文件中读取整数、浮点数等。
*   *风险*：对文件格式要求严格，格式错误可能导致循环提前终止或死循环。

---

## 5. 字符串流 (String Streams)

`<sstream>` 库允许将字符串当作流来处理，这对于数据类型转换非常有用。

### 5.1 类型转换应用
*   **`istringstream`**：从字符串读取数据（类似于 `cin`）。
    *   用途：解析字符串，例如将字符串 `"123"` 转换为整数 `123` (`stringToInteger`)。
*   **`ostringstream`**：向字符串写入数据（类似于 `cout`）。
    *   用途：构造字符串，例如将整数 `42` 转换为字符串 `"42"` (`integerToString`)。

**`stringToInteger` 实现示例**:
```cpp
int stringToInteger(string str) {
    istringstream stream(str); // 用 str 初始化流
    int value;
    stream >> value; // 尝试读取整数
    if (stream.fail() || !stream.eof()) { // 检查是否失败或有多余字符
        error("Illegal integer format");
    }
    return value;
}
```

---

## 6. 类层次结构 (Class Hierarchies)

### 6.1 继承关系 (Inheritance)
C++ 的流库采用了面向对象的设计，形成了一个层级结构,：
*   **`ios`**：基类，提供通用的状态检查方法（如 `fail()`, `clear()`, `eof()`）。
*   **`istream` / `ostream`**：分别继承自 `ios`，提供输入 (`>>`, `get`) 和输出 (`<<`, `put`) 功能。
*   **具体实现类**：
    *   `ifstream` 和 `istringstream` 继承自 `istream`。
    *   `ofstream` 和 `ostringstream` 继承自 `ostream`。

### 6.2 继承的意义
*   **多态性 (Polymorphism)**：可以编写通用的函数来处理所有类型的流。
*   **通用接口设计**：在编写处理流的函数时，参数应使用最通用的基类类型（如 `istream &`），而不是具体的 `ifstream &`。这样该函数既可以处理文件流，也可以处理控制台流 (`cin`) 或字符串流-。

**示例：通用复制函数**:
```cpp
// 可以接受 cin/cout, file streams, 或 string streams
void copyStream(istream & is, ostream & os) {
    char ch;
    while (is.get(ch)) {
        os.put(ch);
    }
}
```

### 6.3 多重继承
*   `iostream` 类（如 `fstream` 和 `stringstream`）同时继承自 `istream` 和 `ostream`，支持双向 I/O。

---

## 7. 斯坦福库扩充 (Stanford Libraries)
*   **`simpio.h`**：
    *   `getInteger`, `getReal`, `getLine`：处理用户输入错误，提供重试机制，比原生 `cin >>` 更安全,。
*   **`filelib.h`**：
    *   `promptUserForFile(stream, prompt)`：循环提示用户输入文件名，直到成功打开文件为止。

## 总结
第四章的核心在于理解流作为数据传输的通用抽象。通过掌握标准流操作、文件流的读写模式以及字符串流的转换功能，可以处理各种复杂的 I/O 需求。同时，理解流类的继承体系对于编写通用、可复用的代码至关重要。