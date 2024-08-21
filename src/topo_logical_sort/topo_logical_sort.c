#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode
{
    struct StackNode* next;
    int data;
} StackNode;

StackNode* initStack()
{
    StackNode* head = (StackNode*)malloc(sizeof(StackNode));

    head->next = NULL;
    head->data = 0;

    return head;
}

int isEmpty(StackNode* head)
{
    if (head->next || head->data != 0)
    {
        return 0;
    }

    return 1;
}

int pop(StackNode* head)
{
    if (!isEmpty(head))
    {
        StackNode* temp = head->next;

        int data = temp->data;

        head->next = temp->next;

        head->data--;

        free(temp);

        return data;
    }

    return -1;
}

void push(StackNode* head, int data)
{
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));

    node->data = data;
    node->next = head->next;

    head->next = node;
    head->data++;
}

typedef struct Graph
{
    char* vexs;
    int** arcs;
    int vexNum;
    int arcNum;
} Graph;

Graph* initGraph(int vexNum)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vexs = (char*)malloc(sizeof(char) * vexNum);
    graph->arcs = (int**)malloc(sizeof(int*) * vexNum);
    for (int i = 0; i < vexNum; i++)
    {
        graph->arcs[i] = (int*)malloc(sizeof(int) * vexNum);
    }
    graph->vexNum = vexNum;
    graph->arcNum = 0;

    return graph;
}

void createGraph(Graph* graph, char* vexs, int* arcs)
{
    for (int i = 0; i < graph->vexNum; i++)
    {
        graph->vexs[i] = vexs[i];
        for (int j = 0; j < graph->vexNum; j++)
        {
            graph->arcs[i][j] = *(arcs + i * graph->vexNum + j);

            if (graph->arcs[i][j])
            {
                graph->arcNum++;
            }
        }
    }

    graph->arcNum /= 2;
}

void freeGraph(Graph* graph)
{
    for (int i = 0; i < graph->vexNum; i++)
    {
        free(graph->arcs[i]);
    }
    free(graph->arcs);
    free(graph->vexs);
    free(graph);
}

void DFS(Graph* graph, int* visited, int index)
{
    printf("%c ", graph->vexs[index]);

    visited[index] = 1;

    for (int i = 0; i < graph->vexNum; i++)
    {
        if (visited[i] != 1 && graph->arcs[index][i])
        {
            DFS(graph, visited, i);
        }
    }
}

int* findInDegrees(Graph* graph)
{
    int* inDegress = (int*)malloc(sizeof(int) * graph->vexNum);

    for (int i = 0; i < graph->vexNum; i++)
    {
        inDegress[i] = 0;
    }
    
    for (int i = 0; i < graph->vexNum; i++)
    {
        for (int j = 0; j < graph->vexNum; j++)
        {
            if (graph->arcs[i][j])
            {
                inDegress[j] += 1;
            }
        }
    }

    return inDegress;
}

void topoLogicalSort(Graph* graph)
{
    int* topo = (int*)malloc(sizeof(int) * graph->vexNum);
    int index = 0;

    int* inDegrees = findInDegrees(graph);

    // for (int i = 0; i < graph->vexNum; i++)
    // {
    //     printf("%d ", inDegrees[i]);
    // }
    // printf("\n");

    StackNode* stack = initStack();

    for (int i = 0; i < graph->vexNum; i++)
    {
        if (inDegrees[i] == 0)
        {
            push(stack, i);   
        }
    }
    
    while (!isEmpty(stack))
    {
        int vex = pop(stack);

        topo[index++] = vex;

        for (int i = 0; i < graph->vexNum; i++)
        {
            if (graph->arcs[vex][i])
            {
                inDegrees[i]--;
                if (inDegrees[i] == 0)
                {
                    push(stack, i);
                }
            }
        }
    }

    // 检查是否成功生成拓扑排序
    if (index != graph->vexNum)
    {
        printf("Graph has a cycle, no valid topological order.\n");
    }
    else
    {
        printf("Topological Sort: ");
        for (int i = 0; i < graph->vexNum; i++)
        {
            printf("%c ", graph->vexs[topo[i]]);
        }
        printf("\n");
    }

    free(topo);
    free(inDegrees);
}

int main(int argc, char* argv[])
{
    Graph* G = initGraph(6);
    int* visited = (int*)malloc(sizeof(int) * G->vexNum);
    for (int i = 0; i < G->vexNum; i++)
        visited[i] = 0;

    int arcs[] = {
        0,1,1,1,0,0,
        0,0,0,0,0,0,
        0,1,0,0,1,0,
        0,0,0,0,1,0,
        0,0,0,0,0,0,
        0,0,0,1,1,0
    };
    createGraph(G, "123456", arcs);

    printf("DFS: ");
    DFS(G, visited, 0);
    printf("\n");

    topoLogicalSort(G);

    freeGraph(G);
    free(visited);

    return 0;
}