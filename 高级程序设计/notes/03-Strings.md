# 第三章：字符串 (Strings) 学习笔记

## 1. 字符串作为抽象值 (Using Strings as Abstract Values)

### 1.1 基本概念
*   **定义**：字符串是字符的序列。例如 `"hello, world"` 是一个包含 12 个字符的序列。
*   **类型**：C++ 在 `<string>` 库中定义了 `string` 类。这与 C 语言中基于字符数组的低级字符串不同，它提供了更高级的抽象。
*   **声明与初始化**：
    ```cpp
    #include <string>
    using namespace std;
    
    string str = "hello, world"; // 使用字符串字面量初始化
    string empty;                // 默认构造函数，初始化为空字符串
    ```

### 1.2 输入与输出 (I/O)
*   **输出**：使用 `<<` 运算符。
*   **输入**：
    *   `cin >> name;`：读取一个单词，**在空白字符（空格、Tab、换行）处停止**。
    *   `getline(cin, name);`：读取整行文本，直到遇到换行符。
    *   `getLine("Prompt: ");`：斯坦福库 `simpio.h` 提供的函数，结合了提示和整行读取，更为方便。

**代码示例 (HelloName.cpp)**：
```cpp
#include <iostream>
#include <string>
#include "simpio.h"
using namespace std;

int main() {
   string name = getLine("Enter your full name: ");
   cout << "Hello, " << name << "!" << endl;
   return 0;
}
```
,

---

## 2. 字符串操作 (String Operations)

`string` 是一个**类 (Class)**，其实例称为**对象 (Object)**。操作通常通过**方法 (Methods)** 调用，使用“接收者语法” (`receiver.name(arguments)`),。

### 2.1 常用方法与运算符表
| 操作 | 语法/方法 | 描述 |
| :--- | :--- | :--- |
| **长度** | `str.length()` | 返回字符串中的字符数。 |
| **连接** | `str1 + str2` | 将两个字符串首尾相连，返回新字符串。 |
| **追加** | `str += s2` | 将 `s2` 追加到 `str` 的末尾。 |
| **比较** | `==`, `!=`, `<`, `>` | 基于**字典序 (Lexicographic order)** 比较字符串 (区分大小写),。 |
| **选择** | `str[k]` | 获取索引 `k` 处的字符 (无边界检查),。 |
| **选择(安全)**| `str.at(k)` | 获取索引 `k` 处的字符 (有边界检查，越界抛异常)。 |
| **子串** | `str.substr(pos, n)` | 从 `pos` 开始提取 `n` 个字符。省略 `n` 则提取到末尾,。 |
| **查找** | `str.find(pattern)` | 返回模式串第一次出现的索引；若未找到返回 `string::npos`,。 |
| **插入** | `str.insert(pos, s2)`| 在 `pos` 位置插入 `s2`。 |
| **替换** | `str.replace(pos,n,s2)`| 将从 `pos` 开始的 `n` 个字符替换为 `s2`。 |

### 2.2 关键模式 (Idiomatic Patterns)

#### 遍历字符串
C++ 中字符串索引从 0 开始。
*   **正向遍历**：
    ```cpp
    for (int i = 0; i < str.length(); i++) {
        // 使用 str[i] 处理每个字符
    }
    ```
   
*   **反向遍历**：
    ```cpp
    for (int i = str.length() - 1; i >= 0; i--) {
        // ...
    }
    ```
   

#### 通过连接构建字符串
```cpp
string result = "";
for (...) {
    result += ch; // 逐个追加字符
}
```


---

## 3. 字符处理库 `<cctype>`

字符串由字符组成，`<cctype>` 提供了处理单个字符的函数。

*   **判断函数 (Predicates)** (返回 `true` 或 `false`):
    *   `isdigit(ch)`: 是否为数字 ('0'-'9')。
    *   `isalpha(ch)`: 是否为字母。
    *   `islower(ch)` / `isupper(ch)`: 是否为小写/大写字母。
    *   `isspace(ch)`: 是否为空白字符 (空格, Tab, 换行等)。
    *   `ispunct(ch)`: 是否为标点符号。
    *   `isalnum(ch)`: 是否为字母或数字。
*   **转换函数**:
    *   `toupper(ch)`: 转大写 (如果不是字母则原样返回)。
    *   `tolower(ch)`: 转小写。

**应用示例**：判断字符串是否表示整数
```cpp
bool isDigitString(string str) {
   if (str.length() == 0) return false;
   for (int i = 0; i < str.length(); i++) {
      if (!isdigit(str[i])) return false;
   }
   return true;
}
```


---

## 4. 修改字符串内容

C++ 中的 `string` 是可变的 (Mutable)。你可以直接修改其中的字符，或者通过函数返回修改后的新字符串。

### 4.1 就地修改 (In-place) vs. 返回新串
*   **就地修改**：直接通过索引赋值 `str[i] = ch;`。
*   **返回新串**：更安全，不影响原字符串。

**示例：将字符串转为大写**
```cpp
string toUpperCase(string str) { // 传值，str 是副本
   string result = "";
   for (int i = 0; i < str.length(); i++) {
      result += toupper(str[i]);
   }
   return result;
}
```


---

## 5. C 风格字符串的遗留问题 (The Legacy of C-style Strings)

C++ 兼容 C 语言，因此存在两种字符串表示：
1.  **C++ `string` 类**：现代、安全、易用。
2.  **C 风格字符串**：字符数组 (`char` array)，也是字符串字面量 (如 `"hello"`) 的存储方式。

### 常见陷阱
*   **字面量相加**：不能直接用 `+` 连接两个字面量。
    *   错误：`string str = "hello" + ", " + "world";` (试图将两个指针相加)。
    *   正确：`string str = string("hello") + ", " + "world";` (显式转换为 `string` 对象)。

### 转换
*   **C++ 到 C**：使用 `str.c_str()` 方法。在旧式库函数需要 C 字符串作为参数时很有用。

---

## 6. 字符串应用案例 (Writing String Applications)

### 6.1 回文检测 (Palindromes)
检查一个字符串正读反读是否相同。
```cpp
bool isPalindrome(string str) {
   for (int i = 0; i < str.length() / 2; i++) {
      if (str[i] != str[str.length() - 1 - i]) {
         return false;
      }
   }
   return true;
}
```
或者利用 `reverse` 函数的优雅实现：
```cpp
bool isPalindrome(string str) {
   return str == reverse(str);
}
```
,

### 6.2 Pig Latin 翻译器
将英语单词转换为 Pig Latin (一种儿童黑话) 的程序。
*   **规则**：
    1.  无元音：保持不变。
    2.  以元音开头：末尾加 "way"。
    3.  以辅音开头：将辅音移到末尾，加 "ay" (例如 "scram" -> "amscray")。
*   **实现思路**：
    *   `findFirstVowel`: 找到第一个元音的位置。
    *   `wordToPigLatin`: 根据元音位置使用 `substr` 切分并重组单词。
    *   `lineToPigLatin`: 解析整行文本，分离单词和标点，逐词翻译,。

---

## 7. Stanford `strlib.h` 库

本书提供的辅助库，补充了标准库的不足,。

| 函数 | 描述 |
| :--- | :--- |
| `integerToString(n)` | 整数转字符串 |
| `stringToInteger(str)` | 字符串转整数 |
| `realToString(d)` | 浮点数转字符串 |
| `stringToReal(str)` | 字符串转浮点数 |
| `toUpperCase(str)` | 返回大写副本 |
| `toLowerCase(str)` | 返回小写副本 |
| `equalsIgnoreCase(s1, s2)` | 忽略大小写比较相等 |
| `startsWith(str, prefix)` | 检查前缀 |
| `endsWith(str, suffix)` | 检查后缀 |
| `trim(str)` | 去除首尾空白字符 |

### 总结
本章展示了从底层的字符操作到高层的字符串抽象的过渡。通过 `string` 类，我们可以忽略底层的内存管理，专注于解决如文本处理、加密、游戏逻辑等实际问题。掌握迭代、子串提取和连接是处理字符串问题的核心技能。