#include "graph2.h"

// Constructor: nr nodes and direction (default: undirected)
Graph2::Graph2(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph2::addEdge(int src, int dest,int flux,  int capacity, int duration) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest,flux,  capacity, duration});
    //nodes[dest].adj.push_back({-flux, src, capacity, duration});
    if (!hasDir) nodes[dest].adj.push_back({ src, flux, capacity, duration});

}

bool Graph2::bfs(int s, int d){
    if(s==d) return true;
// initialize all nodes as unvisited
    for(int s=1; s<=n; s++) nodes[s]. visited = false ;
    queue<int> q; // queue of unvisited nodes
    q.push(s);
    //nodes[v].dist = 0;
    nodes[s]. visited = true ;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front (); q.pop (); // remove first element of q
        cout << u << " "; // show node order
        for(auto e : nodes[u].adj) {
            int w = e.dest;
            if(w == d){
                cout << w << " ";
                return true;
            }
            if (!nodes[w]. visited) { // new node!
                q.push(w);
                nodes[w]. visited = true ;
                //nodes[v].dist = nodes[u].dist + 1;
            }
        }
    }
    return false;
}


void Graph2::fordfulkerson(Graph2 g, int src, int dest ) {


}