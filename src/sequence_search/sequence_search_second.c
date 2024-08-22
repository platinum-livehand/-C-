#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int* data;
    int length;
    int num;
} List;

List* initList(int length)
{
    List* list = (List*)malloc(sizeof(List));
    list->data = (int*)malloc(sizeof(int) * (length + 1)); // +1 为哨兵留出位置
    list->length = length;
    list->num = 0;

    return list;
}

void listAdd(List* list, int data)
{
    if (list->num < list->length)
    {
        list->data[list->num++] = data;
    }
}

void printList(List* list)
{
    for (int i = 0; i < list->num; i++)
    {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int sequenceSearch(List* list, int value)
{
    list->data[list->num] = value;  // 将哨兵放在最后一个位置

    int i = 0;
    
    while (list->data[i] != value)
    {
        i++;
    }

    // 检查是否是哨兵找到的
    if (i == list->num)
    {
        return -1;  // 未找到
    }

    return i; // 返回实际找到的位置
}

void freeList(List* list)
{
    free(list->data);
    free(list);
}

int main(int argc, char* argv[])  
{  
    List* myList = initList(5);  
    listAdd(myList, 10);  
    listAdd(myList, 20);  
    listAdd(myList, 30);  
    listAdd(myList, 40);  
    listAdd(myList, 50);  
    
    printList(myList);  

    int searchValue = 60;  
    int index = sequenceSearch(myList, searchValue);  
    if (index != -1)  
    {  
        printf("Value %d found at index %d.\n", searchValue, index);  
    }  
    else  
    {  
        printf("Value %d not found in the list.\n", searchValue);  
    }  

    freeList(myList);  

    return 0;  
} 
