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
    if(stack->data ==0 || stack->next == NULL)  
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
    Node* stack = initStack();
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    push(stack, 5);
    printStack(stack);

    int stack_element_1 = pop(stack);
    printf("The pop element is %d.\n", stack_element_1);
    int stack_element_2 = pop(stack);
    printf("The pop element is %d.\n", stack_element_2);
    printStack(stack);

    while (pop(stack) != ERRORS)
    {
        printStack(stack);
    }
    printf("The stack is empty!");
    
    return 0;
}