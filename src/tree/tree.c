#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

void createTree(TreeNode** node, const char* data, int* index)
{
    char ch = data[*index];
    
    (*index)++;

    if(ch == '#')
    {
        *node = NULL;
    }
    else
    {
        *node = (TreeNode*)malloc(sizeof(TreeNode));

        (*node)->data = ch;

        // 创建左分支
        createTree(&((*node)->lchild), data, index);

        // 创建右分支
        createTree(&((*node)->rchild), data, index);
    }
}

// 前序
void preOrder(TreeNode* node)
{
    if(node == NULL)
    {
        return;
    }
    else
    {
        printf("%c ", node->data);

        preOrder(node->lchild);

        preOrder(node->rchild);
    }
}

// 中序
void inOrder(TreeNode* node)
{
    if(node == NULL)
    {
        return;
    }
    else
    {
        inOrder(node->lchild);

        printf("%c ", node->data);

        inOrder(node->rchild);
    }
}

// 后序
void postOrder(TreeNode* node)
{
    if(node == NULL)
    {
        return;
    }
    else
    {
        postOrder(node->lchild);

        postOrder(node->rchild);

        printf("%c ", node->data);
    }
    
}

void freeTree(TreeNode* node)
{
    if (node == NULL)
    {
        return;
    }
    else
    {
        freeTree(node->lchild);

        freeTree(node->rchild);

        free(node);
    }
}

int main()
{
    TreeNode* root = NULL;
    const char* data = "ABD##E##CF##G##";
    int index = 0;

    createTree(&root, data, &index);

    printf("前序遍历: \n");
    preOrder(root);
    printf("\n");

    printf("中序遍历: \n");
    inOrder(root);
    printf("\n");

    printf("后序遍历: \n");
    postOrder(root);
    printf("\n");

    freeTree(root);

    return 0;
}