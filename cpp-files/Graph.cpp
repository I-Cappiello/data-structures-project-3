#include "Graph.h"
// #include "MinHeap.h"
// #include "MinHeap.cpp"

#include <unistd.h> 
#include <iostream>

using namespace std;

// Adds a given vertex to the verticies vector
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

// The below functions are commented out for my own sanity.
/*
void Graph::DFS(Vertex& ver) {
    clean_visited();
    DFS_helper(ver);
    clean_visited();
}

void print_queue(VertexQueue q) {
  while (!q.empty())
  {
    cout << q.front().getData() << " ";
    q.pop();
  }
  cout << endl;
}

void Graph::BFS(Vertex& ver) {
    clean_visited();

    int i = get_vertex_index(ver);
    if (i == -1) {
        throw string("BFS: Vertex is not in the graph");
    }
    IntQueue q;
    q.push(i);
    vertices[i].setVisited(true);

    while (!q.empty()) {
        int i = q.front();
        cout << vertices[i].getData() << ' ';
        for(int j = 0; j < edges[i].size(); j++) {
            int adjacent_ver = edges[i][j].dest;
            if (vertices[adjacent_ver].getVisited() == false) {
                vertices[adjacent_ver].setVisited(true);
                q.push(adjacent_ver);
            }
        }
        q.pop();
    }

    clean_visited();
}

void Graph::clean_visited() {
    for(Vertex& v : vertices) {
        v.setVisited(false);
    }
}


void Graph::DFS_helper(Vertex& ver) {
    int i = get_vertex_index(ver);
    if (i == -1) {
        throw string("DFS: Vertex is not in the graph");
    }
    vertices[i].setVisited(true); //visit the current vertex
    cout << vertices[i].getData() << ' '; //print the data of the current vertex
    for(int j = 0; j < edges[i].size(); j++) {
        Vertex adjacent_ver = vertices[edges[i][j].dest];
        if (adjacent_ver.getVisited() == false) {
            DFS_helper(adjacent_ver);
        }
    }
}

int Graph::shortest_path(const Vertex& src, const Vertex& dest) {
    int i_src = get_vertex_index(src);
    int i_dest = get_vertex_index(dest);

    if (i_src == -1 || i_dest == -1) {
        throw string("Shortest path: incorrect vertices"); 
    }

    clean_visited();
    vector<int> distances(vertices.size()); //represents the distances from source to all other vertices

    //set initial distances
    for(int i = 0; i < distances.size(); i++) {
        distances[i] = (i == i_src) ? 0 : INT_MAX;
    }

    IntQueue q;
    q.push(i_src);

    while (!q.empty()) {
        int i = q.front();
        //check the neighbours of the current node
        for(int j = 0; j < edges[i].size(); j++) {
            int i_adjacent_ver = edges[i][j].dest;
            if (vertices[i_adjacent_ver].getVisited() == false) {
                q.push(i_adjacent_ver);
                int dist_from_source = distances[i] + edges[i][j].distance;
                if (dist_from_source < distances[i_adjacent_ver]) {
                    distances[i_adjacent_ver] = dist_from_source;
                    //test how the distances change
                    for(int i : distances) {
                        cout << i << ' ';
                    }
                    cout << '\n';
                }
            }
        }
        vertices[i].setVisited(true);
        q.pop();
    }

    clean_visited();

    return distances[i_dest];
}

int Graph::dijkstra_shortest_path(const Vertex& src, const Vertex& dest) {
    int i_src = get_vertex_index(src);
    int i_dest = get_vertex_index(dest);

    if (i_src == -1 || i_dest == -1) {
        throw string("Shortest path: incorrect vertices"); 
    }

    clean_visited();
    vector<int> distances(vertices.size()); //represents the distances from source to all other vertices

    //set initial distances
    for(int i = 0; i < distances.size(); i++) {
        distances[i] = (i == i_src) ? 0 : INT_MAX;
    }

    MinHeap<Edge> heap;
    int vertices_visited = 0;
    int cur_ver = i_src;

    while (vertices_visited < vertices.size()) {
        int i = cur_ver;
        //check the neighbours of the current node
        for(int j = 0; j < edges[i].size(); j++) {
            int i_adjacent_ver = edges[i][j].dest;
            if (vertices[i_adjacent_ver].getVisited() == false) {
                heap.insert(edges[i][j]);
                int dist_from_source = distances[i] + edges[i][j].distance;
                if (dist_from_source < distances[i_adjacent_ver]) {
                    distances[i_adjacent_ver] = dist_from_source;
                    //test how the distances change
                    for(int i : distances) {
                        cout << i << ' ';
                    }
                    cout << '\n';
                }
            }
        }
        Edge e = heap.delete_min();
        cur_ver = e.dest;        
        vertices[i].setVisited(true);
        vertices_visited++;
    }

    clean_visited();

    return distances[i_dest];
}
*/
