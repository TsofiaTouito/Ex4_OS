#include "Graph.hpp"
#include <iostream>
#include <getopt.h>

int main(int argc, char* argv[]) {
    unsigned int vertexCount, edgeCount;
    int randomSeed;

    if (argc != 7) {
        std::cerr << "Usage: " << argv[0] << " -n <vertices> -m <edges> -s <seed>\n";
        return 1;
    }

    int option;
    while ((option = getopt(argc, argv, "n:m:s:")) != -1) {
        switch (option) {
            case 'n':
                vertexCount = std::stoi(optarg);
                break;
            case 'm':
                edgeCount = std::stoi(optarg);
                break;
            case 's':
                randomSeed = std::stoi(optarg);
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -n <vertices> -m <edges> -s <seed>\n";
                return 1;
        }
    }

    try {
        Graph graph(vertexCount, edgeCount, randomSeed);
        auto eulerianCircle = graph.findEulerianCircle();

        if (eulerianCircle.empty()) {
            std::cout << "No Eulerian circle exists.\n";
        } else {
            std::cout << "Eulerian circle found: ";
            std::cout << eulerianCircle.front().startVertex;
            for (const auto& edge : eulerianCircle) {
                std::cout << " -> " << edge.endVertex;
            }
            std::cout << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
