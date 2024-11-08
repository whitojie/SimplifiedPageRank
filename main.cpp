#include <iostream>
#include <string>
#include "pagerank.h"
using namespace std;


int main() {
    int n, p;
    cin >> n >> p;
    PageRank pagerank(p);

    for (int i = 0; i < n; i++) {
        string from, to;
        cin >> from >> to;
        pagerank.addEdge(from, to);
    }

    pagerank.initialize();
    pagerank.computePageRanks();
    pagerank.display();

    return 0;
}

