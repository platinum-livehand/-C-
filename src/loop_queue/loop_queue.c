#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5
#define TRUE 1
#define FALSE 0

typedef struct Queue 
{
    int front;
    int rear;
    int data[MAXSIZE];
}Queue;

Queue* initQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));

    queue->front = queue->rear = 0;
    
    return queue;
}

int isFull(Queue* queue)
{
    if ((queue->rear + 1) % MAXSIZE == queue->front)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int isEmpty(Queue* queue)
{
    if (queue->rear == queue->front)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int enQueue(Queue* queue, int data)
{
    if(isFull(queue))
    {
        return FALSE;
    }
    else
    {
        queue->data[queue->rear] = data;

        queue->rear = (queue->rear + 1) % MAXSIZE;

        return TRUE;
    }
}

int deQueue(Queue* queue)
{
    if(isEmpty(queue))
    {
        return FALSE;
    }
    else
    {
        int data = queue->data[queue->front];

        queue->front = (queue->front + 1) % MAXSIZE;

        return data;
    }
}

void printQueue(Queue* queue)
{
    int index = queue->front;

    int length = (queue->rear + MAXSIZE - queue->front) % MAXSIZE;
    for (int i = 0; i < length; i++)
    {
        printf("%d -> ", queue->data[index]);

        index = (index + 1) % MAXSIZE;
    }
    printf("NULL\n");
}

int main()
{
    Queue* queue = initQueue();
    
    for (int i = 1; isFull(queue) != TRUE; i++)
    {
        enQueue(queue, i);
        printf("The push data is %d.\n", i);
        printQueue(queue);
    }
    
    while (!isEmpty(queue))
    {   
        int data = deQueue(queue);
        printf("The pop data is %d.\n", data);
        printQueue(queue);
    }
    
    return 0;
}