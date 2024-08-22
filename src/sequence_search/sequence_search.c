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
    list->data = (int*)malloc(sizeof(int) * length);
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
    else
    {
        return;
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
    for (int i = 0; i < list->num; i++)
    {
        if (list->data[i] == value)
        {
            return i;
        }
    }
    
    return -1;
}

void freeList(List* list)
{
    free(list->data);
    free(list);
}

int main(int argc, char* argv[])  
{  
    // 测试程序  
    List* myList = initList(5);  
    listAdd(myList, 10);  
    listAdd(myList, 20);  
    listAdd(myList, 30);  
    listAdd(myList, 40);  
    listAdd(myList, 50);  
    
    printList(myList);  

    int searchValue = 50;  
    int index = sequenceSearch(myList, searchValue);  
    if (index != -1)  
    {  
        printf("Value %d found at index %d.\n", searchValue, index);  
    }  
    else  
    {  
        printf("Value %d not found in the list.\n", searchValue);  
    }  

    freeList(myList); // 释放分配的内存  

    return 0;  
} 