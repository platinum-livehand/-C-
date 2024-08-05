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

// 入队——尾插
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

// 出队——先进先出
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
    // 初始化队列
    Node* queue = initQueue();
    printf("初始化队列: \n");
    printQueue(queue);

    // 入队
    enQueue(queue, 1);
    enQueue(queue, 2);
    enQueue(queue, 3);
    printf("入队 1, 2, 3: \n");
    printQueue(queue);

    // 出队
    int dequeued = deQueue(queue);
    if (dequeued != ERRORS)
        printf("出队元素: %d\n", dequeued);
    printf("出队后: \n");
    printQueue(queue);

    dequeued = deQueue(queue);
    if (dequeued != ERRORS)
        printf("出队元素: %d\n", dequeued);
    printf("出队后: \n");
    printQueue(queue);

    dequeued = deQueue(queue);
    if (dequeued != ERRORS)
        printf("出队元素: %d\n", dequeued);
    printf("出队后: \n");
    printQueue(queue);

    // 检查队列是否为空
    if (isEmpty(queue))
        printf("队列为空\n");
    else
        printf("队列不为空\n");

    return 0;
}