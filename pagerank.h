#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

/* Simplified PageRank
 * Goals:
 * 1. Input data that lists websites and their links
 * 2. Build adjacency list to store info
 * 3. Calculate ranks for each webpage
 */


class PageRank {
private:

public:
    PageRank();

    map<string, float> pageRank;
    map<string, int> outDegree; // out degree, from -> to
    map<string, vector<string>> inDegree; // in degree, to -> from
    int p;

    explicit PageRank(int powerIterations) : p(powerIterations) {};
    void addEdge(const string& from, const string& to);
    void initialize();
    void computePageRanks();
    void display();
    void parseInput(const string& input);
    string getStringRepresentation();
};


void PageRank::initialize() {
    int numWebsites = outDegree.size();
    float initialRank = 1.0f / numWebsites;

    // Initialize the rank of each website
    for (const auto& pair : outDegree) {
        pageRank[pair.first] = initialRank;
    }
}

void PageRank::addEdge(const string &from, const string &to) {
    outDegree[from]++;
    inDegree[to].push_back(from);
    // if from isn't in graph, add from key with empty value into graph
    if(outDegree.find(to) == outDegree.end()){
        outDegree[to] = 0;
    }
}

void PageRank::computePageRanks() {
    map<string, float> newRanks;
    for (int i = 1; i < p; i++) {
        newRanks = pageRank;

        for(auto &website : pageRank){
            float sum = 0.0;
            const string& to = website.first;

            for(auto& link : inDegree[to]){
                sum += (1.0f / (float)outDegree.find(link)->second) * pageRank[link];
            }
            newRanks[website.first] = sum;
        }
        pageRank = newRanks;
    }
}

void PageRank::display() {
    map<string, float>::iterator it;

    for(it = pageRank.begin(); it != pageRank.end(); it++){
        cout << setprecision(2) << fixed << it->first << " " << it->second << endl;
    }
}


string PageRank::getStringRepresentation() {
    ostringstream oss;
    for (const auto& pair : pageRank) {
        oss << setprecision(2) << fixed << pair.first << " " << pair.second << endl;
    }
    return oss.str();
}

void PageRank::parseInput(const string& input) {
    istringstream iss(input);
    int numEdges;
    iss >> numEdges >> p;

    string from, to;
    for (int i = 0; i < numEdges; ++i) {
        iss >> from >> to;
        addEdge(from, to);
    }
}

PageRank::PageRank() {

}
