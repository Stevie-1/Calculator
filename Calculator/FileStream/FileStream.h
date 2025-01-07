#ifndef FILESTREAM_H
#define FILESTREAM_H

#include"../DEBUG.h"
#include"../EXPRESSION_LENGTH.h"
#include"../Status.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief 从文件中读取表达式
 * 
 * @param fileDirName表示文件路径
 * 
 * @return 返回一个字符串表达式
 * 
 * @note 释放堆内存
 */
char *ExpressionReadFromFile(FILE* fp);

/**
 * @brief 将结果写入文件 
 * 
 * @param flieName为文件名，result为计算结果，expression为计算表达式
 * 
 * @return 无返回值
 */
Status ResultSaveToFile(const char* fileName, double result, char* expression);

#endif