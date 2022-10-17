// Statement and information
// Author: Conless
// Date: 2022-10-17
// File name:
// /course/22fall/sjtu/cs1950/week_2/x86-linux-analytical-engine-simulator/main.cpp

// Headers

#include "../include/compiler.h"
#include "../include/operator.h"

// Main function
int main(int argc, char **argv) {
    CheckInput(argc, argv);
    while (getline(std::cin, s[++operation_cnt])) {
        if (!CheckValidInput(s[operation_result]))
            operation_cnt--;
    }
    Operate();
    OutputResult();
    return 0;
}