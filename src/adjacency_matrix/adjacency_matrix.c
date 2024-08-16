#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5
#define TRUE 1
#define FALSE 0

typedef struct Queue
{
    int front;
    int rear;
    int data[MAXSIZE];
} Queue;

Queue* initQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    
    queue->front = queue->rear = 0;

    return queue;
}

int isFull(Queue* queue)
{
    return (queue->rear + 1) % MAXSIZE == queue->front ? TRUE : FALSE;
}

int isEmpty(Queue* queue)
{
    return queue->rear == queue->front ? TRUE : FALSE;
}

int enQueue(Queue* queue, int data)
{
    if (isFull(queue))
    {
        return FALSE;
    }
    else
    {
        queue->data[queue->rear] = data;
        
        queue->rear = (queue->rear + 1) % MAXSIZE;

        return TRUE;
    }
}

int deQueue(Queue* queue)
{
    if (isEmpty(queue))
    {
        return FALSE;
    }
    else
    {
        int data = queue->data[queue->front];

        queue->front = (queue->front + 1) % MAXSIZE;

        return data;
    }
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

            if (graph->arcs[i][j] == 1)
            {
                graph->arcNum ++;
            }
        }
    }
    
    graph->arcNum /= 2;
}

// 深度优先
void DFS(Graph* graph, int* visited, int index)
{
    printf("%c ", graph->vexs[index]);
    
    visited[index] = 1;

    for (int i = 0; i < graph->vexNum; i++)
    {
        if (graph->arcs[index][i] == 1 && visited[i] != 1)
        {
            DFS(graph, visited, i);
        }
        // 返回到上一个节点
    }
}

// 广度优先
void BFS(Graph* graph, int* visited, int index)
{
    printf("%c ", graph->vexs[index]);

    visited[index] = 1;

    Queue* queue = initQueue();
    enQueue(queue, index);

    while (!isEmpty(queue))
    {
        int i = deQueue(queue);
        for (int j = 0; j < graph->vexNum; j++)
        {
            if (graph->arcs[i][j] == 1 && visited[j] != 1)
            {
                printf("%c ", graph->vexs[j]);

                visited[j] = 1;

                enQueue(queue, j);
            }
        }
    }

    free(queue);  // 释放队列内存
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
    int vexNum = 5;
    char vexs[] = {'A', 'B', 'C', 'D', 'E'};
    int arcs[] = {
        0, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        0, 1, 1, 0, 1,
        0, 0, 0, 1, 0
    };

    Graph* graph = initGraph(vexNum);
    createGraph(graph, vexs, arcs);

    int visited[MAXSIZE] = {0};

    printf("DFS: ");
    DFS(graph, visited, 0);
    printf("\n");

    for (int i = 0; i < MAXSIZE; i++)
    {
        visited[i] = 0;
    }

    printf("BFS: ");
    BFS(graph, visited, 0);
    printf("\n");

    freeGraph(graph);

    return 0;
}