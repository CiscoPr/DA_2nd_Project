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

void Graph2::addEdge_res(int src, int dest, int flux){
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest,flux});
    //nodes[dest].adj.push_back({-flux, src, capacity, duration});
    if (!hasDir) nodes[dest].adj.push_back({src, flux});
}

bool Graph2::bfs(int s, int d){
    if(s==d) return true;
    //vector<int> path; //path since source to destine
    // initialize all nodes as unvisited
    for(int s=1; s<=n; s++) nodes[s]. visited = false ;
    queue<int> q; // queue of unvisited nodes
    q.push(s);

    //nodes[v].dist = 0;
    nodes[s].visited = true ;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front (); q.pop (); // remove first element of q
        //path.push_back(u);
        cout << u << " "; // show node order
        for(auto e : nodes[u].adj) {
            int w = e.dest;
            if(w == d){
                //path.push_back(w);
                cout << w << " ";
                /*for(int i = 0; i < path.size(); i++)
                    std::cout << path[i]<< " ";
                */
                return true;
            }
            if (!nodes[w].visited) { // new node!
                q.push(w);
                nodes[w].visited = true ;
                //nodes[v].dist = nodes[u].dist + 1;
            }
        }
    }
    return false;
}

int Graph2::dfs(int v) {
    if (v < 1 || v > n)
        return 0;

    //cout << v << " "; // show node order
    nodes[v].visited = true;
    int count{1};
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            count += dfs(w);
    }

    return count;
}

int Graph2::dijkstra_distance(int a, int b) {
    MaxHeap<int, uint> pq{n, -1};

    for (int i{1}; i <= n; ++i) {
        pq.insert(i, -1);
        nodes[i].dist = INT32_MAX;
    }

    pq.decreaseKey(a, 0);
    nodes[a].dist = 0;

    while (pq.getSize() > 0) {
        auto p = pq.removeMinNode();
        auto &n = nodes[p.key];

        if (p.key == b)
            return p.value;

        for (Edge e : nodes[p.key].adj) {
            Node &o = nodes[e.dest];
            int newdist = e.capacity + n.dist;

            if (o.dist > newdist) {
                pq.decreaseKey(e.dest, newdist);
                o.dist = newdist;
                o.pred = p.key;
            }
        }
    }

    return -1;
}

list<int> Graph2::dijkstra_path(int a, int b) {
    list<int> path{};

    if (dijkstra_distance(a, b) >= 0) {
        int n = b;
        path.push_front(b);
        while (n != a)
            path.push_front(n = nodes[n].pred);
    }

    return path;
}

int Graph2::edmondskarp(Graph2 g, int src, int dest) {
    int max_group = 0;
    int flow = 0;
    int initial_node = 1;
    vector<int> path;
    Graph2 residual_graph(n, true);
    residual_graph = g;
    //create the residual graph
    for(int i = 1; i <= n; i++){
        for(auto e: nodes[i].adj){
            int w = e.dest;
            residual_graph.addEdge_res(w, i, flow);
        }
    }
}

