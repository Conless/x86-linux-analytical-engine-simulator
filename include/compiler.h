#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#define CONSOLE "CON"
#elif __linux__
#define CONSOLE "/dev/tty"
#endif

extern int operation_cnt, operator_type, operation_result, operation_result_1,
    runup_lever, step_cnt;
extern int first_num, second_num;
extern int data[10];
extern char filename[105], outputfilename[105], logfilename[105];

extern std::string s[1005];

extern void CheckInput(int, char **);
extern void CompileError(int, int, char = 0);
extern bool CheckValidInput(std::string);
extern void OperationError(int, int);