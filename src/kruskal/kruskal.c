#include <stdio.h>
#include <stdlib.h>

#define M 32767

typedef struct Graph
{
    char* vexs;
    int** arcs;
    // vertex 顶点的个数
    int vexNum;
    // arc 弧的个数
    int arcNum;
} Graph;

typedef struct Edge
{
    int start;
    int end;
    int weight;
} Edge;

Edge* initEdge(Graph* graph)
{
    Edge* edge = (Edge*)malloc(sizeof(Edge) * graph->arcNum);

    int index = 0;

    for (int i = 0; i < graph->vexNum; i++)
    {
        for (int j = i + 1; j < graph->vexNum; j++)
        {
            if (graph->arcs[i][j] != M)
            {
                edge[index].start = i;
                edge[index].end = j;
                edge[index].weight = graph->arcs[i][j];

                index++;
            }
        }
    }
    
    return edge;
}

void sortEdge(Edge* edge, Graph* graph)
{
    Edge temp;

    // 冒泡排序
    for (int i = 0; i < graph->arcNum - 1; i++)
    {
        for (int j = 0; j < graph->arcNum - 1 - i; j++)
        {
            if (edge[j].weight > edge[j + 1].weight)
            {
                temp = edge[j];
                edge[j] = edge[j + 1];
                edge[j + 1] = temp;
            }
        }
    }
}

void kruskal(Graph* graph)
{
    // 连通数组--初始状态只需要不重复即可
    int* connected = (int*)malloc(sizeof(int) * graph->vexNum);
    for (int i = 0; i < graph->vexNum; i++)
    {
        connected[i] = i + 7;
    }

    Edge* edge = initEdge(graph);

    sortEdge(edge, graph);

    int start = 0;
    int end = 0;

    for (int i = 0; i < graph->arcNum; i++)
    {
        start = connected[edge[i].start];
        end = connected[edge[i].end]; 

        if (start != end)
        {
            printf("v%c -> v%c, weight = %d\n", graph->vexs[edge[i].start], graph->vexs[edge[i].end], edge[i].weight);

            for (int j = 0; j < graph->vexNum; j++)
            {
                if (connected[j] == end)
                {
                    connected[j] = start;
                }
            }
        }
    }

    free(connected);
    free(edge);
}

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

            if (graph->arcs[i][j] != 0 && graph->arcs[i][j] != M)
            {
                graph->arcNum++;
            }
        }
    }
    
    graph->arcNum /= 2;
}

void DFS(Graph* graph, int* visited, int index)
{
    printf("%c ", graph->vexs[index]);

    visited[index] = 1;

    for (int i = 0; i < graph->vexNum; i++)
    {
        if (visited[i] != 1 && graph->arcs[index][i] != M && graph->arcs[index][i] != 0)
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

int main(int argc, char* argv[])
{
    const int vexNum = 6;
    char vexs[] = {'1', '2', '3', '4', '5', '6'};
    int arcs[] = {
        0, 6, 1, 5, M, M,
        6, 0, 5, M, 3, M,
        1, 5, 0, 5, 6, 4,
        5, M, 5, 0, M, 2,
        M, 3, 6, M, 0, 6,
        M, M, 4, 2, 6, 0
    };

    Graph* graph = initGraph(vexNum);
    createGraph(graph, vexs, arcs);

    int visited[6] = {0};

    printf("DFS: ");
    DFS(graph, visited, 0);
    printf("\n");

    printf("\nKruskal's MST:\n");
    kruskal(graph);

    freeGraph(graph);

    return 0;
}