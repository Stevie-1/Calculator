#include "FileStream.h"

//将结果写入文件
void ResultSaveToFile(const char* fileName, double result, char* expression) {
    FILE* fp = fopen(fileName, "a");
    if (fp != NULL) {
        fprintf(fp, "%s=%lf\n", expression, result);
        fclose(fp);
    }
}