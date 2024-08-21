#include <stdio.h>
#include <stdlib.h>

#define M 32767

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
    if (head->next == NULL || head->data == 0)
    {
        return 1;
    }
    
    return 0;
}

int pop(StackNode* head)
{
    if (!isEmpty(head))
    {
        StackNode* temp = head->next;
        
        head->next = temp->next;
        head->data--;

        int data = temp->data;

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
            graph->arcs[i][j] = *(arcs + graph->vexNum * i + j);

            if (graph->arcs[i][j] > 0 && graph->arcs[i][j] != M)
            {
                graph->arcNum++;
            }
        }
    }
}

void DFS(Graph* graph, int* visited, int index)
{
    printf("%c ", graph->vexs[index]);
    visited[index] = 1;

    for (int i = 0; i < graph->vexNum; i++)
    {
        if (visited[i] != 1 && graph->arcs[index][i] > 0 && graph->arcs[index][i] != M)
        {
            DFS(graph, visited, i);
        }
    }
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

int* findInDegrees(Graph* graph)
{
    int* inDegrees = (int*)malloc(sizeof(int) * graph->vexNum);
    for (int i = 0; i < graph->vexNum; i++)
    {
        inDegrees[i] = 0;
    }

    for (int i = 0; i < graph->vexNum; i++)
    {
        for (int j = 0; j < graph->vexNum; j++)
        {
            if (graph->arcs[i][j] > 0 && graph->arcs[i][j] != M)
            {
                inDegrees[j] += 1;
            }
        }
    }

    return inDegrees;
}

int* topoLogicalSort(Graph* graph)
{
    int* topo = (int*)malloc(sizeof(int) * graph->vexNum);

    int index = 0;

    int* inDegrees = findInDegrees(graph);

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
            if (graph->arcs[vex][i] > 0 && graph->arcs[vex][i] != M)
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

    free(inDegrees);

    return topo;
}

int getIndex(Graph* graph, int* topo, int j)
{
    for (int i = 0; i < graph->vexNum; i++)
    {
        if (topo[i] == j)
        {
            return i;
        }
    }

    return -1;
}

void criticalPath(Graph* graph)
{
    int* topo = topoLogicalSort(graph);

    int* early = (int*)malloc(sizeof(int) * graph->vexNum);
    int* late = (int*)malloc(sizeof(int) * graph->vexNum);
    for (int i = 0; i < graph->vexNum; i++)
    {
        early[i] = 0;
        late[i] = 0;
    }
    
    // 计算最早发生时间
    for (int i = 0; i < graph->vexNum; i++)
    {
        int max = 0;

        for (int j = 0; j < graph->vexNum; j++)
        {
            if (graph->arcs[j][topo[i]] > 0 && graph->arcs[j][topo[i]] != M)
            {
                // 节点索引 对应于 topo 序列的索引，节点索引在 topo 序列中的位置
                int index = getIndex(graph, topo, j);

                if (early[index] + graph->arcs[j][topo[i]] > max)
                {
                    max = early[index] + graph->arcs[j][topo[i]];
                }
            }
        }

        early[i] = max;
    }

    printf("Early times: ");
    for (int i = 0; i < graph->vexNum; i++)
    {
        printf("%d ", early[i]);
    }
    printf("\n");
    

    // 计算最晚发生时间
    late[graph->vexNum - 1] = early[graph->vexNum - 1];

    for (int i = graph->vexNum - 2; i >= 0; i--)
    {
        int min = M;

        for (int j = 0; j < graph->vexNum; j++)
        {
            if (graph->arcs[topo[i]][j] > 0 && graph->arcs[topo[i]][j] != M)
            {
                int index = getIndex(graph, topo, j);

                if (late[index] - graph->arcs[topo[i]][j] < min)
                {
                    min = late[index] - graph->arcs[topo[i]][j];
                }
            } 
        }

        late[i] = min;
    }
    
    printf("Late times: ");
    for (int i = 0; i < graph->vexNum; i++)
    {
        printf("%d ", late[i]);
    }
    printf("\n");

    printf("Critical Path:\n");
    for (int i = 0; i < graph->vexNum; i++)
    {
        for (int j = 0; j < graph->vexNum; j++)
        {
            if (graph->arcs[i][j] > 0 && graph->arcs[i][j] != M)
            {
                int start = getIndex(graph, topo, i);
                int end = getIndex(graph, topo, j);

                if (late[end] - graph->arcs[i][j] == early[start])
                {
                    printf("Activity %c -> %c is on the critical path\n", graph->vexs[i], graph->vexs[j]);
                }
            }
        }
    }

    free(topo);
    free(early);
    free(late);
}

int main(int argc, char* argv[])
{
    Graph* G = initGraph(9);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[] = {
        0, 6, 4, 5, M, M, M, M, M,
        M, 0, M, M, 1, M, M, M, M,
        M, M, 0, M, 1, M, M, M, M,
        M, M, M, 0, M, 2, M, M, M,
        M, M, M, M, 0, M, 9, 7, M,
        M, M, M, M, M, 0, M, 4, M,
        M, M, M, M, M, M, 0, M, 2,
        M, M, M, M, M, M, M, 0, 4,
        M, M, M, M, M, M, M, M, 0
    };
    createGraph(G, "012345678", arcs);
    DFS(G, visited, 0);
    printf("\n");

    // topoLogicalSort(G);
    criticalPath(G);

    freeGraph(G);
    free(visited);

    return 0;
}