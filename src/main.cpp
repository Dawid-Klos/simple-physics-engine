#include <iostream>
#include "game_demo/world.h"

#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT 600.0f

using namespace engine;

int main() {
    auto* renderer = new SimulationRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);

    World world(*renderer);
    world.createSpringSystem(WINDOW_HEIGHT);

    sf::Clock ballsTimer = sf::Clock();

    while (renderer->running()) {

        // Create a new ball every 1 seconds
        if (ballsTimer.getElapsedTime().asSeconds() > 0.15f) {
            ballsTimer.restart();
            world.createBall();
        }

        // Update particle position
        world.update();
    }
    return 0;
}
