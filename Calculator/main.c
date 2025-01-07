#include "./DEBUG.h"
#include "./EXPRESSION_LENGTH.h"
#include "./Status.h"
#include "./CalculatorPackage/CalculatorPackage.h"
#include "./FileStream/FileStream.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDER_LENGTH 5

int main(){
    /**
     * 模式选择
     * Mode 1：操作者从终端输入单个表达式，程序运行计算出结果后从终端输出结果；
     * Mode 2：操作者在文件Expression.txt中编辑多个表达式，程序直接从文件中读取，计算出结果后又输出到文件Results.txt中；
     * help：给操作者提供使用指南
     * 
     * 退出程序：quit
     */

    char order[ORDER_LENGTH]; //order字符串用于储存操作者给的指令

    printf("\033[34mMode 1.Get an expression from Shell; print the result in Shell\033[0m\n");
    printf("\033[34mMode 2.Get expressions form Expressions.txt; print the result in Results.txt\033[0m\n");
    printf("\033[32mPlease enter 1 or 2 to chose your mode.\033[0m\n");
    printf("\033[35mEnter help for instructions.\033[0m\n");
    scanf("%s", order);
    if (order[1] == '\0'){
        if ((order[0]-'0') < 0 || (order[0]-'0') > 4){
            printf("\033[31mERROR: Please enter 1 or 2.\033[0m\n");
        }
        else if ((order[0]-'0') == 1){
#if DEBUG
    char s[7] = "Mode 1";//表明成功进入Mode 1
    printf("%s\n", s);
#endif
            while(1){
                char *infix = malloc(EXPRESSION_LENGTH*sizeof(char));
                if (infix == NULL) exit(EXIT_FAILURE);

                //获取表达式
                printf("\033[32mEnter an expression\033[31m(Enter quit to quit):\033[0m");
                scanf("%s", infix);

                //检查是否是退出指令
                if (strcmp(infix, "quit") == 0){
                    printf("\033[37mYou've already quit the executable file!\033[0m");
                    //释放堆内存
                    free(infix);
                    infix = NULL;
                    exit(EXIT_SUCCESS);
                }
            
#if DEBUG
    printf("The infix expression is %s\n", infix);
#endif 
                printf("\033[35mResult: %lf\033[0m\n", InfixExpressionCalculate(infix));

                //释放堆内存
                free(infix);
                infix = NULL;
            }
        }
        else if ((order[0]-'0') == 2){
#if DEBUG
    char s[7] = "Mode 2";//表明成功进入Mode 2
    printf("%s\n", s);
#endif
            FILE *fp = fopen(".\\Expressions&Results\\Expressions.txt", "r"); //fclose
            char *infix = malloc(EXPRESSION_LENGTH*sizeof(char));//free
            if (infix == NULL) exit(EXIT_FAILURE);
            while(1){
                //检查是否到文件尾部
                if (fgetc(fp) == EOF) exit(EXIT_SUCCESS);
                fseek(fp, -1, SEEK_CUR);
                fscanf(fp, "%s", infix);
                //写入文件
#if DEBUG
    printf("\033[31mHi! here! 1\033[0m\n");
#endif
                ResultSaveToFile(".\\Expressions&Results\\Results.txt", InfixExpressionCalculate(infix), infix);
#if DEBUG
    printf("\033[31mHi! here! 2\033[0m\n");
#endif
            }
            printf("\033[35mThe results have been saved to file Results.txt!\033[0m\n");
            free(infix);
            infix = NULL;
            fclose(fp);
            exit(EXIT_SUCCESS);
        }
    }    
    else if (strcmp(order, "help") == 0){
#if DEBUG
    char s[10] = "Mode Help";//表明成功进入Mode Help
    printf("%s\n", s);
#endif
        printf("\033[42m\033[37mQuit: In Mode 1, enter quit to quit form repeated asking.\n");
        printf("Expression Input: The expression consists of real numbers, parentheses, +, -, *, /, ^, and triangle functions.\n");
        printf("Please ensure the expression is valid and don't put <space> between words.\n");
        printf("In Mode 2, divide expressions with <return>.\033[0m\n");
        return 0;
    }
    else if (strcmp(order, "quit") == 0){
        return 0;
    }
    else{
        printf("\033[31mERROR: Invalid Input!\033[0m\n");
        return -1;
    }
}