#include <stdio.h>
#include <stdlib.h>

#define ERRORS -1

typedef struct Node
{
    int data;
    struct Node* next;
}Node;

Node* initStack()
{
    Node* stack = (Node*)malloc(sizeof(Node));
    stack->data = 0;
    stack->next = NULL;

    return stack;
}

int isEmpty(Node* stack)
{
    if(stack->data == 0 || stack->next == NULL)  
        return 1;
    else
        return 0;
}

int pop(Node* stack)
{
    if (isEmpty(stack))
    {
        return ERRORS;
    }
    else
    {
        Node* node = stack->next;

        int data = node->data;

        stack->next = node->next;

        free(node);

        stack->data--;

        return data;
    }
}

void push(Node* stack, int data)
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = data;
    node->next = stack->next;

    stack->next = node;
    stack->data++;
}

void printStack(Node* stack)
{
    Node* iterator = stack->next;
    while (iterator)
    {
        printf("%d->", iterator->data);
        iterator = iterator->next;
    }
    printf("NULL\n");
}

int main()
{
    // 初始化栈
    Node* stack = initStack();

    // 压入元素
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    // 打印栈内容
    printf("当前栈内容: ");
    printStack(stack);

    // 弹出元素并打印
    printf("弹出元素: %d\n", pop(stack));
    printf("弹出元素: %d\n", pop(stack));
    
    // 打印栈内容
    printf("当前栈内容: ");
    printStack(stack);

    // 再次压入元素
    push(stack, 40);
    push(stack, 50);

    // 打印栈内容
    printf("当前栈内容: ");
    printStack(stack);

    // 释放栈内存
    while (!isEmpty(stack))
    {
        pop(stack);
    }
    free(stack);
    
    return 0;
}