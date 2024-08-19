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

            if (graph->arcs[i][j] != M && graph->arcs[i][j] > 0)
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
        if (visited[i] != 1 && graph->arcs[index][i] != M && graph->arcs[index][i] > 0)
        {
            DFS(graph, visited, i);
        }
    }
}

void printPath(int i, int j, int** p, Graph* graph)
{
    if (p[i][j] == i) 
    {
        printf("%c -> %c", graph->vexs[i], graph->vexs[j]);
    }
    else
    {
        printPath(i, p[i][j], p, graph);
        printf(" -> %c", graph->vexs[j]);
    }
}

void floyd(Graph* graph)
{
    int** d = (int**)malloc(sizeof(int*) * graph->vexNum);
    for (int i = 0; i < graph->vexNum; i++)
    {
        d[i] = (int*)malloc(sizeof(int) * graph->vexNum);
    }
    
    int** p = (int**)malloc(sizeof(int*) * graph->vexNum);
    for (int i = 0; i < graph->vexNum; i++)
    {
        p[i] = (int*)malloc(sizeof(int) * graph->vexNum);
    }

    for (int i = 0; i < graph->vexNum; i++)
    {
        for (int j = 0; j < graph->vexNum; j++)
        {
            d[i][j] = graph->arcs[i][j];
            if (graph->arcs[i][j] != M && graph->arcs[i][j] > 0)
            {   
                p[i][j] = i;
            }
            else
            {
                p[i][j] = -1;
            }
            
        }
    }
    
    for (int i = 0; i < graph->vexNum; i++)
    {
        for (int j = 0; j < graph->vexNum; j++)
        {
            for (int k = 0; k < graph->vexNum; k++)
            {
                if (d[j][k] > d[j][i] + d[i][k])
                {
                    d[j][k] = d[j][i] + d[i][k];

                    p[j][k] = p[i][k];
                }
            }
        }
    }
    
    // 打印最短路径矩阵和路径矩阵
    printf("Shortest path matrix (d):\n");
    for (int i = 0; i < graph->vexNum; i++)
    {
        for (int j = 0; j < graph->vexNum; j++)
        {
            if (d[i][j] == M)
            {
                printf(" M ");
            }
            else
            {
                printf("%2d ", d[i][j]);
            }
        }
        printf("\n");
    }

    printf("Path matrix (p):\n");
    for (int i = 0; i < graph->vexNum; i++)
    {
        for (int j = 0; j < graph->vexNum; j++)
        {
            printf("%2d ", p[i][j]);
        }
        printf("\n");
    }

    // 输出最短路径结果
    printf("Shortest paths:\n");
    for (int i = 0; i < graph->vexNum; i++)
    {
        for (int j = 0; j < graph->vexNum; j++)
        {
            if (i != j && d[i][j] != M)
            {
                printf("From %c to %c: Distance = %d, Path = ", graph->vexs[i], graph->vexs[j], d[i][j]);
                printPath(i, j, p, graph);
                printf("\n");
            }
        }
    }

    for (int i = 0; i < graph->vexNum; i++)
    {
        free(p[i]);
    }
    free(p);

    for (int i = 0; i < graph->vexNum; i++)
    {
        free(d[i]);
    }
    free(d);
}

int main(int argc, char* argv[])
{
    const int vexNum = 4;
    char vexs[] = {'1', '2', '3', '4'};
    int arcs[] = {
        0, 1, M, 3,
        1, 0, 2, 2,
        M, 2, 0, 8,
        3, 2, 8, 0
    };

    Graph* graph = initGraph(vexNum);
    createGraph(graph, vexs, arcs);

    int visited[4] = {0};

    printf("DFS: ");
    DFS(graph, visited, 0);
    printf("\n");

    printf("\nFloyd-Warshall Algorithm:\n");
    floyd(graph);

    freeGraph(graph);

    return 0;
}