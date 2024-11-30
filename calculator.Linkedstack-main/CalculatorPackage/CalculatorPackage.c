#include "CalculatorPackage.h"

//将中缀表达式转化为后缀表达式
Status ExpressionInfixToSuffix(char* infix, char* suffix){
    //构建一个栈，检查堆区内存是否分配成功。@note：free
    Stack* charStack = StackConstruct(sizeof(char));
    if (charStack == NULL) return ERROR;

    char cTemp, cTop;
    void* r;
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
                //取栈顶元素到cTop
                if (StackIsEmpty(charStack) == 0) {
                    r = StackGetTop(charStack);
                    cTop = *((char*)r);
                }
                if ('(' == cTop) break;
                StackPop(charStack, &cTemp);
                suffix[j++] = cTemp;
                suffix[j++] = ' ';

            }
            StackPop(charStack, &cTemp);  //左括号出栈但不输出
        }

        //遇到到+或—
        if ('+' ==  infix[i] || '-' == infix[i]) {
            while (1) {
                //取栈顶元素到cTop
                if (StackIsEmpty(charStack) == 0) {
                    r = StackGetTop(charStack);
                    cTop = *((char*)r);
                }
                //栈弹空或者，栈顶元素为左括号，跳出循环
                if (StackIsEmpty(charStack) || '(' == cTop) break; 
                //栈顶元素优先级更低
                StackPop(charStack, &cTemp);//中缀表达式中+-优先级最低，直接把字符栈中运算符出栈
                suffix[j++] = cTemp;
                suffix[j++] = ' ';
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
                //取栈顶元素到cTop
                if (StackIsEmpty(charStack) == 0) {
                    r = StackGetTop(charStack);
                    cTop = *((char*)r);
                }
                if (StackIsEmpty(charStack) || '(' == cTop || '+' == cTop || '-' == cTop) break;
                StackPop(charStack, &cTemp);//栈中除了+-，其它运算符优先级更高，将其出栈
                suffix[j++] = cTemp;
                suffix[j++] = ' ';
            }
            StackPush(charStack, &infix[i]);//将*/入栈
        }

        //遍历中缀表达式到三角函数
        if (strncmp(&infix[i], "sin", 3) == 0 || strncmp(&infix[i], "cos", 3) == 0 || strncmp(&infix[i], "tan", 3) == 0) {
            for (int j = 0; j < 3; j++){
                StackPush(charStack, &infix[i]);
                i++;
            }
        }
        if (strncmp(&infix[i], "arcsin", 6) == 0 || strncmp(&infix[i], "arccos", 6) == 0 ||strncmp(&infix[i], "arctan", 6) == 0 ){
            for (int j = 0; j < 6; j++){
                StackPush(charStack, &infix[i]);
                i++;
            }
        }

        //遍历中缀表达式到^
        if ('^' == infix[i]) {
            StackPush(charStack, &infix[i]);
        }

        //判断输入的表达式是否错误
        if (('(' == infix[i]) && (')' == infix[i + 1])) {
            printf("ERROR：表达式有误\n");
            return ERROR;
        }
    }

    //剩下单词出栈
    while (!StackIsEmpty(charStack)) {
        StackPop(charStack, &cTemp);
        if ('(' != cTemp) {
            suffix[j++] = cTemp;
            suffix[j++] = ' ';
        }
    }
    suffix[--j] = '\0';
    StackDestruct(charStack);
    return OK;
}

//计算后缀表达式的结果:
double SuffixExpressionCalculate(char* suffix) {
    char d[ARRSIZE];
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
                    printf("ERROR：分母不能为0\n");//分母为0时：ERROR
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
        
        if (strncmp(&suffix[i], "sin", 3)==0 || strncmp(&suffix[i], "cos", 3)==0 || strncmp(&suffix[i], "tan", 3)==0 || strncmp(&suffix[i], "arcsin", 6)==0 || strncmp(&suffix[i], "arccos", 6)==0 || strncmp(&suffix[i], "arctan", 6)==0) {
            StackPop(doubleStack, &dPost);
            switch (suffix[i]) {
            case 's'://sin
                dPre = sin(dPost);
                break;
            case 'c'://cos
                dPre = cos(dPost);
                break;
            case 't'://tan
                dPre = tan(dPost);
                break;
            case 'a':
                switch (suffix[i+3]){
                    case 's'://arcsin
                        dPre = asin(dPost);
                        break;
                    case 'c'://arccos
                        dPre = acos(dPost);
                        break;
                    case 't'://arctan
                        dPre = atan(dPost);
                        break;
                }
                break;
            }
            StackPush(doubleStack, &dPre);
        }
    }
    double dResult;
    StackPop(doubleStack, &dResult);//将栈中最后计算出的结果放到中
    StackDestruct(doubleStack);
    return dResult;
}

