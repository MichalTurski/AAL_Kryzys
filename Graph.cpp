//
// Created by michal on 25.05.18.
//

#include <queue>
#include <iostream>
#include <limits>
#include "Graph.h"

Graph::Graph(int no): no(no) {
    neigh = new std::list<timeCityPair>[no];
}
Graph::~Graph() {
    delete[] neigh;
}
void Graph::addEdge(int city1, int city2, int time) {
    neigh[city1].emplace_back(std::make_pair(time, city2));
    neigh[city2].emplace_back(std::make_pair(time, city1));
}
void Graph::calculateDisconnect() {
    std::priority_queue<timeCityPair, std::vector<timeCityPair>> queue;
    std::vector<int> times(no, 0);
    int currCity;
    int currNeigh;
    int currFiber;
    std::list<std::pair<int, int>>::iterator i;

    //Push capital to priority queue with infinite disconnect time (numeric infinite)
    queue.push(std::make_pair(std::numeric_limits<int>::max(), 0));
    times[0] = std::numeric_limits<int>::max();
    while (!queue.empty()) {
        currCity = queue.top().second;
        queue.pop();
        for (i = neigh[currCity].begin(); i != neigh[currCity].end(); ++i) {
            currFiber = i->first;
            currNeigh = i->second;
            if (times[currNeigh] < std::min(currFiber, times[currCity])) {
                times[currNeigh] = std::min(currFiber, times[currCity]);
                queue.push(std::make_pair(times[currNeigh], currNeigh));
            }
        }
    }
    std::cout << "Capital (city 0) will never lose connection.\n";
    for (int j = 1; j < times.size(); ++j) {
        std::cout << "City " << j << " will lose connection in " << times[j] << "months.\n";
    }
}