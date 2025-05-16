#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace City {
    class RoadGraph;
}

class RenderLayer {
    //this class handles drawing all of the layers of the city
public:
    explicit RenderLayer(sf::RenderWindow &window)
        : m_Window(window) {
        m_roadVertices.setPrimitiveType(sf::PrimitiveType::Lines);
    }

    void buildRoadMesh(const City::RoadGraph &graph);

    void renderRoads() const;

private:
    sf::RenderWindow &m_Window;
    sf::VertexArray m_roadVertices;
};
