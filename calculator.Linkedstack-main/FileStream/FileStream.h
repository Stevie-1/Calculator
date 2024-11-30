#ifndef FILESTREAM_H
#define FILESTREAM_H

#include "../common.h"

/**
 * @brief 将结果写入文件 
 * 
 * @param flieName为文件名，result为计算结果，expression为计算表达式
 * 
 * @return 无返回值
 */
void ResultSaveToFile(const char* fileName, double result, char* expression);

#endif