#include "CalculatorPackage.h"

//将中缀表达式转化为后缀表达式
Status expressionInfixToSuffix(char* infix, char* suffix){
    //构建一个栈，检查堆区内存是否分配成功。@note：free
    Stack* charStack = StackConstruct(sizeof(char));
    if (charStack == NULL) return ERROR;

    char *pStringTemp;
    char cGarbage;
    char *pCharTop;
    int i, j = 0; //i用于遍历中缀表达式，j用于遍历后缀表达式

    //遍历中缀表达式
    for (i = 0; i < strlen(infix); i++) {
        //遇到数字和小数点,直接输出到后缀表达式
        while (isdigit(infix[i]) || '.' == infix[i]) {
            suffix[j++] = infix[i++];
            if (!isdigit(infix[i]) && '.' != infix[i])
                suffix[j++] = ' '; //添加分隔符
        }

        //遇到左括号
        if ('(' == infix[i]) {
            //直接入栈
            StackPush(charStack, &infix[i]);
        }

        //遇到右括号
        if (')' == infix[i]) {
            //直接将栈内符号出栈，直到栈顶为左括号
            while (1) {
                //取栈顶元素到(*pCharTop)
                if (StackIsEmpty(charStack) == 0) {
                    pCharTop = (char*)StackGetTop(charStack); 
                    //栈顶元素为左括号，跳出循环
                    if ((*pCharTop) == '(') {
                        StackPop(charStack, &cGarbage);  //左括号出栈但不输出
                        break; 
                    }
                }
                else break;
                //高优先级出栈
                pStringTemp = wordPopFromStack(charStack); //free
                strcpy(&suffix[j], pStringTemp);
                j+=strlen(pStringTemp);
                free(pStringTemp);
                pStringTemp = NULL;
            }
        }

        //遇到到+或—
        if ('+' ==  infix[i] || '-' == infix[i]) {
            while (1) {
                //取栈顶元素到(*pCharTop)
                if (StackIsEmpty(charStack) == 0) {
                    pCharTop = (char*)StackGetTop(charStack); 
                    //栈弹空或者，栈顶元素为左括号，跳出循环
                    if ((*pCharTop) == '(') break;
                }
                else break;
                //高优先级出栈
                pStringTemp = wordPopFromStack(charStack); //free
                strcpy(&suffix[j], pStringTemp);
                j+=strlen(pStringTemp);
                free(pStringTemp);
                pStringTemp = NULL;
            }
            if ('(' == infix[i - 1] || i == 0) { //如果为-为负数标记
                suffix[j++] = '0';
                suffix[j++] = ' ';
            }
            StackPush(charStack, &infix[i]);//把+-入栈
        }

        //遇到到*或/
        if ('*' == infix[i] || '/' == infix[i] || '%' == infix[i]) {
            while (1) {
                //取栈顶元素到(*pCharTop)
                if (StackIsEmpty(charStack) == 0) {
                    pCharTop = (char*)StackGetTop(charStack);
                    if ((*pCharTop) == '(') break; 
                    else if ((*pCharTop) == '+' || (*pCharTop) == '-') break;
                }
                else break;   
                //高优先级出栈
                pStringTemp = wordPopFromStack(charStack); //free
                strcpy(&suffix[j], pStringTemp);
                j+=strlen(pStringTemp);
                free(pStringTemp);
                pStringTemp = NULL;               
            }
            StackPush(charStack, &infix[i]);//将*/入栈           
        }

        //遍历中缀表达式到三角函数和平方根函数等函数
        int iTemp = i;
        int iTemp2 = (int)infix[i];
        if ((iTemp2 > 64 && iTemp2 < 91) || (iTemp2 > 96 && iTemp2 < 123)){
            if ((strncmp(&infix[i], "sin", 3) == 0 && strncmp(&infix[i], "sinh", 4) != 0)\
            || (strncmp(&infix[i], "cos", 3) == 0 && strncmp(&infix[i], "cosh", 4) != 0)\
            || (strncmp(&infix[i], "tan", 3) == 0 && strncmp(&infix[i], "tanh", 4) != 0)||\
            strncmp(&infix[i], "log", 3) == 0) {
                for (int j = 0; j < 3; j++){
                    StackPush(charStack, &infix[iTemp+2-j]);
                }
                i+=2;
            }
            else if (strncmp(&infix[i], "sqrt", 4) == 0 || strncmp(&infix[i], "fabs", 4) == 0 || strncmp(&infix[i], "sinh", 4) == 0 || \
            strncmp(&infix[i], "cosh", 4) == 0 || strncmp(&infix[i], "tanh", 4) == 0 || strncmp(&infix[i], "ceil", 4) == 0){
                for (int j = 0; j < 4; j++){
                    StackPush(charStack, &infix[iTemp+3-j]);
                }
                i+=3;
            }
            else if (strncmp(&infix[i], "floor", 5) == 0){
                for (int j = 0; j < 5; j++){
                    StackPush(charStack, &infix[iTemp+4-j]);
                }
                i+=4;
            }
            else if (strncmp(&infix[i], "arcsin", 6) == 0 || strncmp(&infix[i], "arccos", 6) == 0 ||strncmp(&infix[i], "arctan", 6) == 0 ){
                for (int j = 0; j < 6; j++){
                    StackPush(charStack, &infix[iTemp+5-j]);
                }
                i+=5;
            }
            else {
                printf("ERROR:Expression is wrong.\n");
                return ERROR;
            }
        }

        //遍历中缀表达式到^
        if ('^' == infix[i]) {
            StackPush(charStack, &infix[i]);
        }

        //判断输入的表达式是否错误
        if (('(' == infix[i]) && (')' == infix[i + 1])) {
            printf("ERROR:Expression is wrong.\n");
            return ERROR;
        }

        //错误判断plus 
        int signal = 0;
        int array[] = {0, 32, 40, 41, 42, 43, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 94, 97, 98, 99, 100, 101, 102,\
        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122}; //46
        for (int j = 0; j < 46; j++) {
            if ((int)infix[i] == array[j]) signal++;
        }
        if (signal == 0){
            printf("\033[31mERROR:Expression is wrong.\033[0m\n");
            return ERROR;
        }
    }



    //剩下单词出栈
    while (1) {
        //取栈顶元素到(*pCharTop)
        if (StackIsEmpty(charStack) == 0) {
            pCharTop = (char*)StackGetTop(charStack); 
            if ((*pCharTop) == '(') break;
        }
        else break;
        pStringTemp = wordPopFromStack(charStack); //free
        strcpy(&suffix[j], pStringTemp);
        j+=strlen(pStringTemp);
        free(pStringTemp);
        pStringTemp = NULL;
    }
    suffix[--j] = '\0';
#if DEBUG
    printf("The suffix expression is %s\n", suffix);
#endif
    StackDestruct(charStack);
    return OK;
}

//计算后缀表达式的结果:
double suffixExpressionCalculate(char* suffix) {
    char d[EXPRESSION_LENGTH];
    //构建一个双精度浮点数栈，用于储存操作数。@note：检查堆内存分配是否成功，函数结束时需要释放堆内存。
    Stack* doubleStack = StackConstruct(sizeof(double));
    if (doubleStack == NULL) exit(EXIT_FAILURE);

    //遍历后缀表达式
    for (int i = 0; i < strlen(suffix); i++) {//i用于遍历后缀表达式

        //当i处为实数
        int j = 0;//j用于在每一个i处搜索数字 
        while (isdigit(suffix[i]) || '.' == suffix[i]) { //一次循环可以将一个数据转换成double类型并入栈 
            d[j++] = suffix[i++];//把字符串里的数字和'.'放到另一个字符串中，以将其转换为double类型
            d[j] = '\0';

            if (!isdigit(suffix[i]) && '.' != suffix[i]) { //当str中读取的不是数字(即str[]中的运算符)后，将d[]中字符转换成double类型
                double dTemp;
                dTemp = atof(d);   //使用atof()将字符串形式的运算数转换为double型数据                
                StackPush(doubleStack, &dTemp);   //将类型转化成double后的运算数入栈
            }
        }

        //当i处为运算符
        int iPre, iPost;//用来把double类型的数强制转换成int类型 以进行取余运算
        double dPre, dPost;//dPre用于储存被操作数，dPost用于储存操作数
        if (suffix[i] == '+' || suffix[i] == '-' || suffix[i] == '*' || suffix[i] == '/' || suffix[i] == '%' || suffix[i] == '^') {
            StackPop(doubleStack, &dPost);
            StackPop(doubleStack, &dPre);
            switch (suffix[i]) {
            case '+':
                dPre += dPost;
                break;
            case '-':
                dPre -= dPost;
                break;
            case '*':
                dPre *= dPost;
                break;
            case '/':
                if (dPost == 0) {
                    printf("\033[31mERROR: 0 can't divide.\033[0m\n");//分母为0时：ERROR
                    return ERROR;
                }
                dPre /= dPost;
                break;
            case '%':
                iPre = (int)dPre;
                iPost = (int)dPost;
                iPre %= iPost;
                dPre = (double)iPre;
                break;
            case '^':
                if (dPost == 0) {
                    dPre = 1;
                }
                else {
                    for (int i = 0; i < dPost - 1; i++) {
                        dPre *= dPre;
                    }
                }
                break;
            }
            StackPush(doubleStack, &dPre);
        }
        
        if (strncmp(&suffix[i], "sin", 3)==0 || strncmp(&suffix[i], "cos", 3)==0 || strncmp(&suffix[i], "tan", 3)==0\
        || strncmp(&suffix[i], "log", 3)==0 || strncmp(&suffix[i], "fabs", 4)==0 || strncmp(&suffix[i], "sinh", 4)==0\
        || strncmp(&suffix[i], "cosh", 4)==0 || strncmp(&suffix[i], "tanh", 4)==0 || strncmp(&suffix[i], "ceil", 4)==0\
        || strncmp(&suffix[i], "floor", 5)==0 || strncmp(&suffix[i], "arcsin", 6)==0 || strncmp(&suffix[i], "arccos", 6)==0\
        || strncmp(&suffix[i], "arctan", 6)==0) {                                                                   
            StackPop(doubleStack, &dPost);
            switch (suffix[i]) {
            case 's':
                switch (suffix[i+3]){
                    case 'h': //sinh
                        dPre = sinh(dPost);
                        i+=3;
                        break;
                    default:
                        dPre = sin(dPost);
                        i+=2;
                        break;
                }
                break;

            case 'c':
                switch (suffix[i+3]){
                    default://cos
#if DEBUG
    printf("hi!here!\n");
#endif
                        dPre = cos(dPost);
                        i+=2;
                        break;
                    case 'h': //cosh
                        dPre = cosh(dPost);
                        i+=3;
                        break;
                    case 'l':
                        dPre = ceil(dPost);
                        i+=3;
                        break;
                }
                break;

            case 't':
                switch (suffix[i+3]){
                    default://tan
                        dPre = tan(dPost);
                        i+=2;
                        break;
                    case 'h': //tanh
                        dPre = tanh(dPost);
                        i+=3;
                        break;
                }
                break;

            case 'a':
                switch (suffix[i+3]){
                    case 's'://arcsin
                        dPre = asin(dPost);
                        i+=5;
                        break;
                    case 'c'://arccos
                        dPre = acos(dPost);
                        i+=5;
                        break;
                    case 't'://arctan
                        dPre = atan(dPost);
                        i+=5;
                        break;
                }
                break;

            case 'f':
                switch (suffix[i+1]){
                    case 'a'://fabs
                    dPre = fabs(dPost);
                    i+=3;
                    break;
                    case 'l'://floor
                    dPre = floor(dPost);
                    break;
                }
                break;

            case 'l': //log
                dPre = log(dPost);
                i+=2;
                break;

            default:
                break;
            }
#if DEBUG
    printf("The operated number is %lf\n", dPost);
    printf("Triangle Function outcome is %lf\n", dPre);
#endif
            StackPush(doubleStack, &dPre);
        }

        if (strncmp(&suffix[i], "sqrt", 4)==0){
            StackPop(doubleStack, &dPost);
            dPre = sqrt(dPost);
            i+=3;
            StackPush(doubleStack, &dPre);
        }
    }
    double dResult;
    StackPop(doubleStack, &dResult);//将栈中最后计算出的结果放到中
    StackDestruct(doubleStack);
    return dResult;
}

//计算中缀表达式
double InfixExpressionCalculate(char* infix){
    char *suffix = malloc(EXPRESSION_LENGTH*sizeof(char));
    if (suffix == NULL) exit(EXIT_FAILURE);

    expressionInfixToSuffix(infix, suffix);
    double result = suffixExpressionCalculate(suffix);
    free(suffix);
    suffix = NULL;
    
    return result;
}

