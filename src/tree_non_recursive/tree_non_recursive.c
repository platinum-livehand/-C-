#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode
{
    char data;
    int flag;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
} TreeNode;

void createTree(TreeNode** root, const char* data, int* index)
{
    char ch = data[*index];

    (*index)++;

    if(ch == '#')
    {
        *root = NULL;
    }
    else
    {
        *root = (TreeNode*)malloc(sizeof(TreeNode));

        (*root)->data = ch;

        (*root)->flag = TRUE;

        createTree(&((*root)->lchild), data, index);

        createTree(&((*root)->rchild), data, index);
    }
}

void freeTree(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }

    freeTree(root->lchild);
    freeTree(root->rchild);
    free(root);
}

typedef struct StackNode
{
    int num;
    TreeNode* data;
    struct StackNode* next;
} StackNode;

StackNode* initStack()
{
    StackNode* stack = (StackNode*)malloc(sizeof(StackNode));

    stack->data = NULL;
    stack->next = NULL;
    stack->num = 0;

    return stack;
}

int isEmpty(StackNode* stack)
{
    if (stack->next == NULL)
    {
        return TRUE;
    }
    
    return FALSE;
}

StackNode* getTopNode(StackNode* stack)
{
    return stack->next;
}

// 入栈——头插
void push(TreeNode* root, StackNode* stack)
{
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));

    node->data = root;
    node->next = stack->next;

    stack->next = node;
    (stack->num)++;
}

// 出栈——先进后出
TreeNode* pop(StackNode* stack)
{
    if(isEmpty(stack))
    {
        return NULL;
    }

    StackNode* node = stack->next;

    stack->next = node->next;

    (stack->num)--;

    TreeNode* temp = node->data;

    free(node);

    return temp;
}

void freeStack(StackNode* stack) 
{
    while (!isEmpty(stack)) 
    {
        pop(stack);
    }
    free(stack);
}

// 前序
void preOrder(TreeNode* root, StackNode* stack)
{
    TreeNode* node = root;

    while (node || !isEmpty(stack))
    {
        if(node)
        {
            printf("%c ", node->data);

            push(node, stack);

            node = node->lchild;
        }
        else
        {
            node = pop(stack);

            node = node->rchild;
        }
    }
}

// 中序
void inOrder(TreeNode* root, StackNode* stack)
{
    TreeNode* node = root;

    while (node || !isEmpty(stack))
    {
        if (node)
        {
            push(node, stack);

            node = node->lchild;
        }
        else
        {
            node = pop(stack);

            printf("%c ", node->data);

            node = node->rchild;
        }
    }
}

// 后序
void postOrder(TreeNode* root, StackNode* stack)
{
    TreeNode* node = root;

    while (node || !isEmpty(stack))
    {
        if(node)
        {
            push(node, stack);

            node = node->lchild;
        }
        else
        {
            TreeNode* top = getTopNode(stack)->data;

            if(top->rchild && top->rchild->flag)
            {
                push(top->rchild, stack);

                node = top->rchild->lchild;
            }
            else
            {
                top = pop(stack);

                printf("%c ", top->data);

                top->flag = FALSE;

                node = NULL;
            }
        }
    }
}

int main() {
    const char* data = "ABD##E##CF##G##";
    int index = 0;
    TreeNode* root = NULL;
    createTree(&root, data, &index);

    StackNode* stack = initStack();
    printf("Pre-order traversal: ");
    preOrder(root, stack);
    printf("\n");

    freeStack(stack);
    stack = initStack();

    printf("In-order traversal: ");
    inOrder(root, stack);
    printf("\n");

    freeStack(stack);
    stack = initStack();

    printf("Post-order traversal: ");
    postOrder(root, stack);
    printf("\n");

    freeTree(root);
    freeStack(stack);
    
    return 0;
}