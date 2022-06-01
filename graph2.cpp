#include "graph2.h"

// Constructor: nr nodes and direction (default: undirected)
Graph2::Graph2(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph2::addEdge(int src, int dest, int capacity, int duration) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, capacity, duration});
    //nodes[dest].adj.push_back({-flux, src, capacity, duration});
    if (!hasDir) nodes[dest].adj.push_back({ src, capacity, duration});

}

void Graph2::addEdge_res(int src, int dest, int flux){
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest,flux});
    //nodes[dest].adj.push_back({-flux, src, capacity, duration});
    //if (!hasDir) nodes[dest].adj.push_back({src, flux});
}

pair<bool, int> Graph2::bfs(int s, int d, vector<int> path){
    if(s==d) return {true,nodes[s].flow};
    // initialize all nodes as unvisited
    for(int i=1; i<=n; i++) nodes[i]. visited = false ;
    queue<int> q; // queue of unvisited nodes
    q.push(s);

    //nodes[v].dist = 0;
    nodes[s].visited = true ;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front (); q.pop (); // remove first element of q
        path.push_back(u);
        //cout << u << " "; // show node order
        for(auto e : nodes[u].adj) {
            int w = e.dest;
            if(w == d){
                path.push_back(w);
                //cout << w << " ";
                /*for(int i = 0; i < path.size(); i++)
                    std::cout << path[i]<< " ";
                */
                int mxFlow = INT_MAX;
                for (auto x : path) {
                    mxFlow = min(mxFlow, nodes[x].flow);
                }
                return {true, mxFlow};
            }
            if (!nodes[w].visited) { // new node!
                q.push(w);
                nodes[w].visited = true ;
                //nodes[v].dist = nodes[u].dist + 1;
            }
        }
    }
    return {false, 0};
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

pair<int, int> Graph2::maxFlow(int a, int b) {
    MaxHeap <int> pq;

    for (Node node : nodes) {
        node.pred = 0;
        node.flow = 0;
    }

    nodes[a].flow = INT32_MAX;

    pq.push(nodes[a].flow, a);

    while (!pq.empty()) {

        pair<int, int> mx = pq.top();
        pq.pop();
        int mx_flow = mx.first;
        int mx_index = mx.second;

        for (auto edge : nodes[mx_index].adj) {
            int w = edge.dest;
            if (min(nodes[mx_index].flow, edge.capacity) > nodes[w].flow) {

                nodes[w].flow = min(mx_flow, edge.capacity);
                nodes[w].pred = mx_index;
                pq.push(nodes[w].flow, w);
            }
        }
    }
    cout << "The maximum flow is: "  << nodes[b].flow << endl;
    stack<int> nds;
    int stops = 1;
    cout << a << " ";
    while (nodes[b].pred != 0) {
        nds.push(b);
        b = nodes[b].pred;
        stops++;
    }
    while (!nds.empty()) {
        cout << nds.top() << " ";
        nds.pop();
    }
    cout << endl;

    return {nodes[b].flow, stops};
}

void Graph2::scenario2(int start, int end) {
    vector<int> path;
    pair<int, int> mx = maxFlow(start, end);
    int minFlow = bfs(start, end, path).second;
    int stops = 1;

    MaxHeap <int> pq;

    for (Node node : nodes) {
        node.pred = 0;
        node.flow = 0;
    }

    nodes[start].flow = INT32_MAX;

    pq.push(nodes[start].flow, start);

    while (!pq.empty()) {

        pair<int, int> mx = pq.top();
        pq.pop();
        int mx_flow = mx.first;
        int mx_index = mx.second;

        for (auto edge : nodes[mx_index].adj) {
            int w = edge.dest;
            if (min(nodes[mx_index].flow, edge.capacity) > nodes[w].flow) {

                nodes[w].flow = min(mx_flow, edge.capacity);
                nodes[w].pred = mx_index;
                pq.push(nodes[w].flow, w);
                stops++;
            }
            if (stops > mx.second) continue;
            if (nodes[w].flow < minFlow) continue;
            cout << "viable path ";
        }

    }
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
    return 0;
}

/*Olá meu lindo, hoje estou muito simpatica
    e queria te agradecer por seres o meu sugar daddy
    e por me emprestares sempre tudo
    es muito boa pessoa, love u <3*/