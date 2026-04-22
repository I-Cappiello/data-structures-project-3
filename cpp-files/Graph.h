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
    Graph() {}

    void insert_vertex(const Vertex& ver); // Adds vertex to verticies vector
    void add_edge(const Vertex& ver1, const Vertex& ver2, int cost, int distance); //connect ver1 with ver2
    
    void add_undirected_edge(const Vertex& ver1, const Vertex& ver2, int cost, int distance); //connects ver1 and ver2
    
    void print() const; //prints out all vertices and connected vertices (and their weights)

    void shortestPath(int src, int dest);

    void shortestPathsToState(int src, string state);

    void shortestPathWithStops(int src, int dest, int maxStops);

     void display_flight_connections();
    
    void prim_mst();
    
    void check_connectivity();
    
    void Kruskal_MST();


    //void DFS(Vertex& ver);
    //void BFS(Vertex& ver);

    //int shortest_path(const Vertex& src, const Vertex& dest);
    //int dijkstra_shortest_path(const Vertex& src, const Vertex& dest);

private:
    vector<Vertex> vertices; //nodes
    vector<vector<Edge>> edges; //connections
    
    // Helper Functions
    void clean_visited(); // Sets all vertex's visited to false
    void DFS_helper(Vertex& ver); // Helps with DFS
    int get_vertex_index(const Vertex& ver); // Grabs the index of a given vertex
    int get_edge_index();
    int find_edge(const Vertex& v1, const Vertex& v2);
    bool isInState(int index, string state);
};

#endif
