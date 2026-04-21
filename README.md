# Problem 112 - shell 模拟

**ACMOJ Problem ID**: 1447

## Table of Contents

- [Problem 112 - shell 模拟](#problem-112-shell-模拟)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [Submission Format](#submission-format)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

This problem tests algorithmic problem-solving skills.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **1447. shell 模拟** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/112/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

#### 题面

  在 c++ 中，传统的命令行程序需要用户通过命令调用目标程序。接受用户命令并启动目标程序的中间程序称为 shell 。shell 需要完成的一个重要工作是解析输入字符串，并将其转变成标准参数格式以传入目标程序的 `main` 函数中。 `main` 函数的标准参数格式如下：

  ```c++
  int main(int argc,char** argv);
  ```

  `argc` 代表参数个数， `argv` 指向一个长度为 `argc` 的指针数组，指针数组的每个元素指向一个字符串。

  输入命令的参数以空格隔开，保证输入命令最后一个字符不是空格。

##### 解释

  `ls -al /usr/bin`

  在此条命令中，argc = 3, argv[0] = "ls", argv[1] = "-al", argv[2] = "/usr/bin"

#### 要求

  我们已经为你写好了 `shell` 类，但 `shell` 类的正常工作依赖于 `arguments` 类，为此，请你实现 `arguments` 类的构造函数与析构函数，使 `shell` 类正常工作。

  `arguments` 的构造函数负责解析 `cmd` ，并为 `_argc` 与 `_argv` 赋上正确的值；析构函数负责避免内存泄漏。

  - 不允许使用给定头文件之外的头文件
  - 不允许增加/修改成员变量
  - 不需要修改 `shell` 类的实现
  - 可以添加合适的辅助函数

#### 模板

```C++
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <functional>
// WARNING: NO more headers allowed!

using std::pair;
using std::string;
using std::vector;
using std::map;
using std::function;
namespace final {
    class arguments {
    private:
        // WARNING: You cannot add more member variables.
        int _argc;
        char** _argv;
    public:
        arguments() : _argc(0), _argv(nullptr) {}
        explicit arguments(const string& cmd) {
            // todo implement constructor
        }
        ~arguments() {
            // todo implement destructor
        }
        // WARNING: You cannot modify the following functions
        int argc() const { return _argc; }
        char** argv() const { return _argv; }
    };

    // You don't need to modify shell.
    class shell {
    private:
        map<int, arguments> running_list;
    public:
        shell() = default;

        void run(int pid, const string& cmd, const function<void(int, char**)>& invoked) {
            running_list.emplace(pid, cmd);
            invoked(running_list[pid].argc(), running_list[pid].argv());
        }

        int subprocessExit(int pid, int return_value) {
            running_list.erase(pid);
            return return_value;
        }
        vector<int> getRunningList() const {
            vector<int> rt;
            for (auto& pair:running_list)rt.push_back(pair.first);
            return rt;
        }
    };
}
```

### Input Format



### Output Format



### Samples

No sample data provided for this problem.

### Data Constraints

- 20% 测试点只需要 `argc` 正确
- 60% 测试点需要 `argc` 与 `argv` 均正确
- 20% 测试点测试其它行为

评分：

- 若程序正常退出且无内存泄漏，获得全部已获得分数
- 若程序正常退出但发生内存泄漏，获得 80% 已获得分数
- 若程序编译成功但发生 Runtime Error ，获得退出前 60% 已获得分数
- 若程序无法通过编译，将无法获得分数

## Resource Limits

- **Time Limit**: 10000 ms
- **Memory Limit**: 512 MiB

## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 10000 ms
- **Memory Limit (per test case)**: 512 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/112/data_test/`.

## Submission Requirements

### Submission Format

Submit a single C++ source file to the Online Judge. The OJ provides its own `main.cpp` which `#include "src.hpp"`. Your submission will be written to `src.hpp` and compiled together with the OJ's driver code.

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
