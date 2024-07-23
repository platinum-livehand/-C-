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
    // 初始化队列
    Queue* queue = initQueue();

    // 入队操作
    enQueue(queue, 10);
    enQueue(queue, 20);
    enQueue(queue, 30);
    enQueue(queue, 40);

    // 打印队列内容
    printf("当前队列内容: ");
    printQueue(queue);

    // 尝试入队直到队列满
    if (!enQueue(queue, 50))
    {
        printf("队列已满，无法加入元素50\n");
    }

    // 打印队列内容
    printf("当前队列内容: ");
    printQueue(queue);

    // 出队操作并打印
    printf("出队元素: %d\n", deQueue(queue));
    printf("出队元素: %d\n", deQueue(queue));

    // 打印队列内容
    printf("当前队列内容: ");
    printQueue(queue);

    // 继续入队操作
    enQueue(queue, 50);
    enQueue(queue, 60);

    // 打印队列内容
    printf("当前队列内容: ");
    printQueue(queue);

    // 尝试入队直到队列满
    if (!enQueue(queue, 70))
    {
        printf("队列已满，无法加入元素70\n");
    }

    // 打印队列内容
    printf("当前队列内容: ");
    printQueue(queue);

    // 释放队列内存
    free(queue);
    
    return 0;
}