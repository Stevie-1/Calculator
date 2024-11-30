#ifndef STACK_H
#define STACK_H

#include"../common.h"
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
 * @return 返回TRUE表示栈为空，FALSE表示栈不空
 */
Bool StackIsEmpty(Stack* pStack);

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
 * @brief 访问栈顶元素
 * 
 * @param pStack指向一个栈
 * 
 * @return 返回指向栈顶元素的指针
 */
void *StackGetTop(Stack* pStack);

/**
 * 
 */
Status Visit(void* pElem);
/*
访问栈内一个元素，进行printf操作
参数为数据元素的指针
返回值OK表示visit成功，ERROR表示失败
*/

/**
 * @brief 遍历栈
 * 
 * @param pStack指向一个栈；visit()指向一个函数，使用此函数来访问一个元素
 * 
 * @return 返回OK表示操作成功，返回ERROR表示操作失败
 */
Status StackTraverse(Stack* pStack, Status(*visit)(void*));

#endif
