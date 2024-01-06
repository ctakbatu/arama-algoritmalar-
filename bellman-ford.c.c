//BELLMAN-FORD

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Bir kenari temsil eden struct
struct Edge {
    int src, dest, weight;
};

// Grafi temsil eden struct
struct Graph {
    int V, E;
    struct Edge* edges;
};

// Bellman-Ford algoritmasi
void bellmanFord(struct Graph* graph, int start) {
    int V = graph->V;
    int E = graph->E;
    int* distances = (int*)malloc(V * sizeof(int));

    // Baslangic noktasi disindaki tüm dügümlere sonsuz atama
    for (int i = 0; i < V; ++i)
        distances[i] = INT_MAX;

    distances[start] = 0; // Baslangic dügümüne mesafe 0

    // Tüm kenarlari gez
    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;

            // Dügüm v üzerinden dügüm u'ya giden kisa bir yol var mi kontrol et
            if (distances[u] != INT_MAX && distances[u] + weight < distances[v])
                distances[v] = distances[u] + weight;
        }
    }

    // Negatif döngü kontrolü
    for (int i = 0; i < E; ++i) {
        int u = graph->edges[i].src;
        int v = graph->edges[i].dest;
        int weight = graph->edges[i].weight;

        if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
            printf("Negatif Dongu Var, Bellman-Ford Algoritmasi Uygulanamaz!\n");
            free(distances);
            return;
        }
    }

    // Sonuclari yazdir
    printf("Baslangic Dugumu %c\n", start + 'A');
    for (int i = 0; i < V; ++i) {
        printf("Dugum %c, Ulasim Maliyeti: %d\n", i + 'A', distances[i]);
    }

    free(distances);
}

int main() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = 6; // Dügüm sayisi
    graph->E = 8; // Kenar sayisi
    graph->edges = (struct Edge*)malloc(graph->E * sizeof(struct Edge));

    // Graf kenarlarini tanimla
    graph->edges[0].src = 0; graph->edges[0].dest = 1; graph->edges[0].weight = 2;
    graph->edges[1].src = 0; graph->edges[1].dest = 2; graph->edges[1].weight = 1;
    graph->edges[2].src = 1; graph->edges[2].dest = 4; graph->edges[2].weight = -2;
    graph->edges[3].src = 2; graph->edges[3].dest = 5; graph->edges[3].weight = 5;
    graph->edges[4].src = 3; graph->edges[4].dest = 5; graph->edges[4].weight = 2;
    graph->edges[5].src = 4; graph->edges[5].dest = 3; graph->edges[5].weight = -1;
    graph->edges[6].src = 4; graph->edges[6].dest = 5; graph->edges[6].weight = 5;
    graph->edges[7].src = 5; graph->edges[7].dest = 3; graph->edges[7].weight = 7;

    // Bellman-Ford algoritmasini cagir
    bellmanFord(graph, 0);

    free(graph->edges);
    free(graph);

    return 0;
}
