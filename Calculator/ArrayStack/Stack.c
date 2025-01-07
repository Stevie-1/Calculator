#include "Stack.h"

//构建栈
Stack *StackConstruct(int sizeOfElment) {
    //从堆上分配一个栈。@note：free
    Stack *pStack = (Stack*)malloc(sizeof(Stack)); 
    if (pStack == NULL) { //检查分配成功与否
        return NULL;
    }

    //从堆上给栈的基础分配内存，形成动态内存数组。@note：free
    pStack->pBase = malloc(SIZE * sizeOfElment); 
    if (pStack->pBase == NULL) { //检查分配成功与否
        free(pStack);
        return NULL;
    }

    pStack->pTop = pStack->pBase;
    pStack->elementSize = sizeOfElment;
    pStack->size = SIZE;
    return pStack;
}

//析构栈
void StackDestruct(Stack* pStack) {
    if (pStack == NULL) {
        return;
    }
    free(pStack->pBase);
    pStack->pBase = NULL;
    free(pStack);
    pStack = NULL;
    return;
}

//入栈
Status StackPush(Stack* pStack, void* pElem) {
    //检查栈是否已满，若满栈，则进行数组扩容
    if (StackGetLength(pStack) >= pStack->size) { 
        int NewSize = pStack->size + ADDSIZE;
        void *pTemp = (void*)realloc(pStack->pBase, NewSize * sizeof(pStack->elementSize));
        if (pTemp == NULL) { //检查分配是否成功
            return ERROR;
        }
        else { //更新栈
            pStack->pBase = pTemp;
            pStack->pTop = (char*)pStack->pBase + pStack->size;
            pStack->size = NewSize;
        }
    }
    memcpy(pStack->pTop, pElem, pStack->elementSize); //添加栈顶元素
    pStack->pTop = (char*)pStack->pTop + pStack->elementSize; //更新栈顶
    return OK;
}

//出栈并记录出栈元素
Status StackPop(Stack* pStack, void* pElem) {
    //检查栈是否为空
    if (pStack->pTop == pStack->pBase) {
        return ERROR;
    }
    else {
        pStack->pTop = (char*)pStack->pTop - pStack->elementSize; //更新栈顶
        memcpy(pElem, pStack->pTop, pStack->elementSize); //记录出栈元素
        return OK;
    }
}

//以一个单词为单位出栈，并返回该单词
char *wordPopFromStack(Stack *stack){
#if DEBUG
    if (StackIsEmpty == 0){
        StackTraverse(stack);
    }
#endif
    //从堆区分配一个字符串，储存出栈的单词
    char *string = malloc(EXPRESSION_LENGTH*sizeof(char));
    if (string == NULL) return NULL;
    int i = 0;
    char cTemp;
    StackPop(stack, &cTemp);
    //三角函数和平方根函数判断
    char *pCharTop = (char*)StackGetTop(stack);
#if DEBUG
    printf("top = %c\n", *pCharTop);
#endif
    if ((cTemp == 's' && (*pCharTop) == 'q') || (cTemp == 'f' && (*pCharTop) == 'a') || (cTemp == 'c' && (*pCharTop) == 'e')){ //sqrt or fabs or ceil
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        string[i++] = ' ';
        string[i++] = '\0'; 
    }
    else if (cTemp == 's' && (*pCharTop) == 'i'){ //sin
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
#if DEBUG
    printf("\033[32mGet point_1\n\033[0m");
    printf("empty check = %d\n", StackIsEmpty(stack));
#endif

    if (StackIsEmpty(stack) == 0){
#if DEBUG
    printf("\033[32mGet point_3\n\033[0m");
#endif
        char *pCharTop2 = (char*)StackGetTop(stack);
#if DEBUG
    printf("\033[32mGet point_2\n\033[0m");
    printf("ptoh = %p", pCharTop2);
    printf("h = %c", *pCharTop2);
#endif
        if ((*pCharTop2) == 'h'){ //sinh
            printf("\033[32mGet point_2\n\033[0m");
            StackPop(stack, &cTemp);
            string[i++] = cTemp;
        }
    }
        string[i++] = ' ';
        string[i++] = '\0'; 
}
    else if (cTemp == 'c' && (*pCharTop) == 'o'){ //cos
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;

        if (StackIsEmpty(stack) == 0){
            char *pCharTop2 = (char*)StackGetTop(stack);
            if ((*pCharTop2) == 'h'){ //cosh
                StackPop(stack, &cTemp);
                string[i++] = cTemp;
            }
        } 
        string[i++] = ' ';
        string[i++] = '\0'; 
    }
    else if (cTemp == 't'){ //tan
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        
        if (StackIsEmpty(stack) == 0){
            char *pCharTop2 = (char*)StackGetTop(stack);
            if ((*pCharTop2) == 'h'){ //cosh
                StackPop(stack, &cTemp);
                string[i++] = cTemp;
            }
        }
        string[i++] = ' ';
        string[i++] = '\0'; 
    }
    else if (cTemp == 'a' && (*pCharTop) == 'r'){//arc
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
    }
    else if (cTemp == 'l' && (*pCharTop) == 'o'){//log
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        string[i++] = ' ';
        string[i++] = '\0'; 
    }
    else if (cTemp == 'f' && (*pCharTop) == 'l'){//floor
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        StackPop(stack, &cTemp);
        string[i++] = cTemp;
        string[i++] = ' ';
        string[i++] = '\0'; 
    }
    else{    
        string[i++] = cTemp;
        string[i++] = ' ';
        string[i++] = '\0';    
    }
    return string;
}


//取栈顶元素
void* StackGetTop(Stack* pStack) {
    void* pElem = (char*)pStack->pTop - pStack->elementSize;
    return pElem;
}

//求栈的长度
int StackGetLength(Stack* pStack) {
    return ((int*)pStack->pTop - (int*)pStack->pBase) / pStack->elementSize;
}

//判断栈是否为空:
int StackIsEmpty(Stack* pStack) {
    return(pStack->pTop == pStack->pBase) ? 1 : 0;
}

// 遍历栈
void StackTraverse(Stack* pStack) {
    for (int i = 0; i < pStack->size; i++) {
        if (pStack->elementSize == sizeof(double)) { // double
            void *pTemp = (char*)pStack->pBase + i * sizeof(double);
            printf("%lf ", (*(double*)pTemp));
        }
        else if (pStack->elementSize == sizeof(char)) { // char
            void *pTemp = (char*)pStack->pBase + i * sizeof(char);
            printf("%c ", (*(char*)pTemp));
        } 
    }
    printf("\n"); // 输出结束后换行
}

//栈扩容
Status StackExpand(Stack* pStack) {
    int newSize = pStack->size + ADDSIZE; // 新容量增加
    void* newBase = realloc(pStack->pBase, newSize * pStack->elementSize);
    if (newBase == NULL) {
        return ERROR; // 扩展失败，内存分配错误
    }
    pStack->pBase = newBase; // 更新栈底指针
    pStack->size = newSize; // 更新栈的容量
    return OK; // 扩展成功
}

//栈缩小
Status StackShrink(Stack* pStack) {
    if (pStack->size <= SIZE) return ERROR; // 如果当前大小小于或等于初始大小，不进行缩减

    int newSize = pStack->size - ADDSIZE; // 新容量减小
    void* newBase = realloc(pStack->pBase, newSize * pStack->elementSize);
    if (newBase == NULL) {
        return ERROR; // 缩减空间错误
    }
    pStack->pBase = newBase; // 更新栈底指针
    pStack->size = newSize; // 更新栈的容量
    return OK; // 缩减成功
}

//复制栈
Stack* StackCopy(Stack* pStack) {
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    if (newStack == NULL) return NULL; // 检查内存分配

    newStack->elementSize = pStack->elementSize;
    newStack->size = pStack->size;
    newStack->pBase = malloc(pStack->size * pStack->elementSize);
    if (newStack->pBase == NULL) {
        free(newStack); // 释放已分配的内存
        return NULL;
    }
    
    memcpy(newStack->pBase, pStack->pBase, pStack->size * pStack->elementSize);
    newStack->pTop = newStack->pBase + (pStack->pTop - pStack->pBase); // 设置栈顶指针
    return newStack; // 返回新栈
}

//获取栈底元素
void* StackGetBottom(Stack* pStack) {
    if (StackIsEmpty(pStack)) return NULL; // 如果栈为空，返回NULL
    return pStack->pBase; // 返回栈底元素
}

//查看栈的容量
int StackGetCapacity(Stack* pStack) {
    return pStack->size; // 返回栈当前的容量
}