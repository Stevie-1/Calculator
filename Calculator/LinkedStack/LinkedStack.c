#include"LinkedStack.h"

//创建栈
Stack* StackConstruct(int sizeOfElem) {
    Stack* pList = (Stack*)malloc(sizeof(Stack));
    if (pList == NULL) {
        return NULL;
    }
    pList->pFirstNode = NULL;
    pList->length = 0;
    pList->elementSize = sizeOfElem;
    return pList;
}

//析构栈
void StackDestruct(Stack* pStack) {
    ListClear(pStack);
    free(pStack);
    return;
}

//判断栈是否为空
int StackIsEmpty(Stack* pStack) {
    return pStack->length == 0 ? 1 : 0;
}

//求链表长度
int StackGetLength(Stack* pStack) {
    return pStack->length;
}

//头部插入数据(入栈)
Status StackPush(Stack* pStack, void* pElem) {
    ListNode* pNewNode;
    pNewNode = ListInitNode(pStack, pElem);
    if (pNewNode == NULL) {
        return ERROR;
    }
    pNewNode->pNextNode = pStack->pFirstNode;
    pStack->pFirstNode = pNewNode;
    pStack->length++;
    return OK;
}

//出栈
Status StackPop(Stack* pStack, void* pElem) {
    ListNode* pTempNode;
    if (pStack->length == 0) {
        return ERROR;
    }
    pTempNode = pStack->pFirstNode;
    pStack->pFirstNode = pTempNode->pNextNode;
    void* pTemp = ListGetData(pTempNode);
    memcpy(pElem, pTemp, pStack->elementSize);
    ListFreeNode(pTempNode);
    pTempNode = NULL;
    pStack->length--;
    return OK;
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


//取栈顶数据
void* StackGetTop(Stack* pStack) {
    ListNode* pTempNode;
    if (pStack->length == 0) {
        return NULL;
    }
    pTempNode = pStack->pFirstNode;
    void* pTemp = ListGetData(pTempNode);
    void* pElem=malloc(sizeof(pStack->elementSize));
    memcpy(pElem, pTemp, pStack->elementSize);
    pTempNode = NULL;
    return pElem;
}

//遍历栈
void StackTraverse(Stack* pStack) {
    ListNode *pNodeTemp = pStack->pFirstNode;
    for (int i = 0; i < pStack->length; i++) {
        if (pStack->elementSize == sizeof(double)) { // double
            printf("%lf ", (*(double*)pNodeTemp->pData));
        }
        else if (pStack->elementSize == sizeof(char)) { // char
            printf("%c ", (*(char*)pNodeTemp->pData));
        }
        pNodeTemp = pNodeTemp->pNextNode; // 移动到下一个节点
    }
    printf("\n"); // 输出结束后换行
}

