#include <stdio.h>
#include <stdlib.h>

#define M 32767

typedef struct Graph
{
    char* vexs;
    int** arcs;
    int vexNum;
    int arcNum;
} Graph;

typedef struct Edge
{
    char vex;
    int weight;
} Edge;

Edge* initEdge(Graph* graph, int index)
{
    Edge* edge = (Edge*)malloc(sizeof(Edge) * graph->vexNum);

    for (int i = 0; i < graph->vexNum; i++)
    {
        edge[i].vex = graph->vexs[index];
        edge[i].weight = graph->arcs[index][i];
    }
    
    return edge;
}

int getMinEdge(Edge* edge, Graph* graph)
{
    int index = -1;
    int min = M;

    for (int i = 0; i < graph->vexNum; i++)
    {
        if (edge[i].weight != 0 && edge[i].weight < min)
        {
            min = edge[i].weight;

            index = i;
        }
    }
    
    return index;
}

void prim(Graph* graph, int index)
{
    int min;

    Edge* edge = initEdge(graph, index);

    for (int i = 0; i < graph->vexNum - 1; i++)
    {
        min = getMinEdge(edge, graph);

        printf("v%c -> v%c, weight = %d\n", edge[min].vex, graph->vexs[min], edge[min].weight);

        edge[min].weight = 0;

        for (int j = 0; j < graph->vexNum; j++)
        {
            // 更新权值，如果有更小的则覆盖
            if (graph->arcs[min][j] < edge[j].weight)
            {
                edge[j].weight = graph->arcs[min][j];
                edge[j].vex = graph->vexs[min];
            }
        }
    }

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
        if (graph->arcs[index][i] > 0 && graph->arcs[index][i] != M && visited[i] != 1)
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

    printf("\nPrim's MST:\n");
    prim(graph, 0);

    freeGraph(graph);

    return 0;
}