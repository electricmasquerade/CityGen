#include "RoadGraph.h"

int City::RoadGraph::addVertex(float x, float y) {
    const int id = m_nextVertexId++;
    m_vertices.push_back({id, x, y, {}});
    return id;
}

int City::RoadGraph::addEdge(const int startVertexId, const int endVertexId) {
    const int id = m_nextEdgeId++;
    m_edges.push_back({id, startVertexId, endVertexId});
    m_vertices[startVertexId].edges.push_back(id);
    m_vertices[endVertexId].edges.push_back(id);
    return id;
}
