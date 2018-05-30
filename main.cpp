#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <assert.h>
#include <ctime>
#include <getopt.h>
#include <fstream>
#include <chrono>
#include "fiber.h"
#include "Graph.h"

void usage(char* name) {
    std::cout << "Usage:\n";
    std::cout<< name <<" -r problem_size [-t]\n";
    std::cout<< name <<" -i < file [-t]\n";
    std::cout<< "anotherProgram | " << name << " -i [-t]" << std::endl;
    std::cout<< "\toptions:\n";
    std::cout<< "\t-t - measure execution time.\n";
    std::cout<< "\t-i - expect input from stdin. First number from stdin is problem size.\n";
    std::cout<< "\t\tNext tree numbers are edges where first number is first city, second number is second city, third is disconnection time.\n";
    std::cout<< "\t-r - generate random problem. Size of problem is next argument.\n";
    exit (-1);
}

void graphFromRandom(Graph **graph, unsigned int num) {
    std::srand((unsigned int)std::time(nullptr));

    std::vector<int> inSlots;
    std::vector<int> outSlots;

    *graph = new Graph(num);
    inSlots.resize(num);
    outSlots.resize(2 * num);
    for (int i = 0; i < num; ++i) {
        inSlots[i] = i;
        outSlots[2 * i] = i;
        outSlots[2 * i + 1] = i;
    }
    std::random_shuffle(inSlots.begin(), inSlots.end());
    std::random_shuffle(outSlots.begin(), outSlots.end());

    for (int i = 0; i < num; i++) {
        (*graph)->addEdge(inSlots.back(),outSlots.back(), i+1);
        inSlots.pop_back();
        outSlots.pop_back();
    }
}
bool graphFromStdin(Graph **graph) {
    int size;
    int city1, city2, time;

    if (std::cin >> size) {
        *graph = new Graph(size);
        while (std::cin >> city1) {
            if (std::cin >> city2 && std::cin >> time)
                (*graph)->addEdge(city1, city2, time);
            else {
                std::cout << "Wrong input from stdin.\n";
                exit(-1);
            }
        }
    } else {
        return false;
    }
}

int main(int argc, char **argv) {
    Graph *graph = nullptr;
    int cityNum = 0;
    int opt;
    bool random = false;
    bool input = false;
    bool timeMeasure = false;
    std::chrono::high_resolution_clock::time_point t1, t2;

    while ((opt = getopt(argc, argv, "r:it")) != -1) {
        switch (opt) {
            case 'r':
                random = true;
                cityNum = atoi(optarg);
                break;
            case 'i':
                input = true;
                break;
            case 't':
                timeMeasure = true;
                break;
            default:
                usage(argv[0]);
        }
    }

    if (random) {
        graphFromRandom(&graph, cityNum);
    } else if (input) {
        graphFromStdin(&graph);
    } else {
        usage(argv[0]);
    }
    if (timeMeasure)
         t1 = std::chrono::high_resolution_clock::now();
    graph->calculateDisconnect();
    if (timeMeasure) {
        t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = t2 - t1;
        std::cout << "Execution time of Dijkstra algorithm is " <<
                  std::fixed << elapsed.count() << std::endl;
    }
    delete(graph);
    return 0;
}