#include <iostream>
#include "game_demo/world.h"
#include "game_demo/simulation_renderer.h"

#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT 600.0f

using namespace engine;

int main() {
//    auto* renderer = new SimulationRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
//
//    World world(*renderer);
//    world.createSpringSystem(WINDOW_HEIGHT);
//
//    sf::Clock ballsTimer = sf::Clock();
//
//    while (renderer->running()) {
//
//        // Create a new ball every 1 seconds
//        if (ballsTimer.getElapsedTime().asSeconds() > 0.15f) {
//            ballsTimer.restart();
//            world.createBall();
//        }
//
//        // Update particle position
//        world.update();
//    }

    Vector myV = Vector(3, 4);
    myV.normalize();
    std::cout << myV.x << " " << myV.y << std::endl;

    engine::real myReal = 0.6;
    engine::real myReal2 = 0.8;

    // compare myV with myReal and myReal2
    if (myV.x == myReal && myV.y == myReal2) {
        std::cout << "Test passed" << std::endl;
    } else {
        std::cout << "Test failed" << std::endl;
    }

    return 0;
}
