#include "FileStream.h"

//从文件中读取表达式
char *ExpressionReadFromFile(FILE* fp){
    char *expression = malloc(EXPRESSION_LENGTH*sizeof(char));
    if (expression == NULL) return NULL;
    fscanf(fp, "%s", expression);
    return expression;
}


//将结果写入文件
Status ResultSaveToFile(const char* fileDirName, double result, char* expression) {
    FILE* fp = fopen(fileDirName, "a");
    if (fp != NULL) {
        fprintf(fp, "%s=%lf\n", expression, result);
        fclose(fp);
        return OK;
    }
    else return ERROR;
}