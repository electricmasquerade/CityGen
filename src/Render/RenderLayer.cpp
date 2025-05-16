#include "RenderLayer.h"

#include "../City/RoadGraph.h"


void RenderLayer::buildRoadMesh(const City::RoadGraph &graph) {
    m_roadVertices.clear();
    // Loop through all vertices in the graph
    for (auto const &edge: graph.getEdges()) {
        const auto &startVertex = graph.getVertices()[edge.startVertexId];
        const auto &endVertex = graph.getVertices()[edge.endVertexId];

        //create offsets to center the road in the window
        const float x_offset = static_cast<int>(m_Window.getSize().x / 2.f);
        const float y_offset = static_cast<int>(m_Window.getSize().y / 2.f);
        // Create a line between the start and end vertices
        sf::Vertex start;
        //positions have to be moved to center of window
        start.position = {10*startVertex.x + x_offset, 10*startVertex.y + y_offset};
        start.color = sf::Color::Black; // Set color for the start vertex
        sf::Vertex end;
        end.position = {10*endVertex.x + x_offset, 10*endVertex.y + y_offset};
        end.color = sf::Color::Black; // Set color for the end vertex

        m_roadVertices.append(start);
        m_roadVertices.append(end);
    }
}


void RenderLayer::renderRoads() const {
    m_Window.draw(m_roadVertices);
}
