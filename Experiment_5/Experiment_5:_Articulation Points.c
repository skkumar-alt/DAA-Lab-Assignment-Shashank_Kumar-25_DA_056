// Name: Shashank Kumar
// Roll Number: 25/DA/056

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int timeCount = 0;

void addEdge(int graph[MAX][MAX], int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

void DFS(int u, int n, int graph[MAX][MAX], int visited[], int disc[],
         int low[], int parent[], int ap[]) {
    int children = 0;
    visited[u] = 1;
    disc[u] = low[u] = ++timeCount;

    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                DFS(v, n, graph, visited, disc, low, parent, ap);

                if (low[v] < low[u])
                    low[u] = low[v];

                if (parent[u] == -1 && children > 1)
                    ap[u] = 1;

                if (parent[u] != -1 && low[v] >= disc[u])
                    ap[u] = 1;
            }
            else if (v != parent[u]) {
                if (disc[v] < low[u])
                    low[u] = disc[v];
            }
        }
    }
}

int main() {
    int n, e;
    int graph[MAX][MAX] = {0};

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &e);

    printf("Enter edges:\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    int visited[MAX] = {0};
    int disc[MAX], low[MAX], parent[MAX], ap[MAX] = {0};

    for (int i = 0; i < n; i++)
        parent[i] = -1;

    for (int i = 0; i < n; i++)
        if (!visited[i])
            DFS(i, n, graph, visited, disc, low, parent, ap);

    printf("Articulation Points:\n");
    for (int i = 0; i < n; i++)
        if (ap[i])
            printf("%d ", i);

    return 0;
}
