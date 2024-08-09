#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode
{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    int ltag;
    int rtag;
} TreeNode;

void createTree(TreeNode** root, const char* data, int* index)
{
    char ch = data[*index];

    (*index)++;

    if (ch == '#')
    {
        *root = NULL;
    }
    else
    {
        *root = (TreeNode*)malloc(sizeof(TreeNode));

        (*root)->data = ch;
        (*root)->ltag = FALSE;
        (*root)->rtag = FALSE;

        createTree(&((*root)->lchild), data, index);

        createTree(&((*root)->rchild), data, index);
    }
}

void preThreadTree(TreeNode* root, TreeNode** pre)
{
    if(root == NULL)
    {
        return;
    }

    if(root->lchild == NULL)
    {
        root->lchild = *pre;
        root->ltag = TRUE;
    }

    if((*pre) != NULL && (*pre)->rchild == NULL)
    {
        (*pre)->rchild = root;
        (*pre)->rtag = TRUE;
    }

    *pre = root;

    if(root->ltag == FALSE)
    {
        preThreadTree(root->lchild, pre);
    }
    preThreadTree(root->rchild, pre);
}

TreeNode* getNext(TreeNode* root)
{
    if(root->rtag == TRUE || root->ltag == TRUE)
    {
        return root->rchild;
    }
    else
    {
        return root->lchild;
    }
}

void preOrderThreadTraversal(TreeNode* root) 
{
    while (root != NULL)
    {
        printf("%c ", root->data);

        root = getNext(root);
    }
    printf("\n");
}

void freeThreadedTree(TreeNode* root) 
{
    TreeNode* next = NULL;

    while (root != NULL)
    {
        next = getNext(root);

        free(root);

        root = next;
    }
}

int main()
{
    TreeNode* root = NULL;
    int index = 0;
    const char* data = "ABD#F##E##C##";
    
    createTree(&root, data, &index);

    TreeNode* pre = NULL;
    preThreadTree(root, &pre);

    printf("Pre-order thread traversal: ");
    preOrderThreadTraversal(root);
    

    freeThreadedTree(root);

    return 0;
}