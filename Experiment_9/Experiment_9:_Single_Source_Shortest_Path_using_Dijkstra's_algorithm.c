#include <stdio.h>
#include <limits.h>

#define MAX 100

void dijkstra(int n, int cost[MAX][MAX], int src) {
    int dist[MAX], visited[MAX], i, count, u, min;

    for (i = 0; i < n; i++) {
        dist[i] = cost[src][i];
        if (cost[src][i] == 0 && src != i)
            dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[src] = 0;
    visited[src] = 1;

    for (count = 0; count < n - 1; count++) {
        min = INT_MAX;
        for (i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        for (i = 0; i < n; i++) {
            if (!visited[i] && cost[u][i] && dist[u] != INT_MAX && dist[u] + cost[u][i] < dist[i]) {
                dist[i] = dist[u] + cost[u][i];
            }
        }
    }

    printf("\nVertex\tDistance from Source\n");
    for (i = 0; i < n; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

int main() {
    int n, i, j, cost[MAX][MAX], src;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (use 0 for no edge):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    printf("Enter the source vertex: ");
    scanf("%d", &src);

    dijkstra(n, cost, src);

    return 0;
}
