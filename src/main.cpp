#include <iostream>
#include <memory>
using namespace std;

#include "Player.h"
#include "Scene.h"
#include "Objects.h"
#include "Renderer.h"

void setupScene(Scene& scene) {
    scene.objs.push_back(std::make_shared<Objs::Circle>(100, Vector2f(500, 250), Color::Red));
    scene.objs.push_back(std::make_shared<Objs::Circle>(100, Vector2f(500, 500), Color::Blue));
    scene.objs.push_back(std::make_shared<Objs::Rect>(Vector2f(201, 100), Vector2f(200, 500)));
    scene.objs.push_back(std::make_shared<Objs::Rect>(Vector2f(100, 201), Vector2f(500, 500)));
}

int main() {
    // Create the window
    RenderWindow window(VideoMode(1200, 675), "Raymarcher", Style::Close | Style::Titlebar);
    // window.setFramerateLimit(240);
    window.setVerticalSyncEnabled(true);

    // Create the player object
    Player player(Vector2f(100, 100));
    // The renderer object
    Renderer renderer(90, 675);
    // The scene object
    Scene scene;
    // Add everything to the scene
    setupScene(scene);

    // For calculating the delta time
    Clock clock;
    float lastTime = clock.getElapsedTime().asSeconds();

    // Main loop
    while(window.isOpen()) {
        Event ev;
        while(window.pollEvent(ev)) {
            if(ev.type == Event::Closed)
                window.close();
        }
        // Delta time stuff
        float deltaTime = (clock.getElapsedTime().asSeconds() - lastTime) * 100.f;
        lastTime = clock.getElapsedTime().asSeconds();
        if(!window.hasFocus()) continue;

        // Update the player
        player.Update(deltaTime);
        renderer.Update(scene, player);

        // And draw everything to the window
        window.clear(Color::Black);
        renderer.draw(window, scene);
        // window.draw(player);
        // window.draw(scene);
        window.display();
    }
}