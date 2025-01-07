#ifndef STACK_H
#define STACK_H

#include"../DEBUG.h"
#include"../EXPRESSION_LENGTH.h"
#include"../Status.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 10     //栈指针malloc的内存大小
#define ADDSIZE 5   //栈指针realloc增加的内存大小

/**定义泛型栈结构体
 * @param pBase指向为栈的起始位置，pTop指向为栈顶的下一个位置，elementSize指栈中元素的大小，size表示栈的当前大小
 */
typedef struct Stack{
    void* pBase;
    void* pTop;
    int elementSize;
    int size;
} Stack;

//栈相关函数

/**
 * @brief 构建元素大小为特定值的栈
 * 
 * @param sizeOfElement指栈元素的大小
 * 
 * @return 返回NULL表示操作失败
 * 
 * @note 程序结束时须释放堆内存
 */
Stack* StackConstruct(int sizeOfElment);

/**
 * @brief 析构栈
 * 
 * @param pStack指向一个栈
 * 
 * @return 无返回值
 */
void StackDestruct(Stack* pStack);

/**
 * @brief 判断栈是否为空
 * 
 * @param pStack指向一个栈
 * 
 * @return 返回1表示栈为空，0表示栈不空
 */
int StackIsEmpty(Stack* pStack);

/**
 * @brief 获取栈的长度
 * 
 * @param pStack指向一个栈
 * 
 * @return 返回栈的长度
 */
int StackGetLength(Stack* pStack);

/**
 * @brief 入栈
 * 
 * @param pStack指向一个栈，pElem指向一个栈元素
 * 
 * @return 返回OK表示操作成功，返回ERROR表示操作失败
 */
Status StackPush(Stack* pStack, void* pElem);

/**
 * @brief 出栈并记录出栈元素
 * 
 * @param pStack指向一个栈，pElem指向出栈的元素
 * 
 * @return 返回OK表示操作成功，返回ERROR表示操作失败
 */
Status StackPop(Stack* pStack, void* pElem);

/**
 * @brief 子函数，以一个单词为单位出栈，并返回该单词
 * 
 * @param stack指向一个栈
 * 
 * @return 返回字符串，字符串储存该单词
 * 
 * @note 释放堆区内存
 */
char *wordPopFromStack(Stack *stack);

/**
 * @brief 访问栈顶元素
 * 
 * @param pStack指向一个栈
 * 
 * @return 返回指向栈顶元素的指针
 */
void *StackGetTop(Stack* pStack);

/**
 * @brief 遍历栈
 * 
 * @param pStack指向一个栈；visit()指向一个函数，使用此函数来访问一个元素
 * 
 * @return 无返回值
 */
void StackTraverse(Stack* pStack);

/**
 * @brief 扩充栈的容量
 * 
 * @param pStack指向一个栈
 * 
 * @return 返回OK表示操作成功，返回ERROR表示操作失败
 */
Status StackExpand(Stack* pStack);

/**
 * @brief 缩小栈的容量
 * 
 * @param pStack指向一个栈
 * 
 * @return 返回OK表示操作成功，返回ERROR表示操作失败
 * 
 * @note 缩小后的栈不能再进行入栈操作，否则会导致程序崩溃
 */
Status StackShrink(Stack* pStack);

/**
 * @brief 复制栈
 * 
 * @param pStack指向一个栈
 * 
 * @return 返回复制后的栈
 * 
 * @note 复制后的栈与原栈共享内存，修改其中一个栈会影响另一个栈
 */
Stack* StackCopy(Stack* pStack);

/**
 * @brief 获取栈底元素
 * 
 * @param pStack指向一个栈
 * 
 * @return 返回指向栈底元素的指针
 * 
 * @note 栈底元素是栈中最后一个入栈的元素
 */
void* StackGetBottom(Stack* pStack);

/**
 * @brief 逆向遍历栈
 * 
 * @param pStack指向一个栈
 * 
 * @return 无返回值
 */
void StackReverseTraverse(Stack* pStack);

/**
 * @brief 获取栈的容量
 * 
 * @param pStack指向一个栈
 * 
 * @return 返回栈的容量
 * 
 * @note 栈的容量是指栈的最大容量
 */
int StackGetCapacity(Stack* pStack);




#endif
