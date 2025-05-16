#pragma once
#include <vector>

//this handles the data management for the road graph, storing vertices and edges

namespace City {
    struct Edge {
        int id;
        int startVertexId; // ID of the starting vertex
        int endVertexId; // ID of the ending vertex
    };


    struct Vertex {
        int id;
        float x, y; // Coordinates of the vertex
        std::vector<int> edges; // List of edges connected to this vertex
    };

    class RoadGraph {
    public:
        int addVertex(float x, float y);

        int addEdge(int startVertexId, int endVertexId);
        void reset();

        //getters
        [[nodiscard]] const std::vector<Vertex> &getVertices() const { return m_vertices; }
        [[nodiscard]] const std::vector<Edge> &getEdges() const { return m_edges; }

    private:
        std::vector<Vertex> m_vertices;
        std::vector<Edge> m_edges;

        int m_nextVertexId = 0; // ID for the next vertex to be added
        int m_nextEdgeId = 0; // ID for the next edge to be added
    };
}
