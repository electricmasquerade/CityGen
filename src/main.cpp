#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <cassert>
#include <iostream>

#include "City/RoadGraph.h"
#include "City/LSystemGenerator.h"
#include "City/TurtleBuilder.h"
#include "Render/RenderLayer.h"

int main() {
    // Create the main window
    constexpr unsigned windowWidth = 1000;
    constexpr unsigned windowHeight = windowWidth * 0.8;
    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Maze Algorithms");
    window.setFramerateLimit(120);
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    // Create a render layer for the city
    City::RoadGraph roadGraph;
    RenderLayer renderLayer(window);
    City::LSystemGenerator lSystem;
    lSystem.setAxiom("F");
    //lSystem.addRule({"F", "F[+F]F[-F]F", 1.0f});
    lSystem.addRule({"F", "F[+F][-F][++F][--F]F", 0.3f});  // More branching
    lSystem.addRule({"F", "FF[+F][-F]F", 0.3f});  // Longer segments
    lSystem.addRule({"F", "F[+F]F[-F]F", 0.4f});  // Original rule
    lSystem.setDepth(4);


    while (window.isOpen()) {
        // Process events, including window close
        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto *resized = event->getIf<sf::Event::Resized>()) {
                // Update the view to the new size of the window
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
            }
        }
        sf::Time deltaTime = deltaClock.restart();
        ImGui::SFML::Update(window, deltaTime);

        //handle  render stuff, split to a side window
        window.clear(sf::Color::White);

        sf::View cityView = window.getDefaultView();
        cityView.setViewport(sf::FloatRect{{0.2f, 0.0f}, {0.8f, 1.0f}});
        window.setView(cityView);
        // Put render code here

        renderLayer.renderRoads();

        //split controls back to the left of screen
        window.setView(window.getDefaultView());
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize({window.getSize().x * 0.2f, windowHeight * 0.2}, ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.5f);
        ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Controls");
        if (ImGui::Button("Test")) {
            //test lsystem
            roadGraph.reset();

            lSystem.generate();
            std::cout << "Generated L-System: " << lSystem.getGeneratedString() << std::endl;
            //create a road graph
            City::TurtleBuilder turtle(lSystem, roadGraph);
            turtle.createGraph();
            //print the graph
            std::cout << "Generated Road Graph:" << std::endl;
            for (const auto &vertex: roadGraph.getVertices()) {
                std::cout << "Vertex ID: " << vertex.id << ", Position: (" << vertex.x << ", " << vertex.y << ")" << std::endl;
            }
            renderLayer.buildRoadMesh(roadGraph);
            renderLayer.renderRoads();
        }
        ImVec2 settingsPos = ImGui::GetWindowSize();


        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(0, settingsPos.y), ImGuiCond_Always);
        ImGui::SetNextWindowSize({window.getSize().x * 0.2f, windowHeight * 0.1}, ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.5f);
        //ImGui::SetNextWindowSize(ImVec2(200, 100));
        ImGui::Begin("Simulation Data", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Frame Rate: %.1f FPS", 1.0f / ImGui::GetIO().DeltaTime);
        ImGui::End();


        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
