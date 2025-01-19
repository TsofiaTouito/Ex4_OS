#include "Graph.hpp"
#include <stack>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>

/**
 * Constructs a random graph with the specified number of vertices and edges.
 */
Graph::Graph(unsigned int vertexCount, unsigned int edgeCount, int randomSeed)
    : Graph(vertexCount) {
    if (edgeCount > (vertexCount * (vertexCount - 1)) / 2) {
        throw std::invalid_argument("Too many edges for the given number of vertices.");
    }
    srand(randomSeed);

    // Generate all possible edges
    std::vector<Edge> potentialEdges;
    potentialEdges.reserve((vertexCount * (vertexCount - 1)) / 2);
    for (unsigned int i = 0; i < vertexCount - 1; i++) {
        for (unsigned int j = i + 1; j < vertexCount; j++) {
            potentialEdges.push_back({i, j});
        }
    }

    // Randomly remove edges to meet the desired edge count
    while (potentialEdges.size() > edgeCount) {
        unsigned int randomIndex = rand() % potentialEdges.size();
        std::swap(potentialEdges[randomIndex], potentialEdges.back());
        potentialEdges.pop_back();
    }

    // Add the remaining edges to the graph
    for (const auto& edge : potentialEdges) {
        addEdge(edge);
    }
}

/**
 * Adds an edge between two vertices.
 */
void Graph::addEdge(unsigned int startVertex, unsigned int endVertex) {
    if (startVertex == endVertex) {
        throw std::logic_error("Self-loops are not allowed in simple graphs.");
    }
    adjacencyMatrix.at(startVertex).at(endVertex) = true;
    adjacencyMatrix.at(endVertex).at(startVertex) = true;
}

/**
 * Finds an Eulerian circle in the graph, if one exists.
 */
std::vector<Edge> Graph::findEulerianCircle() const {
    std::vector<unsigned int> vertexDegree(vertexCount, 0);

    // Calculate vertex degrees and check for odd degrees
    for (unsigned int i = 0; i < vertexCount; i++) {
        for (unsigned int j = 0; j < vertexCount; j++) {
            vertexDegree[i] += adjacencyMatrix[i][j];
        }
        if (vertexDegree[i] % 2 == 1) {
            return {}; // No Eulerian circle exists
        }
    }

    // Identify starting vertex
    unsigned int startVertex = vertexCount;
    for (unsigned int i = 0; i < vertexCount; i++) {
        if (vertexDegree[i] > 0) {
            startVertex = i;
            break;
        }
    }
    if (startVertex == vertexCount) {
        return {}; // No edges in the graph
    }

    // Find the Eulerian circle
    std::vector<Edge> eulerianCircle;
    std::stack<unsigned int> traversalStack;
    std::vector<std::vector<bool>> matrixCopy = adjacencyMatrix;

    traversalStack.push(startVertex);
    while (!traversalStack.empty()) {
        unsigned int currentVertex = traversalStack.top();
        bool edgeFound = false;

        // Search for an edge from the current vertex
        for (unsigned int nextVertex = 0; nextVertex < vertexCount; nextVertex++) {
            if (matrixCopy[currentVertex][nextVertex]) {
                matrixCopy[currentVertex][nextVertex] = matrixCopy[nextVertex][currentVertex] = false;
                traversalStack.push(nextVertex);
                edgeFound = true;
                break;
            }
        }

        if (!edgeFound) {
            traversalStack.pop();
            if (!traversalStack.empty()) {
                unsigned int previousVertex = traversalStack.top();
                eulerianCircle.push_back({currentVertex, previousVertex});
            }
        }
    }

    return eulerianCircle;
}
