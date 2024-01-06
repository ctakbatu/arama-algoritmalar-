//KRUSKAL

#include <stdio.h>
#include <stdlib.h>

// Grafı temsil etmek için bir yapı tanımla
struct Edge {
    int src, dest, weight;
};

// Ağırlık sırasına göre kenarları sıralayan yardımcı bir fonksiyon
int compare(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Union-Find veri yapısı için yardımcı fonksiyonlar
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void Union(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

// Kruskal algoritması uygulayan fonksiyon
void Kruskal(struct Edge edges[], int V, int E) {
    // Grafı sırala
    qsort(edges, E, sizeof(edges[0]), compare);

    // Union-Find veri yapısı için parent dizisi oluştur
    int* parent = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++)
        parent[i] = -1;

    printf("Minimum Spanning Tree:\n");
    for (int i = 0; i < E; i++) {
        int x = find(parent, edges[i].src);
        int y = find(parent, edges[i].dest);

        if (x != y) {
            printf("%d - %d \t%d\n", edges[i].src, edges[i].dest, edges[i].weight);
            Union(parent, x, y);
        }
    }

    free(parent);
}

int main() {
    int V = 4; // Düğüm sayısı
    int E = 6; // Kenar sayısı

    struct Edge edges[] = {
        {1, 2, 5},
        {2, 3, 15},
        {2, 4, 30},
        {1, 3, 20},
        {3, 4, 10},
        {1, 4, 25}
    };

    Kruskal(edges, V, E);

    return 0;
}

