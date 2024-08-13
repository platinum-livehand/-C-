#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define nullptr -1

typedef struct TreeNode
{
    int weight;
    int parent;
    int lchild;
    int rchild;
} TreeNode;

typedef struct HFTree
{
    TreeNode* data;
    int length;
} HFTree;

HFTree* initHFTree(int* weight, int length)
{
    if (weight == NULL)
    {
        return NULL;
    }
    
    HFTree* head = (HFTree*)malloc(sizeof(HFTree));
    head->data = (TreeNode*)malloc(sizeof(TreeNode) * (2 * length - 1));
    head->length = length;

    for (int i = 0; i < length; i++)
    {
        head->data[i].weight = weight[i];
        head->data[i].parent = nullptr;
        head->data[i].lchild = nullptr;
        head->data[i].rchild = nullptr;
    }
    
    return head;
}

int* selectMin(HFTree* head)
{
    if (head == NULL)
    {
        return NULL;
    }

    int min = INT_MAX;
    int secondMin = INT_MAX;
    int minIndex = 0;
    int secondIndex = 0;

    for (int i = 0; i < head->length; i++)
    {
        if (head->data[i].parent == nullptr)
        {
            if (head->data[i].weight < min)
            {
                min = head->data[i].weight;
                minIndex = i;
            }
        }
    }
    
    for (int i = 0; i < head->length; i++)
    {
        if (head->data[i].parent == nullptr && i != minIndex)
        {
            if (head->data[i].weight < secondMin)
            {
                secondMin = head->data[i].weight;
                secondIndex = i;
            }
        }
    }

    int* res = (int*)malloc(sizeof(int) * 2);
    res[0] = minIndex;
    res[1] = secondIndex;

    return res;
}

void createHFTree(HFTree* head)
{
    if (head == NULL)
    {
        return;
    }

    int* res = (int*)malloc(sizeof(int) * 2);
    int min;
    int secondeMin;
    int length = 2 * head->length - 1;

    for (int i = head->length; i < length; i++)
    {
        res = selectMin(head);
        min = res[0];
        secondeMin = res[1];

        head->data[i].weight = head->data[min].weight + head->data[secondeMin].weight;

        head->data[i].parent = nullptr;
        head->data[i].lchild = min;
        head->data[i].rchild = secondeMin;

        head->data[min].parent = i;
        head->data[secondeMin].parent = i;

        head->length ++;
    }

    free(res);
}

void preOrder(HFTree* head, int index)
{
    if (head == NULL || index == nullptr)
    {
        return;
    }

    printf("%d ", head->data[index].weight);

    preOrder(head, head->data[index].lchild);
    preOrder(head, head->data[index].rchild);
}

void freeHFTree(HFTree* head)
{
    if (head == NULL)
    {
        return;
    }

    free(head->data);
    free(head);
}

int main(int argc, char* argv[])
{
    int weights[] = {1, 2, 3, 4};
    int length = sizeof(weights) / sizeof(weights[0]);

    HFTree* huffmanTree = initHFTree(weights, length);

    createHFTree(huffmanTree);

    printf("Pre-order traversal of Huffman Tree:\n");
    preOrder(huffmanTree, huffmanTree->length - 1);
    printf("\n");

    freeHFTree(huffmanTree);

    return 0;
}