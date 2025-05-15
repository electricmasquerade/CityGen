#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

int main() {
    // Create the main window
    constexpr unsigned windowWidth = 1000;
    constexpr unsigned windowHeight = windowWidth * 0.8;
    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Maze Algorithms");
    window.setFramerateLimit(120);
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

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

        //handle maze render stuff, split to side window
        window.clear(sf::Color::White);

        sf::View mazeView = window.getDefaultView();
        mazeView.setViewport(sf::FloatRect{{0.2f, 0.0f}, {0.8f, 1.0f}});
        window.setView(mazeView);


        //split controls back to the left of screen
        window.setView(window.getDefaultView());

        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
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
