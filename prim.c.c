//prim algoritmalarý



#include <stdio.h>
#include <limits.h>

//define V 5

int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void printMST(int parent[], int graph[V][V]) {
    printf("Kenar \tAgirligi\n");
    for (int i = 1; i < V; i++)
        printf("%c - %c \t%d \n", parent[i] + 'A', i + 'A', graph[i][parent[i]]);
}

void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    int mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);

        mstSet[u] = 1;

        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    printMST(parent, graph);
}

int main() {
    int graph[V][V] = {
        {0, 5, 0, 10, 0},
        {5, 0, 3, 0, 0},
        {0, 3, 0, 1, 2},
        {10, 0, 1, 0, 6},
        {0, 0, 2, 6, 0}
    };

    primMST(graph);

    return 0;
}
