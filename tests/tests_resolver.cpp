//
// Created by dave on 23.06.23.
//

#include <gtest/gtest.h>

// define TEST_FRIENDS to access private members of Collision detector class
#define TEST_FRIENDS \
    friend class ResolverTests_EmptyVectorAfterResolving_Test; \
    friend class ResolverTests_AbortResolveIfOneObject_Test;

#include <engine/collision_detector.h>

namespace engine {
    struct CollisionDetectionSystem {
        CollisionResolver collisionResolver;
        CollisionDetector detector = CollisionDetector(collisionResolver);
    };

    TEST(ResolverTests, EmptyVectorAfterResolving) {
        CollisionDetectionSystem collisionDetector;

        // create multiple balls
        for (int i = 0; i < 10; i++) {
            GameObject* ball = new Ball(10, real(i+1), real(i+2));
            collisionDetector.detector.addObject(ball);
        }

        collisionDetector.detector.detectCollisions();
        collisionDetector.collisionResolver.resolve();
        EXPECT_EQ(collisionDetector.collisionResolver.collisions.size(), 0);
    }

    TEST(ResolverTests, AbortResolveIfOneObject) {
        CollisionDetectionSystem collisionDetector;

        // create multiple balls
        for (int i = 0; i < 2; i++) {
            GameObject* ball = new Ball(10, real(i+1), real(i+2));
            collisionDetector.detector.addObject(ball);
        }

        collisionDetector.detector.detectCollisions();
        collisionDetector.collisionResolver.resolve();
        EXPECT_EQ(collisionDetector.collisionResolver.collisions.size(), 0);
    }
}
