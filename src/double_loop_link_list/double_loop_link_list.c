#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Node
{
    int data;
    struct Node* pre;
    struct Node* next;
}Node;

Node* initList()
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = 0;
    node->next = node;
    node->pre = node;

    return node;
}

void headInsert(Node* list, int data)
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = data;
    node->next = list->next;
    node->pre = list;
    
    list->next->pre = node;
    list->next = node;

    list->data++;
}

void tailInsert(Node* list, int data)
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = data;
    node->pre = list->pre;
    node->next = list;

    list->pre->next = node;
    list->pre = node;

    list->data++;
}

int delete(Node* list, int data)
{
    Node* iterator = list->next;
    while (iterator != list)
    {
        if (iterator->data == data)
        {
            iterator->pre->next = iterator->next;
            iterator->next->pre = iterator->pre;

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
    while (iterator != list)
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
    while (list->next != list)
    {
        delete(list, list->next->data);
    }
    free(list);
    
    return 0;
}