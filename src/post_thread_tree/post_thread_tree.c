#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode
{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    struct TreeNode* parent;
    int ltag;
    int rtag;
} TreeNode;

void createTree(TreeNode** root, const char* data, int* index, TreeNode* parent)
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
        (*root)->lchild = NULL;
        (*root)->rchild = NULL;
        (*root)->parent = parent;
        (*root)->ltag = FALSE;
        (*root)->rtag = FALSE;

        createTree(&((*root)->lchild), data, index, *root);
        createTree(&((*root)->rchild), data, index, *root);
    }
}

void postThreadTree(TreeNode* root, TreeNode** pre)
{
    if(root == NULL)
    {
        return;
    }

    postThreadTree(root->lchild, pre);
    postThreadTree(root->rchild, pre);

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
}

TreeNode* getFirst(TreeNode* root)
{
    while (root->ltag == FALSE)
    {
        root = root->lchild;
    }

    if(root->rtag == FALSE)
    {
        root = getFirst(root->rchild);
    }
    
    return root;
}

TreeNode* getNext(TreeNode* root)
{
    // 节点存在右线索
    if(root->rtag == TRUE)
    {
        return root->rchild;
    }

    // // 节点为根节点
    // if(root->parent == NULL)
    // {
    //     return root->parent;
    // }

    // // 节点为父节点的右孩子
    // if(root->parent->rchild == root)
    // {
    //     return root->parent;
    // }

    // // 节点为父节点的左线索
    // if (root->parent->ltag == TRUE)
    // {
    //     return root->parent;
    // }

    // 节点为父节点的左孩子
    if(root->parent != NULL && root->parent->lchild == root && root->parent->ltag == FALSE)
    {
        return getFirst(root->parent->rchild);
    }
    else
    {
        return root->parent;
    }
}

void postOrderThreadTraversal(TreeNode* root) 
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
    TreeNode* root = NULL;
    int index = 0;
    const char* data = "ABD#F##E##C##"; 

    createTree(&root, data, &index, NULL);

    TreeNode* pre = NULL;
    postThreadTree(root, &pre);

    printf("Post-order thread traversal: ");
    postOrderThreadTraversal(root);

    freeThreadedTree(root);

    return 0;
}