#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <stack>
#include <unordered_set>
#include <sstream>

// INF is used to ensure no edge has a larger cost.
// True INF is not possible, so it is set as the upper limit of int
const int INF = std::numeric_limits<int>::max();
// True inf cannot be added to or subtracted from, this is not the case here
// so extra checks are needed

struct Edge {
    int from; // index of vertex
    int to; // index of vertex
    int cost; // weight of edge
};


void printPath(std::vector<int> &predecessors, int source, int destination){
    std::stack<int> path;
    int i = destination;

    // Follow the predecessor of each vertex backwards util we reach source
    // Each vertex we follow is added to stack.
    while (i != -1 && i != source){
        path.push(i);
        i = predecessors[i];
    }

    // Empty the stack and print the contents;
    path.push(source);
    std::cout << "Path: ";
    while (!path.empty()) {
        std::cout << path.top();
        path.pop();
        if (!path.empty()) {
            std::cout << "->";
        }
    }
    std::cout <<std::endl;


}

bool cycleIsNegative(const std::vector<Edge>& edges, std::vector<int> cycle){
    // Checks if the total cost of a cycle is negative

    cycle.push_back(cycle[0]);
    int cost = 0;

    for (int i = 0; i < cycle.size(); ++i) {
        for (auto &j : edges) {
            int from = cycle[i];
            int to;
            if (i+1 >= cycle.size()){
                to = cycle[0];
            } else{
                to = cycle[i+1];
            }

            if (j.from == from && j.to == to){
                cost += j.cost;
            }
        }
    }

    if (cost < 0){
        return true;
    }


    std::reverse(cycle.begin(), cycle.end());

    cost = 0;

    for (int i = 0; i < cycle.size(); ++i) {
        for (auto &j : edges) {
            int from = cycle[i];
            int to;
            if (i+1 >= cycle.size()){
                to = cycle[0];
            } else{
                to = cycle[i+1];
            }

            if (j.from == from && j.to == to){
                cost += j.cost;
            }
        }
    }
    if (cost < 0){
        return true;
    }

    return false;
}

void negativeCycle(const std::vector<Edge>& edges, std::vector<int> &predecessors) {
    // Finds all cycles from a list of predecessors vertices

    std::vector<std::string> cycles;  // Store all detected cycles
    std::vector<bool> globalVisited(predecessors.size(), false);  // Vertices that are part of any detected cycle

    // Loop through all vertices
    for (int start = 0; start < predecessors.size(); ++start) {
        if (globalVisited[start]) {
            // Skip vertices that are already part of a detected cycle
            continue;
        }

        std::vector<bool> visited(predecessors.size(), false);  // Local visited for current cycle detection
        int current = start;
        std::vector<int> path;  // Path to store the current traversal
        bool cycleDetected = false;

        // Traverse back using predecessors to find a cycle
        while (current != -1 && !visited[current]) {
            visited[current] = true;
            path.push_back(current);
            current = predecessors[current];
        }

        if (current != -1 && visited[current] && cycleIsNegative(edges, path)) {
            int cycleStartIndex = std::find(path.begin(), path.end(), current) - path.begin();

            std::string cycleStr;

            for (int i = cycleStartIndex; i < path.size(); ++i) {
                cycleStr += std::to_string(path[i]);
                if (i != path.size() - 1) {
                    cycleStr += "-";
                }
            }

            // Add this cycle to the global cycle list
            cycles.push_back(cycleStr);

            // Mark all nodes in the cycle as visited globally
            for (int i = cycleStartIndex; i < path.size(); ++i) {
                globalVisited[path[i]] = true;
            }

            cycleDetected = true;
        }

        if (cycleDetected) {
            std::string top = cycles.back().substr(0, cycles.back().find("-"));
            std::cout <<"Negative cycle detected: " <<cycles.back() <<"-" <<top <<std::endl;
        }
    }

    if (!cycles.empty()) {
        std::cout <<"Total number of negative cycles detected: " <<cycles.size() << std::endl;
    } else {
        std::cout <<"No negative cycle detected." <<std::endl;
    }
}

bool comp(const std::vector<Edge>& edges, int from, int to, int pre){
    // Compares the cost of an edge between a destination vertex
    // and two sources. If the cost from "from" is lesser, returns true

    int preCost = INF;
    int newCost = INF;

    for (auto &i : edges) {
        if (i.to == to && i.from == pre){
            preCost = i.cost;
        }
        if (i.from == from && i.to == to){
            newCost = i.cost;
        }
    }
    if (newCost < preCost){
        return true;
    }
    return false;
}



void bellmanFord(int source, int vertices, const std::vector<Edge>& edges) {
    std::vector<int> distance(vertices, INF); // Cost to reach each vertex. index = id
    std::vector<bool> reachable(vertices, true); // Vertices caught in negative weight cycle
    std::vector<int> predecessors(vertices, -1); // Predecessor of each vertex. -1 = no previous node
    distance[source] = 0;
    std::vector<int> minPre(vertices, -1); // Predecessor of a vertex following the edge with lowest cost.


    // Relax all edges (vertices -1) times
    for (int i = 0; i < vertices; ++i) {
        for (const auto& edge : edges) {
            if (comp(edges, edge.from, edge.to, predecessors[edge.to])){
                minPre[edge.to] = edge.from;
            }
            // If cost of edge from "from" to "to" is less than the already stored cost
            // of travel to "to", we update the cost of "to"
            // INF plus cost will lead to overflow. Extra checks as "true" INF not possible
            if (distance[edge.from] != INF && distance[edge.from] + edge.cost < distance[edge.to]){
                distance[edge.to] = distance[edge.from] + edge.cost;
                predecessors[edge.to] = edge.from;
            }
        }
    }


    // Run again to detect negative weight cycles

    for (int i = 0; i < vertices -1; ++i) {
        for (auto &edge : edges) {
            // Edges should already be relaxed, if we can still reduce cost of edges,
            // it is caught in a negative cycle
            // -INF plus negative weight will lead to underflow. Extra checks as "true" INF not possible
            if (distance[edge.from] == -INF || (distance[edge.from] != INF && distance[edge.from] + edge.cost < distance[edge.to])){
                distance[edge.to] = -INF;
                reachable[edge.to] = false;
            }
        }
    }

    int negativeVertexCount = 0;
    for (int i = 0; i < reachable.size(); ++i) {
        if (!reachable[i]){
            negativeVertexCount++;
        }
    }


    // Print the results
    std::cout << "Shortest paths from source vertex " << source << ":" <<std::endl;
    for (int i = 0; i < vertices; ++i) {
        if (!reachable[i]) {
            std::cout << "Vertex " << i << " is unreachable due to a negative cycle." <<std::endl;
        } else if (distance[i] == INF) {
            std::cout << "Vertex " << i << " is unreachable from source." <<std::endl;
        } else {
            std::cout << "Vertex " << i << ": Cost = " << distance[i] <<", ";
            printPath(predecessors, source, i);
        }
    }

    std::cout << "Total number of vertices caught in negative weight cycles detected: " << negativeVertexCount << std::endl;
        negativeCycle(edges, minPre);
}


std::vector<Edge> getEdgesFromAdjMatrix(const std::vector<std::vector<int>> &adjMatrix) {
    // Converts adjacency matrix to edge list.
    // Assuming the matrix has coordinates, y is the current vertex we are looking at,
    // and x is the vertices that y can reach directly.

    std::vector<Edge> edges;

    int nVertices = adjMatrix.size();

    for (int y = 0; y < nVertices; ++y) {
        for (int x = 0; x < nVertices; ++x) {

            if (adjMatrix[y][x] != INF && adjMatrix[y][x] != 0) {
                edges.push_back({y, x, adjMatrix[y][x]});
            }
        }
    }
    return edges;
}

int main() {
    int vertices;
    int source;
    std::cout << "Enter the number of vertices: ";
    std::cin >> vertices;

    std::vector<std::vector<int>> adjMatrix(vertices, std::vector<int>(vertices));

    // 0 is if a vertex doesn't have a connection to itself, INF is if a vertex can't reach another vertex directly
    std::cout << "Enter the adjacency matrix (use 'INF' for infinity, 0 for no self-loop):\n";
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            std::string input;
            std::cin >> input;
            if (input == "INF") {
                adjMatrix[i][j] = INF;
            } else {
                adjMatrix[i][j] = std::stoi(input);
            }
        }
    }

    std::cout << "Enter the index of source vertex: ";
    std::cin >> source;

    std::vector<Edge> edges = getEdgesFromAdjMatrix(adjMatrix);

    bellmanFord(source, vertices, edges);

    return 0;
}