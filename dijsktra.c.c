
//dijsktra algoritması


#include <stdio.h>
#include <limits.h>
#include <stdbool.h> // bool veri tipini tanimlamak için

#define V 6 // dügüm sayisi

// en yakin dügümü bulan fonksiyon
int min_distance(int dist[], bool visited[]) {
  int min = INT_MAX, min_index;
  for (int v = 0; v < V; v++) {
    if (!visited[v] && dist[v] <= min) {
      min = dist[v];
      min_index = v;
    }
  }
  return min_index;
}

// en kisa yollari ekrana yazdiran fonksiyon
void print_solution(int dist[]) {
  printf("Dugum\tMesafe\n");
  for (int i = 0; i < V; i++)
    printf("%d\t%d\n", i, dist[i]);
}

// Dijkstra algoritmasini uygulayan fonksiyon
void dijkstra(int graph[V][V], int src) {
  int dist[V]; // baslangıc dügümünden diger dügümlere olan uzaklıkları tutan dizi
  bool visited[V]; // bir dügümün ziyaret edilip edilmedigini tutan dizi

  // baslangicta tüm dügümlerin uzaklıgı sonsuz ve ziyaret edilmemis kabul edilir
  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX;
    visited[i] = false;
  }

  // baslangiç dügümünün uzaklıgı 0 kabul edilir
  dist[src] = 0;

  // tüm dügümleri ziyaret edene kadar
  for (int count = 0; count < V - 1; count++) {
    // en yakin dügümü bul
    int u = min_distance(dist, visited);

    // bu dügümü ziyaret edildi olarak ibaretle
    visited[u] = true;

    // bu düðümden gidilebilen diger dügülerin uzakliklarini güncelle
    for (int v = 0; v < V; v++) {
      // eðer v düðümü ziyaret edilmemisse, u ile v arasinda bir kenar varsa ve
      // u düðümünden v düðümüne giden yol, mevcut yoldan daha kısaysa
      if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
        // v düðümünün uzakligini güncelle
        dist[v] = dist[u] + graph[u][v];
      }
    }
  }

  // en kisa yollari yazdir
  print_solution(dist);
}

int main() {

  /* Örnek Graf */
  /* A B C D E F */
  /* 0 1 2 3 4 5 */

  int graph[V][V] = {
      {0, 2, 1, 0, 0, 0},
      {2, 0, 0, 5, 3, 0},
      {1, 0, 0, 0, 0, 0},
      {0, 5, 0, 0, 1, 5},
      {0, 3, 0, 1, 0, 0},
      {0, 0, 0, 5, 0, 0}};

  dijkstra(graph, 0); // dijkstra fonksiyonunu çagir

  return 0;
}
