# x86-linux-analytical-engine-simulator

## simulate - 为分析机代码设计的编译模拟器

在完成课程计算机科学的伟大思想 (Great Ideas in Computer Science, SJTU CS1950 / Stanford CS54N) 的过程中, 看到 TA 们写的 [分析机模拟器](https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1320) 觉得非常炫酷, 于是准备自己实现一个简陋版本.

## 功能

可以通过该模拟器对你的分析机源文件进行 **编译**,**模拟**, 并在模拟过程中, 输出相关**警告信息**,**错误提醒**以及每一步的**储存数据**.

## 环境

项目是在 Ubuntu 22.04 下, 使用 GCC 11.2.0 进行搭建的, 若环境配置不同可自行编译单个主程序 main.cpp.

## 使用方法

以 Linux 为例, 其它系统类同

```
./simulate [source_file] [-o output_file] [-l log_file]

选项:
        -h, --help              输出帮助界面
        -v, --version           输出版本信息与声明
        -o                      将程序输出到指定文件, 若此项留空, 输出结果将会呈现在命令行
        -l                      将程序运行日志输出到指定文件, 若此项留空, 将不会输出日志
```

其中, source_file 是分析机源文件, output_file 是输出文件, log_file 是日志文件. output_file 中存放模拟源程序得到的结果, log_file 中存放每一步的各个数据.

例如
```
./simulate test.txt -o a.txt -l b.txt
``
就是编译模拟 test.txt, 输出结果至 a.txt, 输出日志至 b.txt.
