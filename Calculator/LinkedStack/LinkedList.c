#include"linkedlist.h"

//创建结点
ListNode* ListInitNode(List* pList, void* pData) {
    ListNode* pNewNode;
    pNewNode = (ListNode*)malloc(sizeof(ListNode));
    if (pNewNode == NULL) {
        return NULL;
    }
    pNewNode->pData = malloc(pList->elementSize);
    if (pNewNode->pData == NULL) {
        free(pNewNode);
        return NULL;
    }
    memcpy(pNewNode->pData, pData, pList->elementSize);
    pNewNode->pNextNode = NULL;
    return pNewNode;
}

//释放结点
void ListFreeNode(ListNode* pNode) {
    if (pNode == NULL) {
        return;
    }
    free(pNode->pData);
    free(pNode);
    return;
}

//清空链表
void ListClear(List* pList) {
    ListNode* pCurrentNode, * pNextNode;
    pCurrentNode = pList->pFirstNode;
    while (pCurrentNode != NULL) { //释放结点，但不释放链表(即保留头结点)
        pNextNode = pCurrentNode->pNextNode;
        ListFreeNode(pCurrentNode);
        pCurrentNode = pNextNode;
    }
    pList->pFirstNode = NULL;
    pList->length = 0;
    return;
}

//取结点上的数据
void* ListGetData(ListNode* pNode) {
    if (pNode->pData == NULL) return NULL;
    return pNode->pData;
}

//判断结点是否为空
int Empyt_Node(ListNode* pNode) {
    return pNode == NULL ? 1 : 0;
}

//尾部插入数据
Status ListAppendToEnd(List* pList, void* pData) {
    ListNode* pNewNode, * pTail;
    pNewNode = ListInitNode(pList, pData);//创建一个结点
    if (pNewNode == NULL) {
        return ERROR;
    }
    if (pList->pFirstNode == NULL) {
        pList->pFirstNode = pNewNode;//当链表为空(即只有头结点)
    }
    else {
        pTail = pList->pFirstNode;
        while (pTail->pNextNode != NULL) {
            pTail = pTail->pNextNode;
        }
        pTail->pNextNode = pNewNode;//将创造的结点插入到链表尾部
    }
    pList->length++;
    return OK;
}

//某节点后插入数据
Status ListInsertAfter(List* pList, ListNode* pNode, void* pData) {
    ListNode* pNewNode;
    pNewNode = ListInitNode(pList, pData);//创建结点
    if (pNewNode == NULL) {
        return ERROR;
    }
    pNewNode->pNextNode = pNode->pNextNode;
    pNode->pNextNode = pNewNode;
    pList->length++;
    return OK;
}

//删除第一个结点
Status ListDeleteFirstNode(List* pList) {
    ListNode* pTempNode;
    if (pList->length == 0) {
        return ERROR;
    }
    pTempNode = pList->pFirstNode;
    pList->pFirstNode = pTempNode->pNextNode;
    ListFreeNode(pTempNode);
    pTempNode = NULL;
    pList->length--;
    return OK;
}

//删除最后一个结点
Status ListDeleteLastNode(List* pList) {
    ListNode* p, * q;
    p = NULL;
    if (pList->length == 0) {
        return ERROR;
    }
    q = pList->pFirstNode;
    if (q->pNextNode == NULL) {//q的nest域为空，说明链表(除头结点外)只有一个结点
        return ListDeleteFirstNode(pList);//删除第一个结点
    }
    while (q->pNextNode != NULL) {
        p = q;
        q = q->pNextNode;//将p、q不断往链表尾部移动，直到q的next域为空，则说明已经遍历到了链表尾部
    }
    p->pNextNode = NULL;//此时p变成了新链表的尾部
    ListFreeNode(q);//释放原链表的尾部
    q = NULL;
    pList->length--;//链表长度减1
    return OK;
}

//删除某一结点
Status ListDeleteNode(List* pList, ListNode* pNode) {
    ListNode* pTempNode;
    if (pNode == NULL) {
        return OK;
    }  
    if (pList->length == 0) {
        return ERROR;
    }
    pTempNode = pList->pFirstNode;
    if (pTempNode == pNode) {
        pList->pFirstNode = pNode->pNextNode;
    }
    else {
        while (pTempNode != NULL && pTempNode->pNextNode != pNode) {
            pTempNode = pTempNode->pNextNode;//找到所要删除的结点位置
        }
        if (pTempNode == NULL) {
            return ERROR;
        }
        pTempNode->pNextNode = pNode->pNextNode;//删除结点
    }
    ListFreeNode(pNode);
    pList->length--;
    return OK;
}

//判断两个数据是否相同
int isThisOne(void* listData, void* pData) {
    return strcmp(listData, pData) == 0 ? 1 : 0;
}

//查找数据的位置
ListNode* ListSearch(List* pList, void* pKey, int(*isThisOne)(void*, void*)) {
    ListNode* pTempNode;
    pTempNode = pList->pFirstNode;
    while (pTempNode != NULL) {
        if (isThisOne(pTempNode->pData, pKey) == 1) {
            return pTempNode;
        }
        pTempNode = pTempNode->pNextNode;
    }
    return NULL;
}

//获取链表头节点
ListNode* ListGetFirstNode(List* pList) {
    return pList->pFirstNode; // 返回链表的头节点
}

//获取链表尾节点
ListNode* ListGetLastNode(List* pList) {
    ListNode* pNode = pList->pFirstNode;
    if (pNode == NULL) return NULL; // 如果链表为空，返回NULL
    while (pNode->pNextNode != NULL) {
        pNode = pNode->pNextNode; // 循环直到找到最后一个节点
    }
    return pNode; // 返回最后一个节点
}

//获取指定位置节点
ListNode* ListGetNodeAt(List* pList, int index) {
    if (index < 0 || index >= pList->length) {
        return NULL; // 索引越界返回NULL
    }
    ListNode* pNode = pList->pFirstNode;
    for (int i = 0; i < index; i++) {
        pNode = pNode->pNextNode; // 遍历至指定位置
    }
    return pNode; // 返回指定位置的节点
}

//查找节点的索引
int ListGetIndex(List* pList, ListNode* pNode) {
    if (pNode == NULL) return -1; // 非法节点返回-1
    int index = 0;
    ListNode* currentNode = pList->pFirstNode;
    while (currentNode != NULL) {
        if (currentNode == pNode) {
            return index; // 找到返回索引
        }
        currentNode = currentNode->pNextNode;
        index++;
    }
    return -1; // 未找到返回-1
}

//反转链表
void ListReverse(List* pList) {
    ListNode* prev = NULL;
    ListNode* current = pList->pFirstNode;
    ListNode* next = NULL;
    while (current != NULL) {
        next = current->pNextNode; // 先保存下一个节点
        current->pNextNode = prev;  // 反转当前节点的指针
        prev = current;             // 移动prev和current
        current = next;
    }
    pList->pFirstNode = prev; // 更新头节点为反转后的第一个节点
}

//合并两个链表
List* ListMerge(List* pList1, List* pList2) {
    List* newList = (List*)malloc(sizeof(List));
    newList->pFirstNode = NULL;
    newList->length = 0;
    newList->elementSize = pList1->elementSize; // 假设两个链表的元素大小相同

    // 复制第一个链表
    ListNode* current = pList1->pFirstNode;
    while (current != NULL) {
        ListAppendToEnd(newList, current->pData); // 使用已有的Append函数
        current = current->pNextNode; 
    }

    // 复制第二个链表
    current = pList2->pFirstNode;
    while (current != NULL) {
        ListAppendToEnd(newList, current->pData);
        current = current->pNextNode; 
    }

    return newList; // 返回合并后的新链表
}

//复制链表
List* ListCopy(List* pList) {
    List* newList = (List*)malloc(sizeof(List));
    newList->pFirstNode = NULL;
    newList->length = 0;
    newList->elementSize = pList->elementSize; // 复制元素大小

    ListNode* current = pList->pFirstNode;
    while (current != NULL) {
        ListAppendToEnd(newList, current->pData); // 使用已有的Append函数
        current = current->pNextNode; 
    }

    return newList; // 返回新的链表副本
}

//链表排序
void ListSort(List* pList, int (*compare)(void*, void*)) {
    if (pList == NULL || pList->length <= 1) return; // 空链表或只有一个元素

    for (int i = 0; i < pList->length - 1; i++) {
        ListNode* current = pList->pFirstNode;
        for (int j = 0; j < pList->length - 1 - i; j++) {
            ListNode* next = current->pNextNode;
            if (compare(current->pData, next->pData) > 0) {
                // 交换数据
                void* temp = current->pData;
                current->pData = next->pData;
                next->pData = temp;
            }
            current = next; // 移动到下一个节点
        }
    }
}

//找出中间节点
ListNode* ListGetMiddleNode(List* pList) {
    if (pList->pFirstNode == NULL) return NULL; // 空链表返回NULL

    ListNode* slow = pList->pFirstNode; // 慢指针
    ListNode* fast = pList->pFirstNode; // 快指针
    while (fast != NULL && fast->pNextNode != NULL) {
        slow = slow->pNextNode; // 慢指针每次移动1步
        fast = fast->pNextNode->pNextNode; // 快指针每次移动2步
    }
    return slow; // 返回中间节点
}

//删除重复元素
Status ListRemoveDuplicates(List* pList, int(*isThisSame)(void*, void*)) {
    if (pList->pFirstNode == NULL) return OK; // 空链表直接返回OK

    ListNode* current = pList->pFirstNode; // 当前节点
    while (current != NULL) {
        ListNode* runner = current; // 内部指针
        while (runner->pNextNode != NULL) {
            if (isThisSame(current->pData, runner->pNextNode->pData)) {
                ListNode* duplicateNode = runner->pNextNode; // 找到重复节点
                runner->pNextNode = runner->pNextNode->pNextNode; // 跳过重复节点
                ListFreeNode(duplicateNode); // 释放内存
                pList->length--; // 更新链表长度
            } else {
                runner = runner->pNextNode; // 移动到下一个节点
            }
        }
        current = current->pNextNode; // 移动到下一个节点
    }
    return OK;
}

//拆分为两个链表
void ListSplit(List* pList, List* pList1, List* pList2) {
    if (pList->pFirstNode == NULL) {
        pList1->pFirstNode = NULL; // 处理空链表
        pList2->pFirstNode = NULL;
        pList1->length = 0;
        pList2->length = 0;
        return;
    }

    ListNode* current = pList->pFirstNode;
    ListNode* temp = NULL;
    int midpoint = pList->length / 2; // 找到拆分点
    for (int i = 0; i < midpoint; i++) {
        ListAppendToEnd(pList1, current->pData); // 将前半部分添加到第一个新链表
        current = current->pNextNode; // 移动到下一个节点
    }
    while (current != NULL) {
        ListAppendToEnd(pList2, current->pData); // 将后半部分添加到第二个新链表
        current = current->pNextNode; // 移动到下一个节点
    }
}

//交换两个节点
Status ListSwapNodes(List* pList, ListNode* node1, ListNode* node2) {
    if (node1 == node2) return OK; // 如果相同，不需要交换

    ListNode* prev1 = NULL, *prev2 = NULL;
    ListNode* current = pList->pFirstNode;

    // 找到节点1和节点2的位置及其前驱
    while (current != NULL) {
        if (current->pNextNode == node1) prev1 = current;
        if (current->pNextNode == node2) prev2 = current;
        current = current->pNextNode;
    }

    // 如果节点1是头节点
    if (node1 == pList->pFirstNode) {
        pList->pFirstNode = node2;
    } else if (node2 == pList->pFirstNode) {
        pList->pFirstNode = node1;
    }

    // 交换两个节点
    if (prev1 != NULL) {
        prev1->pNextNode = node2; // 将节点1的前驱指向节点2
    }
    if (prev2 != NULL) {
        prev2->pNextNode = node1; // 将节点2的前驱指向节点1
    }

    // 交换node1和node2的指针
    ListNode* temp = node1->pNextNode;
    node1->pNextNode = node2->pNextNode;
    node2->pNextNode = temp;

    return OK; // 交换成功
}

//遍历链表
void ListTraverse(List* pList) {
    if (pList->length == 0){
        printf("The list is empty\n");
        return;
    }
    for (ListNode *ptemp = pList->pFirstNode; ptemp != NULL; ptemp = ptemp->pNextNode) {
        if (pList->elementSize == sizeof(int)) {
            printf("%d ", *(int *)(ptemp->pData));
        }
        if (pList->elementSize == sizeof(char)) {
            printf("%c ", *((char *)ptemp->pData));
        }
        if (pList->elementSize == sizeof(double)) {
            printf("%lf ", *(double *)(ptemp->pData));
        }
    }
    printf("\n");
    return;
}






