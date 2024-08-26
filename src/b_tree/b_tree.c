#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int level;
    int keyNum;
    int childNum;
    int* keys;
    struct TreeNode** childs;
    struct TreeNode* parent;
} TreeNode;

TreeNode* initTree(int level)
{
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->level = level;
    root->keyNum = 0;
    root->childNum = 0;
    root->keys = (int*)malloc(sizeof(int) * (level + 1));
    root->childs = (TreeNode**)malloc(sizeof(TreeNode*) * level);
    int i = 0;
    while (i < level)
    {
        root->keys[i] = 0;
        root->childs[i] = NULL;
        i++;
    }
    root->keys[i] = 0;
    root->parent = NULL;

    return root;
}

int findSuiteIndex(TreeNode* node, int data)
{
    int index = 1;
    while (data > node->keys[index] && index <= node->keyNum)
    {
        index++;
    }
    
    return index;
}

void addData(TreeNode* node, int data, TreeNode** root)
{
    int index = findSuiteIndex(node, data);
    for (int i = node->keyNum; i >= index; i--)
    {
        node->keys[i + 1] = node->keys[i];
    }
    
    node->keys[index] = data;
    node->keyNum++;

    if (node->keyNum == node->level)
    {
        int mid = (node->level + 1) / 2;

        TreeNode* lchild = initTree(node->level);
        TreeNode* rchild = initTree(node->level);

        for (int i = 1; i < mid; i++)
        {
            addData(lchild, node->keys[i], root);
        }
    
        for (int i = mid + 1; i <= node->keyNum; i++)
        {
            addData(rchild, node->keys[i], root);
        }
            
        for (int i = 0; i < mid; i++)
        {
            lchild->childs[i] = node->childs[i];

            if (node->childs[i] != NULL)
            {
                lchild->childs[i]->parent = lchild;
                lchild->childNum++;
            }
        }

        for (int i = mid, j = 0; i < node->childNum; i++, j++)
        {
            rchild->childs[j] = node->childs[i];

            if (node->childs[i] != NULL)
            {
                rchild->childs[j]->parent = rchild;
                rchild->childNum++;
            }
        }
        
        if (node->parent == NULL)
        {
            TreeNode* parent = initTree(node->level);

            addData(parent, node->keys[mid], root);

            parent->childs[0] = lchild;
            parent->childs[1] = rchild;
            parent->childNum = 2;

            lchild->parent = parent;
            rchild->parent = parent;

            *root = parent;
        }
        else
        {
            int parent_index = findSuiteIndex(node->parent, node->keys[mid]);

            lchild->parent = node->parent;
            rchild->parent = node->parent;

            node->parent->childs[parent_index - 1] = lchild;

            if (node->parent->childs[parent_index] != NULL)
            {
                for (int i = node->parent->childNum - 1; i >= parent_index; i--)
                {
                    node->parent->childs[i + 1] = node->parent->childs[i];
                }
            }

            node->parent->childs[parent_index] = rchild;

            node->parent->childNum++;

            addData(node->parent, node->keys[mid], root);
        }
    }
}

TreeNode* findSuiteLeafNode(TreeNode* node, int data)
{
    if (node->childNum == 0)
    {
        return node;
    }
    else
    {
        int index = findSuiteIndex(node, data);
        return findSuiteLeafNode(node->childs[index - 1], data);
    }
}

void insert(TreeNode** root, int data)
{
    TreeNode* node = findSuiteLeafNode(*root, data);
    addData(node, data, root);
}

void printTree(TreeNode* node, int depth)
{
    if (node == NULL) return;

    for (int i = 0; i < depth; i++)
    {
        printf("    ");
    }

    printf("[");
    for (int i = 1; i <= node->keyNum; i++)
    {
        printf("%d", node->keys[i]);
        if (i < node->keyNum)
        {
            printf(", ");
        }
    }
    printf("]\n");

    for (int i = 0; i < node->childNum; i++)
    {
        printTree(node->childs[i], depth + 1);
    }
}

int main(int argc, char* argv[])
{
    printf("B-Tree Test\n");

    TreeNode* root = initTree(5);

    // 插入测试数据
    for (int i = 1; i < 16; i++)
    {
        insert(&root, i);
    }

    // 打印B树结构
    printTree(root, 0);

    return 0;
}