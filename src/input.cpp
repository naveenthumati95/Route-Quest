#include "Input.h"

int n, t, m, k, fuelCapacity;
vector<vector<int>> graph;
vector<int> hubs, houses, fuelStations;
vector<int> isHub, isHouse, isFuel;
map<int, int> houseToHub;

void resetGlobals() {
    graph.assign(t + 1, vector<int>(t + 1, INF));

    hubs.assign(n, 0);
    houses.assign(n, 0);
    fuelStations.assign(k, 0);

    isHub.assign(t + 1, 0);
    isHouse.assign(t + 1, 0);
    isFuel.assign(t + 1, 0);

    houseToHub.clear();
}

void readInput() {
    cin >> n >> t >> m >> k >> fuelCapacity;
    resetGlobals();

    for (int i = 0; i < n; i++) {
        cin >> hubs[i];
        isHub[hubs[i]] = 1;
    }

    for (int i = 0; i < n; i++) {
        cin >> houses[i];
        isHouse[houses[i]] = 1;
        houseToHub[houses[i]] = hubs[i];
    }

    for (int i = 0; i < k; i++) {
        cin >> fuelStations[i];
        isFuel[fuelStations[i]] = 1;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = graph[v][u] = w;
    }

    for (int i = 0; i <= t; i++) {
        graph[i][i] = 0;
    }
}
