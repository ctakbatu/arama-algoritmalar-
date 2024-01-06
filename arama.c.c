
//A* ARAMASI

#include <stdio.h>
#include <math.h>

#define NODES 7
#define INF 9999

struct Cost {
    int g, h, f;
};

int graph[NODES][NODES] = {
    {INF, 2, 5, INF, INF, INF, INF},
    {2, INF, INF, 4, INF, INF, INF},
    {5, INF, INF, INF, 3, INF, INF},
    {INF, 4, INF, INF, INF, INF, 2},
    {INF, INF, 3, INF, INF, 1, INF},
    {INF, INF, INF, INF, 1, INF, 4},
    {INF, INF, INF, 2, INF, 4, INF}
};

struct Cost costs[NODES];

int calculateH(int node) {
    switch (node) {
        case 0: return 3; // karekok(10) yaklaşık 3
        case 1: return 2; // karekok(5) yaklaşık 2
        case 2: return 3; // karekok(10) yaklaşık 3
        case 3: return 2; // karekok(5) yaklaşık 2
        case 4: return 1; // karekok(2) yaklaşık 1
        case 5: return 1; // karekok(2) yaklaşık 1
        case 6: return 0; // hedef düğüm için h(6) = 0
        default: return INF; // geçersiz düğüm için sonsuz döndür
    }
}

void aStar(int startNode) {
    int i, j, minNode, minCost = INF;
    int visited[NODES];
    int parent[NODES];
    int path[NODES];
    int pathLength;

    for (i = 0; i < NODES; i++) {
        costs[i].g = INF;
        costs[i].h = INF;
        costs[i].f = INF;
    }

    costs[startNode].g = 0;
    costs[startNode].h = calculateH(startNode);
    costs[startNode].f = costs[startNode].g + costs[startNode].h;

    for (i = 0; i < NODES; i++) {
        visited[i] = 0;
    }

    for (i = 0; i < NODES; i++) {
        parent[i] = -1;
    }

    while (visited[6] == 0 && minCost != INF) {
        minCost = INF;
        for (i = 0; i < NODES; i++) {
            if (!visited[i] && costs[i].f < minCost) {
                minCost = costs[i].f;
                minNode = i;
            }
        }

        visited[minNode] = 1;

        for (j = 0; j < NODES; j++) {
            if (graph[minNode][j] != INF && !visited[j]) {
                if (costs[minNode].g + graph[minNode][j] < costs[j].g) {
                    costs[j].g = costs[minNode].g + graph[minNode][j];
                    costs[j].h = calculateH(j);
                    costs[j].f = costs[j].g + costs[j].h;
                    parent[j] = minNode;
                }
            }
        }
    }

    if (visited[6] == 1) {
        i = 6;
        pathLength = 0;
        while (i != -1) {
            path[pathLength] = i;
            pathLength++;
            i = parent[i];
        }

        printf("En kisa yol: ");
        for (i = pathLength - 1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
    } else {
        printf("Hedef dugume ulasilamadi.\n");
    }
}

int main() {
    aStar(0);

    return 0;
}

