#include "graph2.h"

Graph2::Graph2(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

void Graph2::addEdge(int src, int dest, int capacity, int duration) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, capacity, duration});
    //nodes[dest].adj.push_back({-flux, src, capacity, duration});
    if (!hasDir) nodes[dest].adj.push_back({ src, capacity, duration});
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
    while (nodes[b].pred != 0) {
        nds.push(b);
        b = nodes[b].pred;
        stops++;
    }
    cout << a << " ";
    while (!nds.empty()) {
        cout << nds.top() << " ";
        nds.pop();
    }

    return {nodes[b].flow, stops};
}

void Graph2::scenario2(int start, int end) {
    list<int> path;
    maxStops = maxFlow(start, end).second;

    cout << endl;
    minFlow = bfs(start, end).second;
    int c = end;
    path.push_front(c);
    while (nodes[c].pred != 0) {
        path.push_front(nodes[c].pred);
        c = nodes[c].pred;
    }
    cout << "The shortest path has: " << path.size() << " stops" <<  endl;
    for (auto node : path) cout << node << " ";
    cout << endl;

    cout << endl << "The minimum flow worth considering is: " << minFlow << endl
         << "\nThe maximum number of stops worth considering is: " << maxStops << endl;

    for (int i = 1; i <= n; i++) {
        nodes[i].pred = 0;
        nodes[i].visited = false;
        nodes[i].flow = 0;
    }
    nodes[start].flow = INT32_MAX;

    /*vector<queue<int>> help;
    queue<int> aux;
    printAllPaths(start, end, help, aux);

    cout << endl << "Possible paths: " << endl;

    for (queue<int> a : help) {

        cout << endl << "Flow: "  << nodes[end].flow << endl;
        cout << "Stops: " << a.size() << endl;
        cout << "Path: ";

        while (!a.empty()) {
            cout << a.front() << " ";
            a.pop();
        }
        cout << endl;
    }*/
}

void Graph2::printAllPaths(int s, int d, vector<queue<int>> &help, queue<int> aux) {

    if(aux.size() >= maxStops) return;
    if (nodes[s].flow < minFlow) return;

    nodes[s].visited = true;
    aux.push(s);

    if (s == d) {
        help.push_back(aux);
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        for (auto edge : nodes[s].adj) {
            if (!nodes[edge.dest].visited) {
                if (min(nodes[s].flow, edge.capacity) > nodes[edge.dest].flow) {

                    nodes[edge.dest].flow = min(nodes[s].flow, edge.capacity);
                    nodes[edge.dest].pred = s;
                }
                printAllPaths(edge.dest, d, help, aux);
            }
        }

    }

    // Remove current vertex from path[] and mark it as unvisited
    nodes[s].visited = false;
}


vector<vector<pair<int, int>>> Graph2::createResidualGraph(Graph2 g) {
    vector<vector<pair<int, int>>> residual_graph;
    vector<pair<int, int>> edges;
    for(int i = 0; i <= n; i++){
        residual_graph.push_back(edges);
    }
    int i=0;
    while(i <= n){
        for(int it = 0; it <= n; it++){
            residual_graph[i].push_back({0,0});
        }
        i++;
    }

    int j = 1;
    while(j <= n){
        for(auto e: nodes[j].adj){
            int w = e.dest;
            int c = e.capacity;
            int d = e.duration;
            residual_graph[j][w] = {c, d};
        }
        j++;
    }
    return residual_graph;
}


bool Graph2::bfs_for_scenario2(int src, int dest, vector<vector<pair<int, int>>> resid){
    // initialize all nodes as unvisited
    for(int v=1; v<=n; v++){
        nodes[v].visited = false;
        nodes[v].pred = NULL;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(src);
    nodes[src].visited = true ;
    while(!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front (); q.pop (); // remove first element of q
        //cout << u << " "; // show node order
        for (auto e : nodes[u]. adj) {
            int w = e.dest;
            if ((!nodes[w]. visited) && (resid[u][w].first > 0)) { // new node!
                if(w == dest){
                    //cout << w << " ";
                    nodes[w]. visited = true ;
                    nodes[w].pred = u;
                    return true;

                }
                q.push(w);
                nodes[w]. visited = true ;
                nodes[w].pred = u;
            }
        }
    }
    return false;
}

int Graph2::max_flow_separated_groups(Graph2 g, int src, int dest) {
    int u, v;
    vector<vector<pair<int, int>>> rGraph = createResidualGraph(g);
    int max_flow = 0;
    while(bfs_for_scenario2(src, dest, rGraph)){
        int flow = INT32_MAX;
        for(v = dest; v != src; v = nodes[v].pred){
            u = nodes[v].pred;
            flow = min(flow, rGraph[u][v].first);
        }
        for(v = dest; v != src; v = nodes[v].pred){
            u = nodes[v].pred;
            rGraph[u][v].first -= flow;
            rGraph[v][u].first += flow;
        }
        max_flow += flow;
    }
    return max_flow;
}

int Graph2::edmondskarp(Graph2 g, int src, int dest) {
    int u, v;
    vector<vector<pair<int, int>>> rGraph = createResidualGraph(g);
    int max_flow = 0;
    while(bfs_for_scenario2(src, dest, rGraph)){
        int flow = INT32_MAX;
        for(v = dest; v != src; v = nodes[v].pred){
            u = nodes[v].pred;
            flow = min(flow, rGraph[u][v].first);
        }
        for(v = dest; v != src; v = nodes[v].pred){
            u = nodes[v].pred;
            rGraph[u][v].first -= flow;
            rGraph[v][u].first += flow;
        }
        max_flow += flow;
    }
    cout << "\nThe max flow of this graph is: " << max_flow << "\n";
    vector<vector<vector<int>>> flow_graph = create_Flux_graph(rGraph);
    cout << "A possible path is: \n";
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            if(flow_graph[i][j][2] <= 0 ) continue;
            else{
                cout << "   From node " << i << " to node " << j << ", " << flow_graph[i][j][2] << " people moved\n ";
            }

        }
    }


    return max_flow;
}

vector<vector<vector<int>>> Graph2::create_Flux_graph(vector<vector<pair<int, int>>> rGraph){
    vector<vector<vector<int>>> flow_graph;
    vector<vector<int>> edges;
    for(int i = 0; i <= n; i++){
        flow_graph.push_back(edges);
    }
    int i=0;
    while(i <= n){
        for(int it = 0; it <= n; it++){
            flow_graph[i].push_back({0,0,0});
        }
        i++;
    }

    int j = 1;
    while(j <= n){
        for(auto e: nodes[j].adj){
            int w = e.dest;
            int c = e.capacity;
            int d = e.duration;
        flow_graph[j][w] = {c, d, 0};
        }
        j++;
    }

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            flow_graph[i][j][2] = flow_graph[i][j][0] - rGraph[i][j].first;
        }
    }

    return flow_graph;
}

vector<vector<int>> Graph2::random_dimension_divided_groups(Graph2 g, int src, int dest, int dimension) {
    int u, v;
    vector<vector<int>> result;
    vector<vector<pair<int, int>>> rGraph = createResidualGraph(g);
    int max_flow = 0;
    while(bfs_for_scenario2(src, dest, rGraph) && max_flow < dimension){
        int flow = INT32_MAX;
        for(v = dest; v != src; v = nodes[v].pred){
            u = nodes[v].pred;
            flow = min(flow, rGraph[u][v].first);
        }
        for(v = dest; v != src; v = nodes[v].pred){
            u = nodes[v].pred;
            rGraph[u][v].first -= flow;
            rGraph[v][u].first += flow;
        }
        max_flow += flow;
    }
    int real_max_flow = max_flow_separated_groups(g, src, dest);
    if(dimension > real_max_flow){
        cout << "Given this dimension, it's impossible to arrive at node " << dest;
        return {{}};
    }
    vector<vector<vector<int>>> flow_graph = create_Flux_graph(rGraph);
    cout << "A possible path is: \n";
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            if(flow_graph[i][j][2] <= 0 ) continue;
            else if(flow_graph[i][j][2] > dimension) flow_graph[i][j][2] = dimension;
            cout << i << "->" << j << " ";
            result.push_back({i, j});

        }
    }


    return result;
}


int Graph2::minimum_time(Graph2 g, int a, int b) {
    MaxHeap <int> pq;
    int minimum_time = 0;
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
    //cout << "The maximum flow is: "  << nodes[b].flow << endl;
    vector<int> nds;
    int stops = 1;
    while (nodes[b].pred != 0) {
        nds.push_back(b);
        b = nodes[b].pred;
        stops++;
    }

    vector<vector<pair<int, int>>>rgraph = createResidualGraph(g);
    vector<vector<vector<int>>> flow_graph = create_Flux_graph(rgraph);
    minimum_time += flow_graph[a][nds[nds.size()-1]][1];
    for(int i = nds.size()-1; i >= 0; i--){
        for(int j = i-1; j >= 0; j--)
            minimum_time += flow_graph[nds[i]][nds[j]][1];
    }

    cout << "The minimum time of this path is: " << minimum_time;
    return minimum_time;
}

int Graph2::maximum_wait_time(Graph2 g, vector<vector<int>> p){

    int max_w_time = 0;
    vector<int> common_nodes;
    //firstly, let's see the nodes in which the groups can wait for each other
    for(int i = 0; i < p.size() - 1; i++){
        int copy = p[i][1];
        for(int j = i+1; j < p.size(); j++){
            int dest_node = p[j][1];
            if(dest_node == copy) common_nodes.push_back(dest_node);
        }
    }




    return max_w_time;
}