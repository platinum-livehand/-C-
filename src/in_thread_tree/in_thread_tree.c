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

void inThreadTree(TreeNode* root, TreeNode** pre)
{
    if(root == NULL)
    {
        return;
    }

    inThreadTree(root->lchild, pre);

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

    inThreadTree(root->rchild, pre);
}

TreeNode* getFirst(TreeNode* root)
{
    while (root->ltag == FALSE)
    {
        root = root->lchild;
    }
    
    return root;
}

TreeNode* getNext(TreeNode* root)
{
    if(root->rtag == TRUE)
    {
        return root->rchild;
    }
    else
    {
        return getFirst(root->rchild);
    }
}

void inOrderThreadTraversal(TreeNode* root) 
{
    TreeNode* node = getFirst(root);

    while (node != NULL) 
    {
        printf("%c ", node->data);
        node = getNext(node);
    }
    printf("\n");
}

void freeThreadedTree(TreeNode* root) 
{
    TreeNode* curr = getFirst(root);
    TreeNode* next = NULL; 
    
    while (curr != NULL) 
    {
        next = getNext(curr);
        free(curr);
        curr = next;
    }
}

int main() 
{
    const char* data = "ABD#F##E##C##";
    int index = 0;
    TreeNode* root = NULL;
    createTree(&root, data, &index);

    TreeNode* pre = NULL;
    inThreadTree(root, &pre);

    pre->rchild = NULL;
    pre->rtag = TRUE;

    printf("In-order thread traversal: ");
    inOrderThreadTraversal(root);

    freeThreadedTree(root);

    return 0;
}