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
}

void freeList(List* list)
{
    free(list->data);
    free(list);
}

void printList(List* list)
{
    for (int i = 0; i < list->num; i++)
    {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int binarySearchRecursion(List* list, int value, int start, int end)
{
    int mid = (start + end) / 2;

    if (start == end && list->data[mid] != value)
    {
        return -1;
    }
    
    if (list->data[mid] > value)
    {
        return binarySearchRecursion(list, value, start, mid - 1);
    }
    else if (list->data[mid] < value)
    {
        return binarySearchRecursion(list, value, mid + 1, end);
    }
    else
    {
        return mid;
    }
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

    int searchValue = 10;  
    int index = binarySearchRecursion(myList, searchValue, 0, myList->num - 1);  
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