#include "./LinkedStack/LinkedList.h"

static int compareInt(void* a, void* b) {
    // 将void指针转换为int指针
    const int* intA = (const int*)a;
    const int* intB = (const int*)b;

    // 比较两个整数的值
    if (*intA < *intB) {
        return -1; // 第一个整数小于第二个整数
    } else if (*intA > *intB) {
        return 1;  // 第一个整数大于第二个整数
    } else {
        return 0;  // 两个整数相等
    }
}

int main(){
    List list = {NULL, 0, sizeof(int)}; //初始化一个栈，该栈储存整数
    
    for (int i = 0; i < 9; i++){ //给该栈初始化数据
        int temp = 9-i;
        ListAppendToEnd(&list, &temp);
    }
    
    ListTraverse(&list);

    ListSort(&list, compareInt);

    ListTraverse(&list);

    ListReverse(&list);

    ListTraverse(&list);    

    return 0;
}