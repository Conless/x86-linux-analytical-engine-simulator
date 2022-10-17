// Statement and information
// Author: Conless
// Date: 2022-10-17
// File name:
// /course/22fall/sjtu/cs1950/week_2/x86-linux-analytical-engine-simulator/main.cpp

// Headers
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>

// Constants, global variables and definitions


#ifdef _WIN32
#define CONSOLE "CON"
#elif __linux__
#define CONSOLE "/dev/tty"
#endif


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int operation_cnt, operator_type, operation_result, operation_result_1,
    runup_lever, step_cnt;
int first_num, second_num;
int data[10];
char filename[105], outputfilename[105], logfilename[105];
vector<int> result;
string s[1005];

// Classes

// Funtions
void CheckInput(int argc, char **argv) {
    if (argc == 1)
        return;
    int i = 1;
    if (argv[1][0] != '-') {
        strcpy(filename, argv[1]);
        freopen(filename, "r", stdin);
        i++;
    }
    for (; i < argc; i++) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            printf("simulate - 为分析机代码设计的编译模拟器\n\n");
            printf("usage: simulate [source_file] [-o output_file] [-l "
                   "log_file]\n\n");
            printf("选项:\n");
            printf("\t-h, --help\t\t输出帮助界面\n");
            printf("\t-v, --version\t\t输出版本信息与声明\n");
            printf("\t-o\t\t\t将程序输出到指定文件, 若此项留空, 输出结果将会呈现在命令行\n");
            printf("\t-l\t\t\t将程序运行日志输出到指定文件, 若此项留空, "
                   "将不会输出日志\n\n");
            exit(0);
        } else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version")) {
            printf("Analytical Engine Simulator 1.0.0 (Conless Pan, October "
                   "2022)\n");
            printf("分析机模拟器 [版本 1.0.0, GCC版本 11.2.0]\n");
            printf("在 x86-Linux 上运行.\n\n");
            exit(0);
        } else if (!strcmp(argv[i], "-o")) {
            strcpy(outputfilename, argv[i + 1]);
            i++;
        } else if (!strcmp(argv[i], "-l")) {
            strcpy(logfilename, argv[i + 1]);
            freopen(logfilename, "w", stdout);
            i++;
        } else {
            printf("错误: 无法识别的命令 \'%s\'\n", argv[i]);
            printf("键入 \"simulate -h\" 以了解用法.\n");
            exit(-1);
        }
    }
}

void CompileError(int pos, int type, char oper = 0) {
    freopen(CONSOLE, "w", stdout);
    printf("%s:%d: 编译错误: ", filename, pos);
    if (type == 1)
        printf("对函数 N 进行了不当操作.");
    if (type == 2)
        printf("对函数 %c 进行了不当操作.", oper);
    if (type == 3)
        printf("对函数 L 进行了不当操作.");
    if (type == 4)
        printf("对函数 S 进行了不当操作.");
    if (type == 5)
        printf("对函数 P 进行了不当操作.");
    if (type == 6)
        printf("对函数 B 进行了不当操作.");
    if (type == 7)
        printf("对函数 F 进行了不当操作.");
    if (type == 8)
        printf("对函数 ?B 进行了不当操作.");
    if (type == 9)
        printf("对函数 ?F 进行了不当操作.");
    if (type == 10)
        printf("无法识别的命令.");
    printf("\n\t%d | ", pos);
    cout << s[pos] << endl;
    exit(-1);
}

void OutputLog(int line) {
    if (!strcmp(logfilename, ""))
        return;
    printf("Step %d, Line %d\n", step_cnt++, line);
    for (int i = 0; i < 10; i++)
        printf("v%d=%d, ", i, data[i]);
    printf("\n");
    printf("E=%d, E\'=%d\n\n", operation_result, operation_result_1);
}

void OperationError(int pos, int type) {
    freopen(CONSOLE, "w", stdout);
    printf("%s:%d: 操作错误: ", filename, pos);
    if (type == 1)
        printf("输入的操作数过多.");
    if (type == 2)
        printf("运算器并没有给出运算结果.");
    if (type == 3)
        printf("运算器尚未被初始化.");
    printf("\n\t%d | ", pos);
    cout << s[pos] << endl;
    exit(-1);
}

void OutputResult() {
    // fclose(stdout);
    if (strcmp(outputfilename, ""))
        freopen(outputfilename, "w", stdout);
    else freopen(CONSOLE, "w", stdout);
    for (int num : result)
        printf("%d\n", num);
    fclose(stdout);
}

// Main function
int main(int argc, char **argv) {
    CheckInput(argc, argv);
    while (getline(cin, s[++operation_cnt])) {
        if (s[operation_cnt][0] != 'N' && s[operation_cnt][0] != '+' &&
            s[operation_cnt][0] != '-' && s[operation_cnt][0] != '*' &&
            s[operation_cnt][0] != '/' && s[operation_cnt][0] != 'L' &&
            s[operation_cnt][0] != 'S' && s[operation_cnt][0] != 'P' &&
            s[operation_cnt][0] != 'B' && s[operation_cnt][0] != 'F' &&
            s[operation_cnt][0] != '?') {
            for (int i = 0; i < s[operation_cnt].size(); i++) {
                if (s[operation_cnt][0] == '#')
                    break;
                if (s[operation_cnt][0] != ' ')
                    CompileError(operation_cnt, 10);
            }
            operation_cnt--;
        }
    }
    first_num = second_num = -1;
    for (int i = 1; i <= operation_cnt; i++) {
        OutputLog(i - 1);
        if (s[i][0] == 'N') {
            if (s[i].size() < 5 || s[i][1] != ' ' || s[i][2] < '0' ||
                s[i][2] > '9' || s[i][3] != ' ')
                CompileError(i, 1);
            data[s[i][2] - '0'] = 0;
            for (int j = 4; j < s[i].size(); j++) {
                if (s[i][j] == ' ' || s[i][j] == '#')
                    break;
                if (s[i][j] < '0' || s[i][j] > '9')
                    CompileError(i, 1);
                data[s[i][2] - '0'] = data[s[i][2] - '0'] * 10 + s[i][j] - '0';
            }
        } else if (s[i][0] == '+' || s[i][0] == '-' || s[i][0] == '*' ||
                   s[i][0] == '/') {
            if (s[i].size() > 1 && s[i][1] != ' ' && s[i][1] != '#')
                CompileError(i, 2, s[i][0]);
            if (s[i][0] == '+')
                operator_type = 1;
            if (s[i][0] == '-')
                operator_type = 2;
            if (s[i][0] == '*')
                operator_type = 3;
            if (s[i][0] == '/')
                operator_type = 4;
        } else if (s[i][0] == 'L') {
            if (s[i].size() < 3 || s[i][1] != ' ' || s[i][2] < '0' ||
                s[i][2] > '9' ||
                (s[i].size() > 3 && s[i][3] != ' ' && s[i][3] != '#'))
                CompileError(i, 3);
            if (first_num == -1)
                first_num = data[s[i][2] - '0'];
            else if (second_num == -1) {
                second_num = data[s[i][2] - '0'];
                if (operator_type == 1)
                    operation_result = first_num + second_num;
                else if (operator_type == 2) {
                    operation_result = first_num - second_num;
                    if (operation_result < 0) {
                        runup_lever = 1;
                        operation_result = -1;
                    }
                } else if (operator_type == 3) {
                    operation_result = first_num * second_num;
                } else if (operator_type == 4) {
                    if (second_num == 0) {
                        runup_lever = 1;
                        operation_result = -1;
                        operation_result_1 = -1;
                    } else {
                        operation_result_1 = first_num / second_num;
                        operation_result = first_num % second_num;
                    }
                } else {
                    OperationError(i, 3);
                }
                first_num = -1;
                second_num = -1;
            } else
                OperationError(i, 1);
        } else if (s[i][0] == 'S') {
            if (s[i].size() < 2)
                CompileError(i, 2);
            if (s[i][1] != '\'') {
                if (s[i].size() < 3 || s[i][1] != ' ' || s[i][2] < '0' ||
                    s[i][2] > '9' ||
                    (s[i].size() > 3 && s[i][3] != ' ' && s[i][3] != '#'))
                    CompileError(i, 4);
                if (operation_result == -1)
                    OperationError(i, 2);
                data[s[i][2] - '0'] = operation_result;
            } else {
                if (s[i].size() < 4 || s[i][2] != ' ' || s[i][3] < '0' ||
                    s[i][3] > '9' ||
                    (s[i].size() > 4 && s[i][4] != ' ' && s[i][4] != '#'))
                    CompileError(i, 4);
                if (operation_result_1 == -1)
                    OperationError(i, 2);
                data[s[i][3] - '0'] = operation_result_1;
            }
        } else if (s[i][0] == 'P') {
            if (s[i].size() < 3 || s[i][1] != ' ' || s[i][2] < '0' ||
                s[i][2] > '9' ||
                (s[i].size() > 3 && s[i][3] != ' ' && s[i][3] != '#'))
                CompileError(i, 5);
            result.push_back(data[s[i][2] - '0']);
        } else if (s[i][0] == 'B') {
            if (s[i].size() < 3 || s[i][1] != ' ' || s[i][2] < '0' ||
                s[i][2] > '9')
                CompileError(i, 6);
            int backward_step = 0;
            for (int j = 2; j < s[i].size(); j++) {
                if (s[i][j] == ' ' || s[i][j] == '#')
                    break;
                if (s[i][j] < '0' || s[i][j] > '9')
                    CompileError(i, 6);
                backward_step = backward_step * 10 + s[i][j] - '0';
            }
            i -= backward_step;
        } else if (s[i][0] == 'F') {
            if (s[i].size() < 3 || s[i][1] != ' ' || s[i][2] < '0' ||
                s[i][2] > '9')
                CompileError(i, 7);
            int forward_step = 0;
            for (int j = 2; j < s[i].size(); j++) {
                if (s[i][j] == ' ' || s[i][j] == '#')
                    break;
                if (s[i][j] < '0' || s[i][j] > '9')
                    CompileError(i, 6);
                forward_step = forward_step * 10 + s[i][j] - '0';
            }
            i += forward_step;
        } else if (s[i][0] == '?') {
            if (s[i][1] == 'B') {
                if (runup_lever == 0)
                    continue;
                s[i].erase(0, 1);
                runup_lever = 0;
                if (s[i].size() < 3 || s[i][1] != ' ' || s[i][2] < '0' ||
                    s[i][2] > '9')
                    CompileError(i, 8);
                int backward_step = 0;
                for (int j = 2; j < s[i].size(); j++) {
                    if (s[i][j] == ' ' || s[i][j] == '#')
                        break;
                    if (s[i][j] < '0' || s[i][j] > '9')
                        CompileError(i, 6);
                    backward_step = backward_step * 10 + s[i][j] - '0';
                }
                s[i].insert(0, "?");
                i -= backward_step;
            } else if (s[i][1] == 'F') {
                if (runup_lever == 0)
                    continue;
                s[i].erase(0, 1);
                runup_lever = 0;
                if (s[i].size() < 3 || s[i][1] != ' ' || s[i][2] < '0' ||
                    s[i][2] > '9')
                    CompileError(i, 9);
                int forward_step = 0;
                for (int j = 2; j < s[i].size(); j++) {
                    if (s[i][j] == ' ' || s[i][j] == '#')
                        break;
                    if (s[i][j] < '0' || s[i][j] > '9')
                        CompileError(i, 6);
                    forward_step = forward_step * 10 + s[i][j] - '0';
                }
                s[i].insert(0, "?");
                i += forward_step;
            } else {
                CompileError(i, 10);
            }
        } else {
            if (s[i] != "")
                CompileError(i, 0);
        }
    }
    OutputResult();
    return 0;
}