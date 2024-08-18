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

            if (graph->arcs[i][j] != 0 && graph->arcs[i][j] != M)
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
        if (visited[i] != 1 && graph->arcs[index][i] != 0 && graph->arcs[index][i] != M)
        {
            DFS(graph, visited, i);
        }
    }
}

int getMin(Graph* graph, int* d, int* s)
{
    int min = M;

    int index = -1;

    for (int i = 0; i < graph->vexNum; i++)
    {
        if (!s[i] && d[i] < min)
        {
            min = d[i];
            index = i;
        }
    }
    
    return index;
}

void dijkstra(Graph* graph, int index)
{
    int* s = (int*)malloc(sizeof(int) * graph->vexNum);
    int* p = (int*)malloc(sizeof(int) * graph->vexNum);
    int* d = (int*)malloc(sizeof(int) * graph->vexNum);

    for (int i = 0; i < graph->vexNum; i++)
    {
        if (graph->arcs[index][i] != 0 && graph->arcs[index][i] != M)
        {
            d[i] = graph->arcs[index][i];
            p[i] = index;
        }
        else
        {
            d[i] = M;
            p[i] = -1;
        }

        s[i] = 0;
    }

    s[index] = 1;
    d[index] = 0;
    
    for (int i = 0; i < graph->vexNum - 1; i++)
    {
        int min = getMin(graph, d, s);

        s[min] = 1;

        for (int j = 0; j < graph->vexNum; j++)
        {
            if (!s[j] && d[j] > d[min] + graph->arcs[min][j])
            {
                d[j] = d[min] + graph->arcs[min][j];

                p[j] = min;
            }
        }
    }

    // 打印 s, p, d 数组
    printf("s array: ");
    for (int i = 0; i < graph->vexNum; i++)
    {
        printf("%d ", s[i]);
    }
    printf("\n");

    printf("p array: ");
    for (int i = 0; i < graph->vexNum; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n");

    printf("d array: ");
    for (int i = 0; i < graph->vexNum; i++)
    {
        printf("%d ", d[i]);
    }
    printf("\n");
    
    // 输出最短路径结果
    printf("\nShortest paths from vertex %c:\n", graph->vexs[index]);
    for (int i = 0; i < graph->vexNum; i++)
    {
        if (i != index)
        {
            printf("To vertex %c: Distance = %d, Path = %c", graph->vexs[i], d[i], graph->vexs[i]);
            int j = i;
            while (p[j] != index)
            {
                printf(" <- %c", graph->vexs[p[j]]);
                j = p[j];
            }
            printf(" <- %c\n", graph->vexs[index]);
        }
    }

    free(s);
    free(p);
    free(d);
}

int main(int argc, char* argv[])
{
    const int vexNum = 7;
    char vexs[] = {'1', '2', '3', '4', '5', '6', '7'};
    int arcs[] = {
        0, 12, M, M, M, 16, 14,
        12, 0, 10, M, M, 7, M,
        M, 10, 0, 3, 5, 6, M,
        M, M, 3, 0, 4, M, M,
        M, M, 5, 4, 0, 2, 8,
        16, 7, 6, M, 2, 0, 9,
        14, M, M, M, 8, 9, 0
    };

    Graph* graph = initGraph(vexNum);
    createGraph(graph, vexs, arcs);

    int visited[7] = {0};

    printf("DFS: ");
    DFS(graph, visited, 0);
    printf("\n");

    printf("\nDijkstra's Shortest Paths:\n");
    dijkstra(graph, 0);

    freeGraph(graph);

    return 0;
}