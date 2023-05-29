#include "game_demo/world.h"

#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT 600.0f

using namespace engine;

int main() {
    auto* renderer = new SimulationRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);

    World world(*renderer);
    world.createSpringSystem(WINDOW_HEIGHT);

    while (renderer->running()) {
        world.createBalls();

        // Update particle position
        world.update();
    }
    return 0;
}
