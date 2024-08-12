#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    int height;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
} TreeNode;

int getHeight(TreeNode* node)
{
    return node ? node->height : 0;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void rrRotation(TreeNode* node, TreeNode** root)
{
    TreeNode* temp = node->rchild;
    node->rchild = temp->lchild;
    temp->lchild = node;

    node->height = max(getHeight(node->lchild), getHeight(node->rchild)) + 1;
    temp->height = max(getHeight(temp->lchild), getHeight(temp->rchild)) + 1;

    *root = temp;
}

void llRotation(TreeNode* node, TreeNode** root)
{
    TreeNode* temp = node->lchild;
    node->lchild = temp->rchild;
    temp->rchild = node;

    node->height = max(getHeight(node->lchild), getHeight(node->rchild)) + 1;
    temp->height = max(getHeight(temp->lchild), getHeight(temp->rchild)) + 1;

    *root = temp;
}

void lrRotation(TreeNode* node, TreeNode** root)
{
    rrRotation(node->lchild, &(node->lchild));
    llRotation(node, root);
}

void rlRotation(TreeNode* node, TreeNode** root)
{
    llRotation(node->rchild, &(node->rchild));
    rrRotation(node, root);
}

void avlInsert(TreeNode** root, int data)
{
    if ((*root) == NULL)
    {
        *root = (TreeNode*)malloc(sizeof(TreeNode));
        (*root)->data = data;
        (*root)->height = 0;
        (*root)->lchild = NULL;
        (*root)->rchild = NULL;
    }
    else
    {
        if (data > (*root)->data)
        {
            avlInsert(&((*root)->rchild), data);

            int lHeight = getHeight((*root)->lchild);
            int rHeight = getHeight((*root)->rchild);

            if (rHeight - lHeight == 2)
            {
                if (data > (*root)->rchild->data)
                {
                    rrRotation(*root, root);
                }
                else
                {
                    rlRotation(*root, root);
                }
            }
        }
        else if (data < (*root)->data)
        {
            avlInsert(&((*root)->lchild), data);

            int lHeight = getHeight((*root)->lchild);
            int rHeight = getHeight((*root)->rchild);

            if(lHeight - rHeight == 2)
            {
                if (data < (*root)->lchild->data)
                {
                    llRotation(*root, root);
                }
                else
                {
                    lrRotation(*root, root);
                }
            }
        }
        else
        {
            return;
        }
    }

    (*root)->height = max(getHeight((*root)->lchild), getHeight((*root)->rchild)) + 1;
}

void preOrder(TreeNode* root)
{
    if(root == NULL)
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

int main (int argc, char* argv[])
{
    TreeNode* root = NULL;

    avlInsert(&root, 8);
    avlInsert(&root, 7);
    avlInsert(&root, 9);
    avlInsert(&root, 5);
    avlInsert(&root, 6);

    printf("Pre-order traversal: ");
    preOrder(root);
    printf("\n");

    freeTree(root);

    return 0;
}