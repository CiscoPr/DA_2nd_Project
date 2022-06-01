#include "graph2.h"

Graph2::Graph2(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

void Graph2::addEdge(int src, int dest, int capacity, int duration) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, capacity, duration});
    //nodes[dest].adj.push_back({-flux, src, capacity, duration});
    if (!hasDir) nodes[dest].adj.push_back({ src, capacity, duration});
}

void Graph2::addEdge_res(int src, int dest, int flux){
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest,flux});
}

pair<bool, int> Graph2::bfs(int s, int d, vector<int> &path){
    if(s==d) return {true,nodes[s].flow};

    // initialize all nodes as unvisited
    for(int i=1; i<=n; i++) nodes[i].visited = false ;
    queue<int> q; // queue of unvisited nodes
    q.push(s);

    nodes[s].visited = true ;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front (); q.pop (); // remove first element of q
        path.push_back(u);

        for(auto e : nodes[u].adj) {
            int w = e.dest;
            if(w == d){
                path.push_back(w);
                int mxFlow = INT32_MAX;
                for (auto x : path) {
                    mxFlow = min(mxFlow, nodes[x].flow);
                }
                return {true, mxFlow};
            }
            if (!nodes[w].visited) { // new node!
                q.push(w);
                nodes[w].visited = true ;
            }
        }
    }
    return {false, 0};
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
    int stops;
    int maxStops = maxFlow(start, end).second;

    cout << endl;
    int minFlow = bfs(start, end, path).second;
    cout << "The shortest path has: " << path.size() << " stops" <<  endl;
    for (auto x :  path) {
        cout << x << " ";
    }
    cout << endl;

    MaxHeap <int> pq;

    for (Node node : nodes) {
        node.pred = 0;
        node.flow = 0;
    }

    nodes[start].flow = INT32_MAX;

    pq.push(nodes[start].flow, start);

    while (!pq.empty()) {
        stops = 1;
        bool tester = false;

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
                if (stops >= maxStops) {
                    tester = true;
                    break;
                }
                if (nodes[w].flow < minFlow) {
                    tester = true;
                    break;
                }
            }
        }
        if (!tester || nodes[end].flow == INT32_MAX) continue;

        stack<int> nds;
        stops = 1;
        while (nodes[end].pred != 0) {
            nds.push(end);
            end = nodes[end].pred;
            stops++;
        }

        cout << endl << "Possible paths:";

        cout << endl << "Flow: "  << nodes[end].flow << endl;
        cout << "Stops: " << stops << endl;
        cout << "Path: " << start << " ";

        while (!nds.empty()) {
            cout << nds.top() << " ";
            nds.pop();
        }
        cout << endl;
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
