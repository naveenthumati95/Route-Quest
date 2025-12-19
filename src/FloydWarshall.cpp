#include "FloydWarshall.h"
#include "Input.h"

vector<vector<int>> dist;
vector<vector<int>> parent;

void computeAllPairsShortestPath() {
    dist.assign(t + 1, vector<int>(t + 1, INF));
    parent.assign(t + 1, vector<int>(t + 1, -1));

    for (int i = 0; i <= t; i++) {
        for (int j = 0; j <= t; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF) parent[i][j] = i;
        }
    }

    for (int k = 0; k <= t; k++) {
        for (int i = 0; i <= t; i++) {
            for (int j = 0; j <= t; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }
}

void buildPath(int start, int end, vector<int>& path) {
    path.clear();
    int cur = start;

    while (cur != end) {
        path.push_back(cur);
        cur = parent[end][cur];
    }

    reverse(all(path));
}
