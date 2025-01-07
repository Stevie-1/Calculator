#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../DEBUG.h"
#include "../EXPRESSION_LENGTH.h"
#include "../Status.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//结点类型的定义
typedef struct ListNode {
    struct ListNode* pNextNode;//指向下一个节点的指针
    void* pData;//指向节点值的泛型指针
}ListNode;

//链表的定义
typedef struct {
    ListNode* pFirstNode; //头节点指针
    int length;//链表长度
    int elementSize;//泛型元素的大小
}List;

/**
 * @brief 创建一个节点
 * 
 * @param pList指向一个链表，pData指向一个数据
 * 
 * @return 返回指向新节点的指针，创建失败则返回NULL
 */
ListNode* ListInitNode(List* pList, void* pData);

/**
 * @biref 释放节点
 * 
 * @param pNode指向一个需要释放的节点
 * 
 * @return 无返回值
 */
void ListFreeNode(ListNode* pNode);

/**
 * @brief 清空链表(不清除头节点)
 * 
 * @param pList指向一个链表
 * 
 * @return 无返回值
 */
void ListClear(List* pList);

/**
 * @brief 取节点数据
 * 
 * @param pNode指向要取的节点
 * 
 * @return 返回数据的地址
 * 
 * @note pNode不能为NULL
 */
void* ListGetData(ListNode* pNode);

/**
 * @brief 判断节点是否为空
 * 
 * @param pNode指向目标节点
 * 
 * @return 若为空，返回1；否则返回0
 */
int NodeIsEmpty(ListNode* pNode);

/**
 * @brief 从链表尾部插入数据
 * 
 * @param pList指向一个链表，pData指向要插入的数据
 * 
 * @return 操作成功返回OK，失败返回ERROR
 */
Status ListAppendToEnd(List* pList, void* pData);

/**
 * @brief 从某个节点后插入数据
 * 
 * @param pList指向一个链表，pNode指向某个节点，pData指向要插入的数据
 * 
 * @return 操作成功返回OK，失败返回ERROR
 */
Status ListInsertAfter(List* pList, ListNode* pNode, void* pData);

/**
 * @brief 删除第一个节点
 * 
 * @param pList指向一个链表
 * 
 * @return 操作成功返回OK，操作失败返回ERROR
 */
Status ListDeleteFirstNode(List* pList);

/**
 * @brief 删除最后一个节点
 * 
 * @param pList指向一个链表
 * 
 * @return 操作成功返回OK，失败返回ERROR
 */
Status ListDeleteLastNode(List* pList);

/**
 * @brief 删除某一节点
 * 
 * @param pList指向一个链表，pNode指向某个节点
 * 
 * @return 操作成功返回OK，失败返回ERROR
 */
Status ListDeleteNode(List* pList, ListNode* pNode);

/**
 * @brief 判断链表上的数据和给出数据是否相同
 * 
 * @param listData指向链表上的数据，pData指向给出的数据
 * 
 * @return 一致返回1,不一致返回0
 */
int isThisOne(void* listData, void* pData);

/**
 * @brief 查找数据
 * 
 * @param pList指向一个链表，pKey指向要查找的数据，inThisOne()
 * 
 * @return 返回找到的节点的指针，若不存在该节点，返回NULL
 */
ListNode* ListSearch(List* pList, void* pKey, int(*isThisOne)(void*, void*));

/**
 * @brief 获取链表头节点
 * 
 * @param pList指向一个链表
 * 
 * @return 返回链表头节点的指针
 */
ListNode* ListGetFirstNode(List* pList);

/**
 * @brief 获取链表尾节点
 * 
 * @param pList指向一个链表
 * 
 * @return 返回链表尾节点的指针
 */
ListNode* ListGetLastNode(List* pList);

/**
 * @brief 获取指定位置节点
 * 
 * @param pList指向一个链表，index指定位置
 * 
 * @return 返回指定位置的节点的指针，若不存在该节点，返回NULL
 */
ListNode* ListGetNodeAt(List* pList, int index);


/**
 * @brief 获取节点在链表中的位置
 * 
 * @param pList指向一个链表，pNode指向某个节点
 * 
 * @return 返回节点在链表中的位置，若不存在该节点，返回-1
 */
int ListGetIndex(List* pList, ListNode* pNode);

/**
 * @brief 反转链表
 * 
 * @param pList指向一个链表
 * 
 * @return 无返回值
 */
void ListReverse(List* pList);

/**
 * @brief 合并两个链表
 * 
 * @param pList1指向一个链表，pList2指向另一个链表
 * 
 * @return 返回合并后的链表的指针
 */
List* ListMerge(List* pList1, List* pList2);

/**
 * @brief 复制链表
 * 
 * @param pList指向一个链表
 * 
 * @return 返回复制后的链表的指针
 */
List* ListCopy(List* pList);

/**
 * @brief 链表排序
 * 
 * @param pList指向一个链表，compare指向比较函数
 * 
 * @return 无返回值
 */
void ListSort(List* pList, int (*compare)(void*, void*));

/**
 * @brief 获取链表中间节点
 * 
 * @param pList指向一个链表
 * 
 * @return 返回链表中间节点的指针
 */
ListNode* ListGetMiddleNode(List* pList);

/**
 * @brief 移除链表中的重复元素
 * 
 * @param pList 指向一个链表
 * 
 * @param isThisSame 指向判断是否相同的函数
 */
Status ListRemoveDuplicates(List* pList, int(*isThisSame)(void*, void*));

/**
 * @brief 链表分割
 * 
 * @param pList1 分割结果指向的第一个链表
 * 
 * @param pList2 分割结果指向的另一个链表
 * 
 * @return 无返回值
 */
void ListSplit(List* pList, List* pList1, List* pList2);

/**
 * @brief 链表分割
 * 
 * @param pList 传入的链表的地址
 * 
 * @return 无返回值
 */
void ListTraverse(List* pList);

#endif
