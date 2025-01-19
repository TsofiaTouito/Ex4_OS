#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

/**
 * @struct Edge
 * Represents an edge in a graph with two endpoints.
 */
struct Edge {
    unsigned int startVertex;
    unsigned int endVertex;
};

/**
 * @class Graph
 * Represents a simple undirected graph using an adjacency matrix.
 * Provides functionality to generate random graphs and find Eulerian circles.
 */
class Graph {
private:
    unsigned int vertexCount; ///< Number of vertices in the graph
    std::vector<std::vector<bool>> adjacencyMatrix; ///< Adjacency matrix representation of the graph

public:
    /**
     * Default constructor initializes an empty graph.
     */
    inline Graph() : vertexCount(0) {}

    /**
     * Constructs a graph with a specified number of vertices.
     * @param size Number of vertices in the graph
     */
    inline explicit Graph(unsigned int size)
        : vertexCount(size), adjacencyMatrix(size, std::vector<bool>(size, false)) {}

    /**
     * Constructs a random graph with the given number of vertices and edges.
     * @param vertexCount Number of vertices
     * @param edgeCount Number of edges
     * @param randomSeed Seed for random number generation (default: 42)
     * @throws std::invalid_argument if too many edges are requested
     */
    Graph(unsigned int vertexCount, unsigned int edgeCount, int randomSeed = 42);

    /**
     * Adds an edge between two vertices.
     * @param startVertex First vertex of the edge
     * @param endVertex Second vertex of the edge
     * @throws std::logic_error if the vertices are the same
     */
    void addEdge(unsigned int startVertex, unsigned int endVertex);

    /**
     * Adds an edge using an Edge structure.
     * @param edge Edge to be added
     */
    inline void addEdge(const Edge& edge) {
        addEdge(edge.startVertex, edge.endVertex);
    }

    /**
     * Finds an Eulerian circle in the graph, if one exists.
     * @return A vector of edges representing the Eulerian circle, or an empty vector if none exists
     */
    std::vector<Edge> findEulerianCircle() const;
};

#endif // GRAPH_HPP
