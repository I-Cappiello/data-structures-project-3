#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Reads a given csv file and outputs a 2D vector containing all cells
// NOTE: does not actually work with csv files, I convereted airports.csv to a txt file to work
vector<vector<string>> readCSV(const string& filename) {
    vector<vector<string>> data;    // The 2D vector that stores cell data
    ifstream file(filename);        // Opens the file
    
    // Should the file not exist
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return data;
    }
    
    bool first = true;      // If the first line is being parsed
    string line;            // Stores the current line
    while (getline(file, line)) {
        vector<string> row;     // Stores a row's cell strings
        stringstream ss(line);  // Allows us to read/write from a given line
        string cell;            // Stores cell string
        int i = 0;              // Increment
        while (getline(ss, cell, ',')) {
            // Skips over Origin_City and Destinitation_City
            if(first && (i == 4 || i==5)){
                row.push_back(cell);
            }
            // Skips over Origin_City and Destinitation_City
            else if(i<2 || i > 5){
                row.push_back(cell);
            }
            i++;
        }
        first=false;
        // Row vector passed to data
        data.push_back(row);
    }
    // Closes file and returns 2D vector
    file.close();
    return data;
}

int main() {
    // Stores csv data as well as its size
    auto data = readCSV("airports.txt");
    // Cancels program if data is empty
    if(data.empty()){
        cout << "No data loaded.\n";
        return 0;
    }
    int numRows = data.size();
    int numCol = data[0].size();
    Graph g;
    Graph g_u;
    
    // Enters data into directed and undirected graphs g and g_u
    for(int i = 1; i < numRows;i++){
        Vertex v1(data[i][0]);
        Vertex v2(data[i][1]);
        g.insert_vertex(v1);
        g_u.insert_vertex(v1);
        g.insert_vertex(v2);
        g_u.insert_vertex(v2);
        g.add_edge(v1,v2,stoi(data[i][2]),stoi(data[i][3]));
        g_u.add_undirected_edge(v1,v2,stoi(data[i][2]),stoi(data[i][3]));
    }
    
    // Prints directed graph data
    g_u.print();
    g_u.shortestPath();
    g_u.shortestPathsToState();
    g_u.shortestPathWithStops();
    g.display_flight_connections();
    return 0;
}
