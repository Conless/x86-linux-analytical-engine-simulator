// Statement and information
// Author: Conless
// Date: 2022-10-17
// File name:
// /course/22fall/sjtu/cs1950/week_2/x86-linux-analytical-engine-simulator/main.cpp

// Headers

#include "../include/compiler.h"
#include "../include/operator.h"

int operation_cnt, operator_type, operation_result, operation_result_1,
    runup_lever, step_cnt;
int first_num, second_num;
int data[10];
char filename[105], outputfilename[105], logfilename[105];

std::string s[1005];

std::vector<int> result;

// Main function
int main(int argc, char **argv) {
    CheckInput(argc, argv);
    while (getline(std::cin, s[++operation_cnt])) {
        if (!CheckValidInput())
            operation_cnt--;
    }
    Operate();
    OutputResult();
    return 0;
}