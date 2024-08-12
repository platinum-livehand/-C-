#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
} TreeNode;

void bstInsert(TreeNode** node, int data)
{
    if (*node == NULL)
    {
        *node = (TreeNode*)malloc(sizeof(TreeNode));
        (*node)->data = data;
        (*node)->lchild = NULL;
        (*node)->rchild = NULL;
    }
    else
    {
        if ((*node)->data < data)
        {
            bstInsert(&((*node)->rchild), data);
        }
        else if ((*node)->data > data)
        {
            bstInsert(&((*node)->lchild), data);
        }
        else
        {
            return;
        }
    }
}

TreeNode* bstSearch(TreeNode* root, int data)
{
    if (root ==  NULL)
    {
        return NULL;
    }
    
    if (root->data == data)
    {
        return root;
    }
    else if (root->data < data)
    {
        return bstSearch(root->rchild, data);
    }
    else
    {
        return bstSearch(root->lchild, data);
    }
}

void preOrder(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    
    printf("%d ", root->data);

    preOrder(root->lchild);
    preOrder(root->rchild);
}

void freeTree(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }

    freeTree(root->lchild);

    freeTree(root->rchild);

    free(root);
}

int main(int argc, char* argv[])
{
    TreeNode* root = NULL;
    
    bstInsert(&root, 50);
    bstInsert(&root, 30);
    bstInsert(&root, 70);
    bstInsert(&root, 20);
    bstInsert(&root, 40);
    bstInsert(&root, 60);
    bstInsert(&root, 80);

    printf("Pre-order traversal: ");
    preOrder(root);
    printf("\n");

    TreeNode* searchNode = bstSearch(root, 70);
    if (searchNode != NULL)
    {
        printf("Found node with data: %d\n", searchNode->data);
    }
    else
    {
        printf("Node not found.\n");
    }

    freeTree(root);

    return 0;
}