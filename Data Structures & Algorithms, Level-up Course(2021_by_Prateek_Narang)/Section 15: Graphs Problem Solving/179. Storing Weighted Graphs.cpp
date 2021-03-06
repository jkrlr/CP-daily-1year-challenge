#include<iostream>
#include<list>
using namespace std;

class Graph{
    int V;
    list<pair<int, int>> *adjList;

public:

    Graph(int v){
        V = v;
        adjList = new list<pair<int, int>>[V];
    }

    void addEdge(int u, int v, int wt, bool undir = true){
        adjList[u].push_back({wt, v});

        if(undir){
            adjList[v].push_back({wt, v});
        }
    }
};

int main(){

    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(0, 3, 7);
    g.addEdge(3, 2, 2);
    g.addEdge(3, 4, 3);

    return 0;
}