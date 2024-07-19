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
    
    Node* iterator = list;
    while (iterator->next != list)
    {
        iterator = iterator->next;
    }
    iterator->next->pre = node;
    iterator->next = node;

    node->pre = iterator;
    node->next = list;

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

            iterator->next = NULL;
            iterator->pre = NULL;

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
        printf("%d->", iterator->data);
        iterator = iterator->next;
    }
    printf("NULL\n");
}

int main()
{
    Node* list = initList();
    headInsert(list, 1);
    headInsert(list, 2);
    headInsert(list, 3);
    headInsert(list, 4);
    headInsert(list, 5);
    printList(list);

    tailInsert(list, 6);
    tailInsert(list, 7);
    tailInsert(list, 8);
    tailInsert(list, 9);
    tailInsert(list, 10);
    printList(list);

    delete(list, 5);
    delete(list, 10);
    delete(list, 6);
    printList(list);
    
    return 0;
}