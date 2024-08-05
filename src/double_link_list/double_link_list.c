#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Node
{
    int data;
    struct Node* pre;
    struct Node* next;
} Node;

Node* initList()
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = 0;
    node->next = NULL;
    node->pre = NULL;
    
    return node;
}

void headInsert(Node* list, int data)
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = data;
    node->pre = list;
    node->next = list->next;

    if(list->data != 0)
    {
        list->next->pre = node;
    } 
    list->next = node;

    list->data++;
}

void tailInsert(Node* list, int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    
    node->data = data;

    Node* iterator = list;
    while (iterator->next)
    {
        iterator = iterator->next;
    }
    
    node->next = iterator->next;
    node->pre = iterator;

    iterator->next = node;

    list->data++;
}

int delete(Node* list, int data)
{
    Node* iterator = list->next;
    while (iterator)
    {
        if (iterator->data == data)
        {
            if(iterator->next)
            {
                iterator->next->pre = iterator->pre;
            }
            iterator->pre->next = iterator->next;

            free(iterator);

            list->data--;

            return TRUE;
        }

        iterator = iterator->next;
    }
    
    return FALSE;
}

void printList(Node* list)
{
    Node* iterator = list->next;

    while (iterator)
    {
        printf("%d -> ", iterator->data);
        iterator = iterator->next;
    }
    printf("NULL\n");
}

int main()
{
    // 初始化链表
    Node* list = initList();
    printf("初始化链表: \n");
    printList(list);

    // 头插法插入元素
    headInsert(list, 3);
    headInsert(list, 2);
    headInsert(list, 1);
    printf("头插法插入 1, 2, 3: \n");
    printList(list);

    // 尾插法插入元素
    tailInsert(list, 4);
    tailInsert(list, 5);
    tailInsert(list, 6);
    printf("尾插法插入 4, 5, 6: \n");
    printList(list);

    // 删除元素
    delete(list, 1);
    printf("删除元素 1: \n");
    printList(list);

    delete(list, 4);
    printf("删除元素 4: \n");
    printList(list);

    delete(list, 6);
    printf("删除元素 6: \n");
    printList(list);

    // 释放链表内存
    while (list->next)
    {
        delete(list, list->next->data);
    }
    free(list);
    
    return 0;
}