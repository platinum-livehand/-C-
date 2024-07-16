#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int data;
    struct Node* next;
} Node;

Node* initList() 
{
    Node* list = (Node*)malloc(sizeof(Node));
    list->data = 0;
    list->next = NULL;
    return list;
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
    Node* head = list;
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    list = list->next;
    while (list->next)
    {
        list = list->next;
    }
    list->next = node;
    head->data++;
}

void delete(Node* list, int data)
{
    Node* pre = list;
    Node* current = list->next;
    while (current)
    {
        if(current->data == data)
        {
            pre->next = current->next;
            free(current);
            break;
        }
        pre = current;
        current = current->next;
    }
    list->data--;
}

void printList(Node* list)
{
    list = list->next;
    while(list)
    {
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");
}

int main()
{
    Node* list = initList();
    headInsert(list, 1);
    headInsert(list, 2);
    headInsert(list, 3);
    headInsert(list, 4);
    headInsert(list, 5);
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