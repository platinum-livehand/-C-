#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Node 
{
    int data;
    struct Node* next;
} Node;

Node* initList() 
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = 0;
    node->next = NULL;

    return node;
}

void headInsert(Node* list, int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = list->next;

    list->next = node;
    list->data++;
}

void tailInsert(Node* list, int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    
    node->data = data;
    node->next = NULL;

    Node* iterator = list;

    while (iterator->next)
    {
        iterator = iterator->next;
    }
    iterator->next = node;

    list->data++;
}

int delete(Node* list, int data)
{
    Node* pre = list;
    Node* current = list->next;
    while (current)
    {
        if(current->data == data)
        {
            pre->next = current->next;

            free(current);

            list->data--;

            return TRUE;
        }

        pre = current;

        current = current->next;
    }

    return FALSE;
}

void printList(Node* list)
{
    list = list->next;
    while(list)
    {
        printf("%d->", list->data);

        list = list->next;
    }
    
    printf("NULL\n");
}

int main()
{
    // 初始化链表
    Node* list = initList();
    printf("初始化链表: ");
    printList(list);

    // 头插法插入元素
    headInsert(list, 3);
    headInsert(list, 2);
    headInsert(list, 1);
    printf("头插法插入 1, 2, 3: ");
    printList(list);

    // 尾插法插入元素
    tailInsert(list, 4);
    tailInsert(list, 5);
    tailInsert(list, 6);
    printf("尾插法插入 4, 5, 6: ");
    printList(list);

    // 删除元素
    delete(list, 1);
    printf("删除元素 1: ");
    printList(list);

    delete(list, 4);
    printf("删除元素 4: ");
    printList(list);

    delete(list, 6);
    printf("删除元素 6: ");
    printList(list);

    return 0;
}