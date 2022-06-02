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

pair<bool, int> Graph2::bfs(int s, int d){
    if(s==d) return {true,INT32_MAX};

    // initialize all nodes as unvisited
    for(int i=1; i<=n; i++) {
        nodes[i].visited = false ;
        nodes[i].pred = 0;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(s);

    nodes[s].visited = true ;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front(); q.pop(); // remove first element of q

        for(auto e : nodes[u].adj) {
            if (nodes[e.dest].visited) continue;
            int w = e.dest;

            nodes[w].pred = u;
            q.push(w);
            nodes[w].visited = true;
            if(w == d){
                    return {true, nodes[w].flow};
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
    list<int> path;
    int maxStops = maxFlow(start, end).second;

    cout << endl;
    int minFlow = bfs(start, end).second;
    int c = end;
    path.push_front(c);
    while (nodes[c].pred != 0) {
        path.push_front(nodes[c].pred);
        c = nodes[c].pred;
    }
    cout << "The shortest path has: " << path.size() << " stops" <<  endl;
    for (auto x :  path) {
        cout << x << " ";
    }
    cout << endl;

    vector<stack<int>> paths;
    for (Node node : nodes) {
        node.pred = 0;
        node.flow = 0;
        node.visited = false;
    }

    vector<stack<int>> help;
    stack<int> aux;
    printAllPaths(start, end, help, aux);

    cout << endl << "Possible paths: " << endl;

    for (stack<int> a : help) {
        bool tester = false;

        if(a.size() >= maxStops) {
            continue;
        }
        int stops = 0;
        stack<int> auxi = stack<int>();
        while (!a.empty()) {
            int t = a.top();
            if (nodes[t].flow <= minFlow) {
                tester = true;
                break;
            }
            a.pop();
            auxi.push(t);
            stops++;
        }
        if (tester) break;

        cout << endl << "Flow: "  << nodes[auxi.top()].flow << endl;
        cout << "Stops: " << stops << endl;
        cout << "Path: ";

        while (!auxi.empty()) {
            cout << auxi.top() << " ";
            auxi.pop();
        }
    }
}

void Graph2::printAllPaths(int s, int d, vector<stack<int>> &help, stack<int> &aux) {

        nodes[s].visited = true;
        aux.push(s);

        if (s == d) {
            help.push_back(aux);
            while (!aux.empty()) aux.pop();
        }
        else // If current vertex is not destination
        {
            // Recur for all the vertices adjacent to current vertex
            auto it = nodes[s].adj.begin();
            for (auto edge : nodes[s].adj) {
                if (!nodes[edge.dest].visited) printAllPaths(edge.dest, d, help, aux);
            }

        }

        // Remove current vertex from path[] and mark it as unvisited
        nodes[s].visited = false;
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
