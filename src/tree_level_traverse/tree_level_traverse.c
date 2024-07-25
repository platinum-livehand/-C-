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

typedef struct QueueNode
{
    int num;
    TreeNode* data;
    struct QueueNode* pre;
    struct QueueNode* next;
}QueueNode;

void createTree(TreeNode** tNode, const char* data, int* index)
{
    char ch = data[*index];

    (*index)++;

    if(ch == '#')
    {
        *tNode = NULL;
    }
    else
    {
        *tNode = (TreeNode*)malloc(sizeof(TreeNode));

        (*tNode)->data = ch;

        createTree(&((*tNode)->lchild), data, index);
        
        createTree(&((*tNode)->rchild), data, index);
    }
}

// 前序
void preOrder(TreeNode* tNode)
{
    if(tNode == NULL)
    {
        return;
    }
    else
    {
        printf("%c ", tNode->data);

        preOrder(tNode->lchild);

        preOrder(tNode->rchild);
    }
}

void freeTree(TreeNode* tNode)
{
    if (tNode == NULL)
    {
        return;
    }
    else
    {
        freeTree(tNode->lchild);

        freeTree(tNode->rchild);

        free(tNode);
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

void enQueue(TreeNode* tNode, QueueNode* qNode)
{
    QueueNode* tempNode = (QueueNode*)malloc(sizeof(QueueNode));

    tempNode->data = tNode;
    tempNode->pre = qNode->pre;
    tempNode->next = qNode;

    qNode->pre->next = tempNode;
    qNode->pre = tempNode;

    qNode->num++;
}

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

void levelTraverse(TreeNode* tNode, QueueNode* qNode)
{
    enQueue(tNode, qNode);
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

    printf("前序遍历: ");
    preOrder(root);
    printf("\n");

    printf("层次遍历: ");
    levelTraverse(root, queue);
    printf("\n");

    freeTree(root);
    free(queue);

    return 0;
}