// Name: Shashank Kumar
// Roll Number: 25/DA/056

#include <stdio.h>
#include <stdlib.h>

#define INF 999999
#define MAX 100

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    int parent[MAX];
    int rank[MAX];
} DisjointSet;

int n, e;
int graph[MAX][MAX];
Edge edges[MAX * MAX];

void initSet(DisjointSet *ds, int vertices) {
    for (int i = 0; i < vertices; i++) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
}

int findSet(DisjointSet *ds, int i) {
    if (ds->parent[i] == i)
        return i;
    return ds->parent[i] = findSet(ds, ds->parent[i]);
}

void unionSet(DisjointSet *ds, int u, int v) {
    int rootU = findSet(ds, u);
    int rootV = findSet(ds, v);
    if (rootU != rootV) {
        if (ds->rank[rootU] < ds->rank[rootV]) {
            ds->parent[rootU] = rootV;
        } else if (ds->rank[rootU] > ds->rank[rootV]) {
            ds->parent[rootV] = rootU;
        } else {
            ds->parent[rootV] = rootU;
            ds->rank[rootU]++;
        }
    }
}

int compareEdges(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void primMST() {
    int selected[MAX] = {0};
    int parent[MAX];
    int key[MAX];

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        selected[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int min = INF, u = -1;

        for (int v = 0; v < n; v++) {
            if (!selected[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        if (u == -1) break;
        selected[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !selected[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("\n--- Prim's Algorithm MST ---\n");
    printf("Edge \tWeight\n");
    int totalCost = 0;
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
            printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
            totalCost += graph[i][parent[i]];
        }
    }
    printf("Total Cost of MST: %d\n", totalCost);
}

void kruskalMST() {
    DisjointSet ds;
    initSet(&ds, n);

    Edge sortedEdges[MAX * MAX];
    for (int i = 0; i < e; i++) {
        sortedEdges[i] = edges[i];
    }

    qsort(sortedEdges, e, sizeof(Edge), compareEdges);

    printf("\n--- Kruskal's Algorithm MST ---\n");
    printf("Edge \tWeight\n");
    int totalCost = 0;
    int edgesInMST = 0;

    for (int i = 0; i < e && edgesInMST < n - 1; i++) {
        int u = sortedEdges[i].u;
        int v = sortedEdges[i].v;
        int weight = sortedEdges[i].weight;

        if (findSet(&ds, u) != findSet(&ds, v)) {
            unionSet(&ds, u, v);
            printf("%d - %d \t%d\n", u, v, weight);
            totalCost += weight;
            edgesInMST++;
        }
    }
    printf("Total Cost of MST: %d\n", totalCost);
}

int main() {
    int choice;

    printf("Enter number of vertices (0 to %d): ", MAX - 1);
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    printf("\nEnter edges in format (u v weight) where u and v are vertex indices (0-indexed):\n");
    for (int i = 0; i < e; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
        
        graph[edges[i].u][edges[i].v] = edges[i].weight;
        graph[edges[i].v][edges[i].u] = edges[i].weight;
    }

    do {
        printf("\nMenu:\n");
        printf("1. Prim's Algorithm\n");
        printf("2. Kruskal's Algorithm\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                primMST();
                break;
            case 2:
                kruskalMST();
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 3);

    return 0;
}
