#ifndef CALCULATORPACKAGE_H
#define CALCULATORPACKAGE_H

#include "../ArrayStack/Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/**
 * @brief 子函数，将中缀表达式转化为后缀表达式参数 
 * 
 * @param infix指向为中缀表达式，suffix指向后缀表达式
 * 
 * @return 返回OK表示操作成功，ERROR表示失败
 * 
 * @note 该函数引用子函数stackToString()
 */
Status expressionInfixToSuffix(char* infix, char* suffix);

/**
 * @brief 子函数，计算后缀表达式 
 * 
 * @param suffix指向后缀表达式
 * 
 * @return 返回计算结果
 */
double suffixExpressionCalculate(char* suffix);

/**
 * @brief 计算中缀表达式
 * 
 * @param infix指向中缀表达式
 * 
 * @return 返回计算结果
 */
double InfixExpressionCalculate(char* infix);


#endif