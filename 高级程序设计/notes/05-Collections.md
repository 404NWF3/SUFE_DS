# 第五章：集合 (Collections) 学习笔记

## 1. 概述与基础
*   **集合类 (Collection Classes)**：用于存储一组数据的对象。
*   **模板 (Templates)**：C++ 使用模板来定义通用的容器。
    *   语法：`CollectionType<ElementType>`。
    *   例如：`Vector<int>` 表示整数向量，`Map<string, int>` 表示键为字符串、值为整数的映射。
*   **抽象数据类型 (ADT)**：由其**行为**（操作）而非其**实现**（底层数据结构）定义的类型。这提供了简单性（隐藏细节）、灵活性（易于更改实现）和安全性（防止错误修改）。

---

## 2. 线性结构 (Linear Structures)

### 2.1 Vector (向量)
`Vector` 是数组的现代替代品，它是动态的（大小可变）且安全的（提供边界检查）。

*   **概念**：有序的元素序列，通过索引访问。
*   **核心接口 (Interface)**：
    *   **构造**：
        *   `Vector<T> vec;` (空向量)
        *   `Vector<T> vec(n, value);` (包含 n 个 value 的向量)
    *   **添加/删除**：
        *   `vec.add(value)`: 在末尾添加元素。
        *   `vec.insertAt(index, value)`: 在指定索引插入，后续元素后移。
        *   `vec.removeAt(index)`: 删除指定索引元素，后续元素前移。
    *   **访问/修改**：
        *   `vec.get(index)`: 返回索引处的元素 (带边界检查)。
        *   `vec.set(index, value)`: 修改索引处的元素。
        *   `vec[index]`: **运算符重载**，允许像数组一样使用下标访问和修改，且比原生数组更安全（越界会报错）。
    *   **状态**：
        *   `vec.size()`: 返回元素个数。
        *   `vec.isEmpty()`: 判断是否为空。
        *   `vec.clear()`: 清空向量。
    *   **操作符**：
        *   `v1 + v2`: 连接两个向量。
        *   `v1 += val`: 将 val 追加到 v1 末尾。

> **Grid (网格)**: Stanford 库特有的类，用于表示二维数组。
> *   `grid[row][col]`: 访问元素。
> *   `grid.resize(rows, cols)`: 重置大小。
> *   `grid.inBounds(row, col)`: 检查坐标是否有效。

### 2.2 Stack (栈)
*   **概念**：遵循 **LIFO (Last-In, First-Out，后进先出)** 原则。就像叠盘子，最后放上去的必须最先拿下来。
*   **典型应用**：函数调用栈、计算器（后缀表达式）、撤销操作。
*   **核心接口 (Interface)**：
    *   `stack.push(value)`: 将元素压入栈顶。
    *   `stack.pop()`: 移除并返回栈顶元素。
    *   `stack.peek()`: 返回栈顶元素但不移除。
    *   `stack.size()` / `stack.isEmpty()` / `stack.clear()`: 状态查询与清空。
*   **限制**：只能访问栈顶元素，不能遍历（除非弹空）。

### 2.3 Queue (队列)
*   **概念**：遵循 **FIFO (First-In, First-Out，先进先出)** 原则。就像排队买票。
*   **典型应用**：任务调度、缓冲处理、模拟排队系统。
*   **核心接口 (Interface)**：
    *   `queue.enqueue(value)`: 将元素添加到队尾 (Tail)。
    *   `queue.dequeue()`: 移除并返回队首 (Head) 元素。
    *   `queue.peek()`: 返回队首元素但不移除。
    *   `queue.size()` / `queue.isEmpty()` / `queue.clear()`。

---

## 3. 关联结构 (Associative Structures)

### 3.1 Map (映射)
这是本章最强大的工具之一，类似于字典或关联数组。

*   **概念**：存储 **键-值对 (Key-Value pairs)**。键 (Key) 是唯一的，用于查找对应的值 (Value)。
*   **核心接口 (Interface)**：
    *   `map.put(key, value)`: 建立映射。如果键已存在，覆盖旧值。
    *   `map.get(key)`: 返回与键关联的值。如果键不存在，通常会报错。
    *   `map.containsKey(key)`: 检查键是否存在（返回 bool）。
    *   `map.remove(key)`: 删除键及其对应的值。
    *   `map.size()` / `map.isEmpty()` / `map.clear()`。
*   **运算符重载 (Associative Array Syntax)**：
    *   `map[key]`: 可以像数组一样使用。
    *   **重要特性**：如果 `key` 不存在，使用 `map[key]` 会**自动创建**一个该键的条目，并将值初始化为默认值（如 int 为 0, string 为 ""）。
    *   示例：`counts[word]++;` (如果 word 不存在，先创建并设为 0，然后加 1)。

### 3.2 Set (集合)
*   **概念**：数学意义上的集合。存储**不重复**的元素，且无序（但在 C++ 实现中，遍历通常是有序的）。
*   **核心接口 (Interface)**：
    *   `set.add(value)`: 添加元素。如果已存在，则无操作。
    *   `set.contains(value)`: 检查元素是否存在。
    *   `set.remove(value)`: 删除元素。
    *   `set.isSubsetOf(otherSet)`: 判断子集关系。
*   **高级集合运算 (High-level Operators)**：
    *   `s1 + s2`: **并集 (Union)** (A ∪ B)。
    *   `s1 * s2`: **交集 (Intersection)** (A ∩ B)。
    *   `s1 - s2`: **差集 (Difference)** (A - B)。
    *   支持 `+=`, `*=`, `-=` 操作。

> **Lexicon (词库)**: 专门用于存储单词列表的高效集合。
> *   `lex.contains(word)`: 检查单词是否存在。
> *   `lex.containsPrefix(prefix)`: **特有功能**，检查是否存在以 prefix 开头的单词（对拼字游戏等应用非常高效）。

---

## 4. 迭代 (Iteration)

如何遍历这些集合？C++ 提供了 `foreach` 模式（在斯坦福库中通过宏实现，类似现代 C++ 的 range-based for）。

*   **语法**：
    ```cpp
    for (Type variable : collection) {
        // 处理 variable
    }
    ```
*   **遍历顺序 (Iteration Order)**：
    *   **Vector**: 按索引顺序 (0 到 size-1)。
    *   **Grid**: 行优先顺序 (Row-major order)。
    *   **Map**: 按 **键 (Key)** 的顺序（如字母序或数字序）遍历。注意：`foreach` 获取的是 Key，而不是 Value。
    *   **Set**: 按元素的顺序遍历（有序）。
    *   **Stack / Queue**: **不支持** `foreach` 遍历（这违反了它们只能访问端点的原则）。

## 5. 总结表

| 类 (Class) | 描述 (Description) | 核心操作 (Key Operations) | 遍历顺序 |
| :--- | :--- | :--- | :--- |
| **Vector** | 动态数组 | `add`, `insertAt`, `removeAt`, `[]` | 索引顺序 |
| **Stack** | 后进先出 (LIFO) | `push`, `pop`, `peek` | 不支持 |
| **Queue** | 先进先出 (FIFO) | `enqueue`, `dequeue`, `peek` | 不支持 |
| **Map** | 键值对映射 | `put`, `get`, `containsKey`, `[]` | 键的排序顺序 |
| **Set** | 无重复元素集合 | `add`, `contains`, `+`, `*`, `-` | 元素的排序顺序 |


---

## Lexicon 拓展


### 1. 概述 (Overview)
*   **定义**：`Lexicon` 是一个专门用于存储**单词列表**（word list）的集合类。
*   **与 Map/Dictionary 的区别**：`Lexicon` 不存储单词的定义或关联值，只存储单词本身的存在性。从概念上讲，它类似于 `Set<string>`。
*   **设计目的**：虽然 `Set<string>` 也能存储单词，但 `Lexicon` 针对单词存储进行了**极其高效**的优化，特别是在检查**前缀 (Prefix)** 方面，这使得它非常适合用于拼写检查器、Scrabble、Boggle 等文字游戏程序。

### 2. 核心特性 (Key Features)
1.  **前缀查找 (Prefix Lookup)**：这是 `Lexicon` 最强大的功能。它不仅能检查一个单词是否存在，还能检查是否存在以特定字符串为**前缀**的单词。
    *   *应用场景*：在填字游戏中，如果你有 "zz"，你可以询问词库是否有以 "zz" 开头的单词。如果返回 `false`，你就知道无需再尝试添加后续字母了。
2.  **忽略大小写 (Case Insensitivity)**：在 `Lexicon` 中，"Zoo", "ZOO", and "zoo" 被视为同一个单词。单词通常以小写形式存储。
3.  **高效存储**：内部通常使用 **Trie (字典树/前缀树)** 数据结构实现（见下文“内部实现”），比普通的二叉搜索树更节省空间且查找速度更快。

### 3. 常用接口 (Interface Summary)

需包含头文件：`#include "lexicon.h"`

#### 3.1 构造函数
| 方法 | 描述 |
| :--- | :--- |
| `Lexicon()` | 创建一个空的词库。 |
| `Lexicon(filename)` | 创建一个词库，并自动从指定文件中读取单词。文件可以是文本文件（每行一个词）或预编译的二进制文件（`.dat`）。 |

> **提示**: 斯坦福库通常附带一个名为 `"EnglishWords.dat"` 的文件，包含约 100,000 个英语单词。
> ```cpp
> Lexicon english("EnglishWords.dat");
> ```

#### 3.2 核心方法
| 方法 | 用法示例 | 描述 |
| :--- | :--- | :--- |
| **contains** | `lex.contains(word)` | 检查 `word` 是否存在于词库中 (返回 `bool`, 忽略大小写)。 |
| **containsPrefix**| `lex.containsPrefix(prefix)` | **核心功能**。检查词库中是否存在以 `prefix` 开头的单词。例如，如果词库中有 "apple"，则 `containsPrefix("app")` 返回 `true`。 |
| **add** | `lex.add(word)` | 向词库中添加一个新单词。 |
| **addWordsFromFile**| `lex.addWordsFromFile(filename)`| 读取文件中的所有单词并添加到当前词库中。 |
| **size** | `lex.size()` | 返回词库中单词的总数。 |
| **isEmpty** | `lex.isEmpty()` | 如果词库为空返回 `true`。 |
| **clear** | `lex.clear()` | 清空词库中的所有单词。 |

#### 3.3 迭代 (Iteration)
`Lexicon` 支持使用 `for` 进行遍历。
*   **遍历顺序**：按字母顺序 (Alphabetical order)。
*   **大小写**：返回的单词通常是小写。

```cpp
for (string word : english) {
    if (word.length() == 2) {
        cout << word << endl; // 打印所有两个字母的单词
    }
}
```

---

### 4. 内部实现原理：Trie (Prefix Tree)
虽然作为客户端只需了解接口，但了解其实现有助于理解为何它比 `Set<string>` 更适合处理单词。

*   **Trie (发音类似 "try")**：一种树形结构。
*   **结构**：根节点代表空字符串。每个节点有 26 个分支（对应 'a'-'z'）。
*   **路径即单词**：单词不是存储在节点中，而是由从根节点向下的**路径**表示。
*   **标记**：节点中有一个标志（flag），表示到达该位置的路径是否构成一个完整的单词。

**Trie 的优势**：
1.  **前缀查询极快**：要检查 "app" 是否是前缀，只需从根节点向下走三步（a -> p -> p）。如果路径存在，则是有效前缀。
2.  **节省空间**：单词 "apple", "apply", "application" 共享公共路径 "appl-"，节省了存储公共前缀的空间。

---

### 5. 应用示例：查找英语中的单词

以下代码展示了如何使用 `Lexicon` 生成所有由两个字母组成的英语单词（如 "at", "is", "go"）：

```cpp
#include <iostream>
#include "lexicon.h"
using namespace std;

int main() {
   // 初始化英语词库
   Lexicon english("EnglishWords.dat");
   
   string word = "xx"; // 占位符
   
   // 遍历所有可能的两个字母组合
   for (char c0 = 'a'; c0 <= 'z'; c0++) {
      word = c0;
      for (char c1 = 'a'; c1 <= 'z'; c1++) {
         word = c1;
         
         // 利用 Lexicon 检查是否为有效单词
         if (english.contains(word)) {
            cout << word << endl;
         }
      }
   }
   return 0;
}
```

### 总结
`Lexicon` 是处理自然语言单词列表的最佳选择。如果你需要做拼写检查、字谜游戏或任何涉及单词前缀搜索的任务，应优先使用 `Lexicon` 而不是 `Set<string>` 或 `Vector<string>`。