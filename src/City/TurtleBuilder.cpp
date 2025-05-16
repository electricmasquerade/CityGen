#include "TurtleBuilder.h"

void City::TurtleBuilder::createGraph() {
    //use CitySymbols and turtle graphics to create a graph from the L-system string
    //create the graph
    for (const char c: m_lSystemString) {
        //convert c to string to check if it is a command symbol

        //check if the character is a command symbol
        if (isCommandSymbol(c)) {
            switch (c) {
                case kForward:
                    moveForward();
                    break;
                case kRight:
                    turn(90.0f);
                    break;
                case kLeft:
                    turn(-90.0f);
                    break;
                case kPush:
                    pushState();
                    break;
                case kPop:
                    popState();
                    break;
                default:
                    break;
            }
        }
    }
}

void City::TurtleBuilder::moveForward() {
    //take heading to calculate new position
    //move forward by 5 meters each time

    const float newX = m_currentState.x + (std::cos(m_currentState.angle * M_PI / 180.0f));
    const float newY = m_currentState.y + (std::sin(m_currentState.angle * M_PI / 180.0f));

    // create and add new vertex to graph
    const int newVertexId = m_graph.addVertex(newX, newY);

    //add edge to graph from current vertex
    m_graph.addEdge(m_currentState.currentVertexID, newVertexId);
    //update current state
    m_currentState.x = newX;
    m_currentState.y = newY;
    m_currentState.currentVertexID = newVertexId;
}

void City::TurtleBuilder::turn(const float angle) {
    //turn the turtle, with some random variation



    m_currentState.angle += angle;
    if (m_currentState.angle > 360.0f) {
        m_currentState.angle -= 360.0f;
    } else if (m_currentState.angle < 0.0f) {
        m_currentState.angle += 360.0f;
    }
}

void City::TurtleBuilder::pushState() {
    //push the current state to the stack
    m_stateStack.push(m_currentState);
}

void City::TurtleBuilder::popState() {
    //pop the state from the stack to restore the previous state
    if (!m_stateStack.empty()) {
        m_currentState = m_stateStack.top();
        m_stateStack.pop();
    }
}
