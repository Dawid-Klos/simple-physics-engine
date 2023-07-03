#include "game_demo/world.h"
#include "game_demo/simulation_renderer.h"

#define WINDOW_WIDTH 1920.0f
#define WINDOW_HEIGHT 1080.0f

using namespace engine;

int main() {
    auto* renderer = new SimulationRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);

    World world(*renderer);
    world.createSpringSystem(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT);
    world.setScreenBoundaries(WINDOW_WIDTH, WINDOW_HEIGHT);

    sf::Clock ballsTimer = sf::Clock();

    while (renderer->running()) {

        // Create a new ball every 1 seconds
        if (ballsTimer.getElapsedTime().asSeconds() > 0.25f) {
            ballsTimer.restart();
            world.createBall();
        }

        world.update();
    }

    return 0;
}
