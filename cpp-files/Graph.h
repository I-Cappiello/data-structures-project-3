#ifndef GRAPH_H
#define GRAPH_H
#include "Vertex.h"
#include "Edge.h"
#include <vector>
using namespace std;

class Graph {
public:
    // Meant for the algorithms, a stand in for infinity (no price should be this high, I hope. If it is, just add another 0.)
    const static int INT_MAX = 100000;
    
    Graph() {} // Constructor
    void insert_vertex(const Vertex& ver); // Adds vertex to verticies vector
    void add_edge(const Vertex& ver1, const Vertex& ver2, int cost, int distance); //connect ver1 with ver2
    void add_undirected_edge(const Vertex& ver1, const Vertex& ver2, int cost, int distance); //connects ver1 and ver2
    void print() const; //prints out all vertices and connected vertices (and their weights)
    void shortestPath(string srcCode, string destCode); //Finds the shortest path between two airports
    void shortestPathsToState(string srcCode, string state, vector<string> states, vector<vector<string>> airports); // Finds the shortest path from an airport to all connected airports in a given state
    void shortestPathWithStops(string srcCode, string destCode, int maxStops); // Finds the shortest path between two airports with a number of stops
    void display_flight_connections(); // Finds the number of direct flights to and from all airports
    void prim_mst(); // Finds the minimum spanning tree with Prim's Method
    void check_connectivity(); // Checks the connectivity of the graph and displays unnconnected airports
    void Kruskal_MST(); // Finds the minimum spanning tree with Kruskal's method

private:
    vector<Vertex> vertices; //nodes
    vector<vector<Edge>> edges; //connections
    
    // Helper Functions
    int get_vertex_index(const Vertex& ver); // Grabs the index of a given vertex
    int find_edge(const Vertex& v1, const Vertex& v2); // Finds the inner index of an edge
    int find_state_index(vector<string> states, string state); // Finds the index of a state within a vector
    int find_airport(vector<vector<string>> airports, string airport, int sindex); // Finds the inner index of an airport within a 2D vector
    bool isInState(int i, string state, vector<string> states, vector<vector<string>> airports); // Determines if an airport is within a state
    
};

#endif
