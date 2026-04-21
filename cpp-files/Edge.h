#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
    // Constructor
    Edge(int src = 0, int dest = 0, int cost = 0, int distance = 0) : 
        src(src), dest(dest), cost(cost), distance(distance) {}
    
    // Compares an egdge to another edge
    bool operator<(const Edge& other) const {
        if(this->cost < other.cost) {
            return true;
        }
        return false;
    }
    
    // Variables
    int src;        // Origin Vertex Index
    int dest;       // Destination Vertex Index
    int cost;       // Cost weight
    int distance;   // Distance weight
};

#endif

