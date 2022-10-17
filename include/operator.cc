#include "operator.h"
#include "compiler.h"

void OutputResult() {
    // fclose(stdout);
    if (strcmp(outputfilename, ""))
        freopen(outputfilename, "w", stdout);
    else
        freopen(CONSOLE, "w", stdout);
    for (int num : result)
        printf("%d\n", num);
    fclose(stdout);
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

void Operate() {
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
}