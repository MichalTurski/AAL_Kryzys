//
// Created by michal on 25.05.18.
//

#ifndef KRYZYS_GRAPH_H
#define KRYZYS_GRAPH_H

#include <utility>
#include <list>

typedef std::pair<int, int>timeCityPair;

class Graph {
    int no;
    std::list<std::pair<int, int>> *neigh;
public:
    Graph(int no);
    ~Graph();
    void addEdge(int city1, int city2, int time);
    void calculateDisconnect();
};


#endif //KRYZYS_GRAPH_H
