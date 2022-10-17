#include "compiler.h"

void GetHelp() {
    printf("simulate - 为分析机代码设计的编译模拟器\n\n");
    printf("usage: simulate [source_file] [-o output_file] [-l "
           "log_file]\n\n");
    printf("选项:\n");
    printf("\t-h, --help\t\t输出帮助界面\n");
    printf("\t-v, --version\t\t输出版本信息与声明\n");
    printf("\t-o\t\t\t将程序输出到指定文件, 若此项留空, "
           "输出结果将会呈现在命令行\n");
    printf("\t-l\t\t\t将程序运行日志输出到指定文件, 若此项留空, "
           "将不会输出日志\n\n");
}

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
            GetHelp();
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

void CompileError(int pos, int type, char oper) {
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
    std::cout << s[pos] << std::endl;
    exit(-1);
}

bool CheckValidInput(std::string strinput) {
    if (strinput[0] != 'N' && strinput[0] != '+' &&
        strinput[0] != '-' && strinput[0] != '*' &&
        strinput[0] != '/' && strinput[0] != 'L' &&
        strinput[0] != 'S' && strinput[0] != 'P' &&
        strinput[0] != 'B' && strinput[0] != 'F' &&
        strinput[0] != '?') {
        for (int i = 0; i < strinput.size(); i++) {
            if (strinput[0] == '#')
                return 0;
            if (strinput[0] != ' ')
                CompileError(operation_cnt, 10);
        }
    }
    return 1;
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
    std::cout << s[pos] << std::endl;
    exit(-1);
}