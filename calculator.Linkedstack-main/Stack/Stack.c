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
Bool StackIsEmpty(Stack* pStack) {
    return(pStack->pTop == pStack->pBase) ? TRUE : FALSE;
}

//定义visit函数
Status Visit(void* pElem) {
    if (!pElem) return ERROR;
    char* ch = (char*)pElem;
    printf("%s", ch);
    return OK;
}
//遍历栈：
Status StackTraverse(Stack* pStack, Status(*visit)(void*)) {
    if (pStack->pTop == pStack->pBase || pStack->pTop == NULL) return ERROR;
    void* p = pStack->pBase;
    char* temp = (char*)p;
    while (p != pStack->pTop) {
        Visit(p);
        p = ++temp;
    }
    return OK;
}




