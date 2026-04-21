#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
    // Constructor
    Edge(int src = 0, int dest = 0, int cost = 0, int distance = 0) : 
        src(src), dest(dest), cost(cost), distance(distance) {}
    
    // Compares an edge to another edge using cost as the determining factor
    bool operator<(const Edge& other) const {
        if(this->cost < other.cost) {
            return true;
        }
        return false;
    }
    
    // Compares the distance between two edges
    bool compare_distance(const Edge& other) const{
        if(this->distance < other.distance){
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
