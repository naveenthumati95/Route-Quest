#include "Fuel.h"
#include "FloydWarshall.h"
#include "Input.h"

vector<vector<int>> nearestFuel;

static int simulatePath(int start, int end, int fuel) {
    vector<int> path;
    buildPath(end, start, path);

    vector<int> route = {start};
    route.insert(route.end(), all(path));

    for (int i = 1; i < route.size(); i++) {
        if (isFuel[route[i - 1]]) fuel = fuelCapacity;
        fuel -= graph[route[i - 1]][route[i]];
        if (fuel < 0) return -1;
    }

    if (isFuel[route.back()]) fuel = fuelCapacity;
    return fuel;
}

void computeNearestFuelStations() {
    nearestFuel.assign(t + 1, vector<int>(k));

    for (int i = 0; i <= t; i++) {
        vector<pair<int,int>> options;
        for (int j = 0; j <= t; j++) {
            if (isFuel[j]) options.push_back({dist[i][j], j});
        }
        sort(all(options));
        for (int j = 0; j < k; j++) {
            nearestFuel[i][j] = options[j].second;
        }
    }
}

int canTravel(int start, int end, int fuel) {
    int remaining = simulatePath(start, end, fuel);
    if (remaining < 0) return 0;

    remaining = simulatePath(end, nearestFuel[end][0], remaining);
    return remaining >= 0;
}
