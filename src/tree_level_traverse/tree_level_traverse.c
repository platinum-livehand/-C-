#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode
{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

// 循环队列
typedef struct QueueNode
{
    int num;
    TreeNode* data;
    struct QueueNode* pre;
    struct QueueNode* next;
}QueueNode;

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

        createTree(&((*root)->lchild), data, index);
        
        createTree(&((*root)->rchild), data, index);
    }
}

// 前序
void preOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        printf("%c ", root->data);

        preOrder(root->lchild);

        preOrder(root->rchild);
    }
}

void freeTree(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        freeTree(root->lchild);

        freeTree(root->rchild);

        free(root);
    }
}

QueueNode* initQueue()
{
    QueueNode* queue = (QueueNode*)malloc(sizeof(QueueNode));

    queue->num = 0;
    queue->data = NULL;
    queue->pre = queue;
    queue->next = queue;

    return queue;
}

int isEmpty(QueueNode* qNode)
{
    if(qNode->next == qNode)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

// 进队——尾插
void enQueue(TreeNode* root, QueueNode* qNode)
{
    QueueNode* tempNode = (QueueNode*)malloc(sizeof(QueueNode));

    tempNode->data = root;
    tempNode->pre = qNode->pre;
    tempNode->next = qNode;

    qNode->pre->next = tempNode;
    qNode->pre = tempNode;

    qNode->num++;
}

// 出队——先进先出
QueueNode* deQueue(QueueNode* qNode)
{
    if(isEmpty(qNode))
    {
        return NULL;
    }
    else
    {
        QueueNode* tempNode = qNode->next;

        qNode->next = tempNode->next;

        tempNode->next->pre = qNode;

        return tempNode;
    }
}

// 层次遍历
void levelTraverse(TreeNode* root, QueueNode* qNode)
{
    enQueue(root, qNode);
    while (!isEmpty(qNode))
    {
        QueueNode* tempNode = deQueue(qNode);

        printf("%c ", tempNode->data->data);
        
        if(tempNode->data->lchild)
        {
            enQueue(tempNode->data->lchild, qNode);
        }
        
        if(tempNode->data->rchild)
        {
            enQueue(tempNode->data->rchild, qNode);
        }
    }
}

int main()
{
    TreeNode* root = NULL;
    QueueNode* queue = initQueue();
    const char* data = "ABD##E##CF##G##";
    int index = 0;

    createTree(&root, data, &index);

    printf("前序遍历: \n");
    preOrder(root);
    printf("\n");

    printf("层次遍历: \n");
    levelTraverse(root, queue);
    printf("\n");

    freeTree(root);
    free(queue);

    return 0;
}