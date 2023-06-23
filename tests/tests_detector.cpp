//
// Created by dave on 23.06.23.
//

#include <gtest/gtest.h>

// define TEST_FRIENDS to access private members of Collision detector class
#define TEST_FRIENDS \
    friend class DetectorTests_ZeroObjects_Test; \
    friend class DetectorTests_OneObject_Test;   \
    friend class DetectorTests_MultipleObjects_Test; \
    friend class DetectorTests_ResolverEmptyVector_Test;

#include <engine/collision_detector.h>
#include "../src/collision_detector.cpp"
#include "../src/collision_resolver.cpp"
#include "../src/game_demo/ball.cpp"

namespace engine {
    CollisionDetector initDetector() {
        CollisionResolver collisionResolver;
        return CollisionDetector(collisionResolver);
    }

    struct CollisionDetectionSystem {
        CollisionResolver collisionResolver;
        CollisionDetector detector = CollisionDetector(collisionResolver);
    };

    TEST(DetectorTests, ZeroObjects) {
        CollisionDetector collisionDetector = initDetector();

        collisionDetector.detectCollisions();
        EXPECT_EQ(collisionDetector.balls.size(), 0);
    }

    TEST(DetectorTests, OneObject) {
        CollisionDetector collisionDetector = initDetector();
        Ball* ball = new Ball(10, 0, 0);
        collisionDetector.addBall(ball);

        collisionDetector.detectCollisions();
        EXPECT_EQ(collisionDetector.balls.size(), 1);
    }

    TEST(DetectorTests, MultipleObjects) {
        CollisionDetectionSystem collisionDetector;

        // create multiple balls
        for (int i = 0; i < 10; i++) {
            Ball* ball = new Ball(10, real(i+1), real(i+2));
            collisionDetector.detector.addBall(ball);
        }

        collisionDetector.detector.detectCollisions();
        EXPECT_EQ(collisionDetector.detector.balls.size(), 10);
    }
}







