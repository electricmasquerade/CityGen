#pragma once
#include <stack>

#include "RoadGraph.h"
#include "LSystemGenerator.h"
#include "CitySymbols.h"
#include <SFML/Graphics.hpp>

// this class handles turning the L-system string into a road graph.
// all units are assumed to be in meters.
namespace City {
    struct State {
        float x, y;
        float angle; //angle in degrees
        int currentVertexID; // ID of the current vertex
    };


    class TurtleBuilder {
    public:
        TurtleBuilder(const LSystemGenerator &lSystem, RoadGraph &rGraph): m_graph(rGraph),
                                                                           m_lSystemString(
                                                                               lSystem.getGeneratedString()) {
            //init current state
            m_currentState.x = 0.0f;
            m_currentState.y = 0.0f;
            m_currentState.angle = 0.0f;
            m_currentState.currentVertexID = m_graph.addVertex(m_currentState.x, m_currentState.y);
        }

        ~TurtleBuilder() = default;

        void createGraph();

        void moveForward();

        void turn(float angle);

        void pushState();

        void popState();

    private:
        std::string m_lSystemString;
        RoadGraph &m_graph;

        std::stack<State> m_stateStack; // Stack to store the state of the turtle
        State m_currentState{}; // Current state of the turtle
    };
}
