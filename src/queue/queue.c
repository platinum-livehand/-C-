#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define ERRORS -1

typedef struct Node
{
    int data;
    struct Node* next; 
}Node;

Node* initQueue()
{
    Node* queue = (Node*)malloc(sizeof(Node));

    queue->data = 0;
    queue->next = NULL;

    return queue;
}

void enQueue(Node* queue, int data)
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = data;

    Node* iterator = queue;
    while (iterator->next)
    {
        iterator = iterator->next;
    }
    
    node->next = iterator->next;

    iterator->next = node;

    queue->data++;
}

int isEmpty(Node* queue)
{
    if (queue->data == 0 || queue->next == NULL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int deQueue(Node* queue)
{
    if(isEmpty(queue))
    {
        return ERRORS;
    }
    else
    {
        Node* node = queue->next;

        int data = node->data;

        queue->next = node->next;

        node->next = NULL;

        free(node);

        queue->data--;

        return data;
    }
}

void printQueue(Node* queue)
{
    Node* iterator = queue->next;
    while (iterator)
    {
        printf("%d -> ", iterator->data);
        iterator = iterator->next;
    }
    printf("NULL\n");
}

int main()
{
    Node* queue = initQueue();
    enQueue(queue, 1);
    enQueue(queue, 2);
    enQueue(queue, 3);
    enQueue(queue, 4);
    enQueue(queue, 5);
    printQueue(queue);

    while (queue->next)
    {
        int data = deQueue(queue);
        printQueue(queue);
        printf("The pop data is %d.\n",data);
    }

    return 0;
}