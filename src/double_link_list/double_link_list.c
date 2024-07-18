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

            iterator->pre = NULL;
            iterator->next = NULL;

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
        printf("%d->", iterator->data);
        iterator = iterator->next;
    }
    printf("NULL\n");
}

int main()
{
    Node* L = initList();
    headInsert(L, 1);
    headInsert(L, 2);
    headInsert(L, 3);
    headInsert(L, 4);
    headInsert(L, 5);
    printList(L);

    tailInsert(L, 6);
    tailInsert(L, 7);
    tailInsert(L, 8);
    tailInsert(L, 9);
    tailInsert(L, 10);
    printList(L);

    delete(L, 1);
    delete(L, 1);
    delete(L, 10);
    printList(L);
    
    return 0;
}