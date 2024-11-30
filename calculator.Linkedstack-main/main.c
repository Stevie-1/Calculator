#include "common.h"
#include "./CalculatorPackage/CalculatorPackage.h"
#include "./FileStream/FileStream.h"

#define EXPRESSION_LENGTH 50

int main(){
    char *infix = malloc(EXPRESSION_LENGTH*sizeof(char));
    if (infix == NULL) exit(EXIT_FAILURE);
    char *suffix = malloc(EXPRESSION_LENGTH*sizeof(char));
    if (suffix == NULL) exit(EXIT_FAILURE);

    printf("输入一个表达式：");
    scanf("%s", infix);
    
#if DEBUG
    printf("输入的表达式为：%s", infix);
#endif 

    ExpressionInfixToSuffix(infix, suffix);
    double result = SuffixExpressionCalculate(suffix);

#if DEBUG
    printf("结果为%lf", result);
#endif 


}