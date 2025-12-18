#include "Solver.h"
#include "Input.h"
#include "Fuel.h"
#include "FloydWarshall.h"

vector<int> bestPath;
int bestCost;

static vector<int> currentPath;
static int currentCost;

void solveFromHub(int hubIndex) {
    currentPath.clear();
    currentCost = 0;

    set<int> remainingHubs;
    set<int> remainingHouses;

    for (int i = 0; i < n; i++) {
        if (i != hubIndex) remainingHubs.insert(hubs[i]);
        remainingHouses.insert(houses[i]);
    }

    int currentNode = hubs[hubIndex];
    int fuel = fuelCapacity;
    currentPath.push_back(currentNode);

    while (!remainingHouses.empty()) {
        int nextNode = -1;

        for (int x : remainingHubs) {
            if (canTravel(currentNode, x, fuel) &&
                (nextNode == -1 || dist[currentNode][x] < dist[currentNode][nextNode])) {
                nextNode = x;
            }
        }

        for (int x : remainingHouses) {
            if (!remainingHubs.count(houseToHub[x]) &&
                canTravel(currentNode, x, fuel) &&
                (nextNode == -1 || dist[currentNode][x] < dist[currentNode][nextNode])) {
                nextNode = x;
            }
        }

        if (nextNode == -1) {
            if (!canTravel(currentNode, nearestFuel[currentNode][0], fuel)) {
                currentCost = INF;
                return;
            }
            nextNode = nearestFuel[currentNode][0];
        }

        vector<int> stepPath;
        buildPath(nextNode, currentNode, stepPath);

        for (int x : stepPath) {
            currentPath.push_back(x);
            fuel -= graph[currentNode][x];
            currentCost += graph[currentNode][x];

            if (isFuel[x]) fuel = fuelCapacity;
            if (isHub[x]) remainingHubs.erase(x);
            if (isHouse[x] && !remainingHubs.count(houseToHub[x])) {
                remainingHouses.erase(x);
            }
            currentNode = x;
        }
    }

    if (currentCost < bestCost) {
        bestCost = currentCost;
        bestPath = currentPath;
    }
}
