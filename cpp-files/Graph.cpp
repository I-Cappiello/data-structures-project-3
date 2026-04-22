#include "Graph.h"
#include <unistd.h> 
#include <iostream>
#include <algorithm>

using namespace std;
const int Graph::INT_MAX;

class UnionFind {
    vector<int> parent;
public:
    UnionFind(int n) : parent(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        return parent[x] == x ? x : (parent[x] = find(parent[x]));
    }
    
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;  // Already connected
        parent[x] = y;
        return true;
    }
};

// Adds a given vertex to the esies vector
void Graph::insert_vertex(const Vertex& ver) {
    if (get_vertex_index(ver) == -1) {
        vertices.push_back(ver); //insert the vertex to the array of vertices
        vector<Edge> tmp;
        edges.push_back(tmp); //insert empty vector to the edges
    }
}

// Finds the index of a given vertex within the verticies vector
int Graph::get_vertex_index(const Vertex& ver) {
    for(int i = 0; i < vertices.size(); i++) {
        if (vertices[i].getData() == ver.getData()) {
            return i;
        }
    }
    // If no matching vertex is found 
    return -1;
}

// Returns the nested/inner index of a given edge in the edges vector 
int Graph::find_edge(const Vertex& v1, const Vertex& v2){
    int i1 = get_vertex_index(v1);
    int i2 = get_vertex_index(v2);
    if (i1 == -1 || i2 == -1) {
        throw std::string("find_edge: incorrect vertices");
    }
    for(int i = 0; i < edges[i1].size(); i++){
        if(edges[i1][i].dest==i2){
            return i;
        }
    }
    // If no matching edge is found
    return -1;
}

// Adds an edge to a directed graph (and the edges vector)
void Graph::add_edge(const Vertex& ver1, const Vertex& ver2, int cost, int distance) {
    int i1 = get_vertex_index(ver1);
    int i2 = get_vertex_index(ver2);
    if (i1 == -1 || i2 == -1) {
        throw string("Add_edge: incorrect vertices");
    }
    Edge v(i1, i2, cost, distance);
    edges[i1].push_back(v);
}

// Adds an edge to an undirected graph (and the edges vector)
void Graph::add_undirected_edge(const Vertex& ver1, const Vertex& ver2, int cost, int distance) {
    int i1 = get_vertex_index(ver1);
    int i2 = get_vertex_index(ver2);
    if (i1 == -1 || i2 == -1) {
        throw std::string("Add_edge: incorrect vertices");
    }
    int ei1 = find_edge(ver1,ver2);
    int ei2 = find_edge(ver2,ver1);
    // If the edges have not been created yet
    if(ei1==-1){
        Edge v(i1, i2, cost, distance);
        Edge v2(i2, i1, cost, distance);
        edges[i1].push_back(v);
        if (i1 != i2) {
            edges[i2].push_back(v2);
        }
    }
    // If the edges have been created but the cost of the new edge is lower
    else{
        if(cost < edges[i1][ei1].cost){
            edges[i1][ei1].cost=cost;
            edges[i2][ei2].cost=cost;
        }
    }
}

// Prints out each vertex and its corresponding connected vertices, distance, and cost
void Graph::print() const {
    for (int i = 0; i < vertices.size(); i++) {
        cout << "{ " << vertices[i].getData() << ": ";
        for(int j = 0; j < edges[i].size(); j++) {
            cout << '{' << vertices[edges[i][j].dest].getData() << ", ";
            cout << edges[i][j].cost << ", ";
            cout << edges[i][j].distance << "} ";
        }
        cout << " }\n";
    }
}

// Finds the index a certain state is located at
int Graph::find_state_index(vector<string> states, string state){
    for(int j = 0; j < states.size();j++){
        if(states[j]==state){
            return j;
        }
    }
    return -1;
}

// Finds the index a certain airport is located
int Graph::find_airport(vector<vector<string>> airports, string airport, int sindex){
    for(int j = 0; j < airports[sindex].size();j++){
        if(airports[sindex][j]==airport){
            return j;
        }
    }
    return -1;
}

// Checks if a vertex is within a states (i is the index of a vertex in verticies)
bool Graph::isInState(int i, string state, vector<string> states, vector<vector<string>> airports){
    int si = find_state_index(states, state);
    string airportData = vertices[i].getData();
    if(si==-1){
        return false;
    }
    if(find_airport(airports,airportData,si)!=-1){
        return true;
    }
    return false;
}
//prints out the shortest path between origin and destination airports, with distance and cost
void Graph::shortestPath(string srcCode, string destCode) {
    // 1. Convert the strings to indices using your helper function
    int src = get_vertex_index(Vertex(srcCode));
    int dest = get_vertex_index(Vertex(destCode));

    // 2. Make sure the airports actually exist in your graph
    if (src == -1 || dest == -1) {
        cout << "Error: One or both airport codes (" << srcCode << ", " << destCode << ") not found." << endl;
        return;
    }

    int n = edges.size();
    vector<int> dist(n, INT_MAX);
    vector<int> totalCost(n, 0); 
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    dist[src] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        int minDist = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (auto &edge : edges[u]) {
            int v = edge.dest;
            int weight = edge.distance;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                totalCost[v] = totalCost[u] + edge.cost; 
                parent[v] = u;
            }
        }
    }

    // Header part of the output
    cout << "Shortest route from " << vertices[src].getData() << " to " 
         << vertices[dest].getData() << ": ";

    if (dist[dest] == INT_MAX) {
        cout << "None" << endl;
        return;
    }

    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++) {
        cout << vertices[path[i]].getData();
        if (i != path.size() - 1) cout << " -> ";
    }

    cout << ". The length is " << dist[dest] << ". The cost is " << totalCost[dest] << "." << endl;
}

//prints out the shortest paths from one airport to all airports in a specified state, alongside cost and distance
void Graph::shortestPathsToState(string srcCode, string state, vector<string> states, vector<vector<string>> airports) {
    // 1. Convert the starting airport code to an index
    int src = get_vertex_index(Vertex(srcCode));

    // 2. Validate that the starting airport exists
    if (src == -1) {
        cout << "Error: Starting airport code (" << srcCode << ") not found." << endl;
        return;
    }

    int n = edges.size();
    vector<int> dist(n, INT_MAX);
    vector<int> totalCost(n, 0); 
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    dist[src] = 0;

    // Dijkstra's Algorithm
    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        int minDist = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (auto &edge : edges[u]) {
            int v = edge.dest;
            if (!visited[v] && dist[u] + edge.distance < dist[v]) {
                dist[v] = dist[u] + edge.distance;
                totalCost[v] = totalCost[u] + edge.cost; 
                parent[v] = u;
            }
        }
    }

    bool found = false;

    // Header matches the sample output exactly
    cout << "\nShortest paths from " << vertices[src].getData() << " to " << state << " state airports are:\n" << endl;
    cout << "Path\t\t\tLength\t\tCost" << endl;

    for (int i = 0; i < n; i++) {
        // Filter by state using your isInState requirement
        if (isInState(i, state, states, airports) && dist[i] != INT_MAX) {
            found = true;
        
            vector<int> path;
            for (int v = i; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            reverse(path.begin(), path.end());

            string pathString = "";
            for (int j = 0; j < path.size(); j++) {
                pathString += vertices[path[j]].getData();
                if (j != path.size() - 1) pathString += "->";
            }

            // Aligned output
            cout << pathString;
            if (pathString.length() < 16) cout << "\t\t"; 
            else cout << "\t";
            
            cout << dist[i] << "\t\t" << totalCost[i] << endl;
        }
    }

    if (!found) {
        cout << "No paths to state " << state << endl;
    }
}

//prints out the shortest Path between an origin and destination airport, with max stops as a constraint
void Graph::shortestPathWithStops(string srcCode, string destCode, int maxStops) {
    // 1. Convert the airport codes to indices
    int src = get_vertex_index(Vertex(srcCode));
    int dest = get_vertex_index(Vertex(destCode));

    // 2. Validate the input
    if (src == -1 || dest == -1) {
        cout << "Error: One or both airport codes (" << srcCode << ", " << destCode << ") not found." << endl;
        return;
    }

    int n = edges.size();
    // dist[airport][stops]
    vector<vector<int>> dist(n, vector<int>(maxStops + 2, INT_MAX));
    // cost[airport][stops]
    vector<vector<int>> totalCost(n, vector<int>(maxStops + 2, INT_MAX));
    // parent[airport][stops]
    vector<vector<int>> parent(n, vector<int>(maxStops + 2, -1));

    dist[src][0] = 0;
    totalCost[src][0] = 0;

    // Dynamic Programming approach based on stops
    for (int stops = 0; stops <= maxStops; stops++) {
        for (int u = 0; u < n; u++) {
            if (dist[u][stops] == INT_MAX) continue;

            for (auto &edge : edges[u]) {
                int v = edge.dest;
                int newDist = dist[u][stops] + edge.distance;
                int newCost = totalCost[u][stops] + edge.cost;

                if (newDist < dist[v][stops + 1]) {
                    dist[v][stops + 1] = newDist;
                    totalCost[v][stops + 1] = newCost;
                    parent[v][stops + 1] = u;
                }
            }
        }
    }

    int bestDist = INT_MAX;
    int finalCost = 0;
    int bestStopCount = -1;

    // Find the best distance among all valid stop counts (up to maxStops)
    for (int i = 0; i <= maxStops + 1; i++) {
        if (dist[dest][i] < bestDist) {
            bestDist = dist[dest][i];
            finalCost = totalCost[dest][i];
            bestStopCount = i;
        }
    }

    if (bestDist == INT_MAX) {
        cout << "Shortest route from " << vertices[src].getData() << " to " 
             << vertices[dest].getData() << " with " << maxStops << " stops: None" << endl;
    } else {
        vector<int> path;
        int curr = dest;
        int currStop = bestStopCount;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr][currStop];
            currStop--;
        }
        reverse(path.begin(), path.end());

        cout << "Shortest route from " << vertices[src].getData() << " to " 
             << vertices[dest].getData() << " with " << maxStops << " stops: ";
        
        for (int i = 0; i < path.size(); i++) {
            cout << vertices[path[i]].getData();
            if (i != path.size() - 1) cout << " -> ";
        }
        
        cout << ". The length is " << bestDist << ". The cost is " << finalCost << "." << endl;
    }
}

void Graph::display_flight_connections() {
    struct AirportConnections {
        string name;
        int inbound;
        int outbound;
        int total;
    };
    
    vector<AirportConnections> airport_data;
    
    for (int i = 0; i < vertices.size(); i++) {
        AirportConnections ac;
        ac.name = vertices[i].getData();
        ac.outbound = edges[i].size();
        
        ac.inbound = 0;
        for (int j = 0; j < vertices.size(); j++) {
            for (int k = 0; k < edges[j].size(); k++) {
                if (edges[j][k].dest == i) {
                    ac.inbound++;
                }
            }
        }
        
        ac.total = ac.inbound + ac.outbound;
        airport_data.push_back(ac);
    }
    
// bubble sort by total count
for (int i = 0; i < airport_data.size() - 1; i++) {
    for (int j = 0; j < airport_data.size() - i - 1; j++) {
        if (airport_data[j].total < airport_data[j + 1].total) {
            AirportConnections temp = airport_data[j];
            airport_data[j] = airport_data[j + 1];
            airport_data[j + 1] = temp;
        }
    }
}
    cout << "Airport Flight Connections:\n";
    for (const auto& ac : airport_data) {
        cout << ac.name << ": " << ac.total <<" connections"
             << " (inbound: " << ac.inbound 
             << ", outbound: " << ac.outbound << ")" << endl;
    }
}

void Graph::prim_mst() {
    int n = vertices.size();
    
    if (n == 0) {
        cout << "Graph is empty. Cannot generate MST.\n";
        return;
    }
    
    vector<bool> in_mst(n, false);
    
    struct MSTEdge {
        int v1;
        int v2;
        int cost;
    };
    vector<MSTEdge> mst_edges;
    
    in_mst[0] = true;
    int vertices_in_mst = 1;
    int total_cost = 0;
    
    while (vertices_in_mst < n) {
        int min_cost = -1;
        int best_from = -1;
        int best_to = -1;
        
        for (int i = 0; i < n; i++) {
            if (!in_mst[i]) continue;
            
            for (int j = 0; j < edges[i].size(); j++) {
                int dest = edges[i][j].dest;
                int cost = edges[i][j].cost;
                
                if (!in_mst[dest]) {
                    if (min_cost == -1 || cost < min_cost) {
                        min_cost = cost;
                        best_from = i;
                        best_to = dest;
                    }
                }
            }
        }
        
        if (min_cost == -1) {
            cout << "Graph is disconnected. MST cannot be formed.\n";
            return;
        }
        
        in_mst[best_to] = true;
        vertices_in_mst++;
        total_cost += min_cost;
        
        MSTEdge edge;
        edge.v1 = best_from;
        edge.v2 = best_to;
        edge.cost = min_cost;
        mst_edges.push_back(edge);
    }
   cout << "\nMinimal Spanning Tree:\n";
cout << "Edge              Weight\n";

for (int i = 0; i < mst_edges.size(); i++) {
    string edge_str = vertices[mst_edges[i].v1].getData() + " - " + 
                     vertices[mst_edges[i].v2].getData();
    
    // Pad to 18 characters
    while (edge_str.length() < 18) {
        edge_str += " ";
    }
    
    cout << edge_str << mst_edges[i].cost << "\n";
}

cout << "\nTotal Cost of MST: " << total_cost << "\n\n";
}

void Graph::check_connectivity() {
    int n = vertices.size();
    if (n == 0) return;
    
    vector<bool> visited(n, false);
    vector<int> queue;
    queue.push_back(0);
    visited[0] = true;
    int reachable = 1;
    
    int front = 0;
    while (front < queue.size()) {
        int current = queue[front++];
        for (int i = 0; i < edges[current].size(); i++) {
            int neighbor = edges[current][i].dest;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push_back(neighbor);
                reachable++;
            }
        }
    }
    
    cout << "\nCONNECTIVITY CHECK! (for MST output to actually work)\n";
    cout << "Total: " << n << " | Reachable: " << reachable << "\n";
    
    if (reachable == n) {
        cout << "CONNECTED\n\n";
    } else {
        cout << "DISCONNECTED - Unreachable airports:\n";
        for (int i = 0; i < n; i++) {
            if (!visited[i]) cout << "  - " << vertices[i].getData() << "\n";
        }
        cout << "\n";
    }
}

void Graph::Kruskal_MST(){
    int n = vertices.size();
    if (n == 0){
        cout <<"graph is empty. \n";
        return;
    }
    
    vector<Edge> all_edges;
    
    for (int i = 0; i<n; i++){
        for (int j = 0; j < edges[i].size(); j++){
            if (i < edges[i][j].dest){
                all_edges.push_back(edges[i][j]);
            }
        }
    }
    
    for (int i = 0; i < all_edges.size() - 1; i++){
        for (int j = 0; j < all_edges.size() - i - 1; j++){
            if (all_edges[j+1] < all_edges[j]) {
                Edge temp = all_edges[j];
                all_edges[j] = all_edges[j+1];
                all_edges[j+1] = temp;
            }
        }
    }

    
    
    UnionFind uf(n);
    vector<Edge> mst_edges;
    int total_cost = 0;
    
    for (int i = 0; i < all_edges.size(); i++){
        Edge edge = all_edges[i];
    
            if (uf.unite(edge.src, edge.dest)) {
            mst_edges.push_back(edge);
            total_cost += edge.cost;
        }
    }
    
    cout <<"\nMinimal Spanning Tree:\n";
    cout << "Edge     Weight\n";
    
    for (int i = 0; i < mst_edges.size(); i++) {
        string edge_str = vertices[mst_edges[i].src].getData() + " - " + vertices[mst_edges[i].dest].getData();
        
        while(edge_str.length() < 18){
            edge_str += " ";
        }
        cout << edge_str << mst_edges[i].cost << "\n";
    }
    
    cout << "\nTotal Cost of MST: " << total_cost << "\n\n";
    
}
