#ifndef CALCULATORPACKAGE_H
#define CALCULATORPACKAGE_H

#include "../Stack/Stack.h"
#define ARRSIZE 50

/**
 * @brief 将中缀表达式转化为后缀表达式参数 
 * 
 * @param infix指向为中缀表达式，suffix指向后缀表达式
 * 
 * @return 返回OK表示操作成功，ERROR表示失败
 */
Status ExpressionInfixToSuffix(char* infix, char* suffix);

/**
 * @brief 计算后缀表达式 
 * 
 * @param suffix指向后缀表达式
 * 
 * @return 返回计算结果
 */
double SuffixExpressionCalculate(char* suffix);

#endif