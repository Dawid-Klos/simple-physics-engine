//
// Created by dave on 17.04.23.
//
#include <iostream>
#include "engine/collision_detector.h"
#include "game_demo/ball.h"


using namespace engine;

void CollisionDetector::addBall(Ball* ball) {
    balls.push_back(ball);
}

void CollisionDetector::updateBoundingBoxes() {
    for (auto* ball : balls) {
        ball->updateBoundingBox();
    }
}

bool CollisionDetector::ballsOverlap(Ball &ball1, Ball &ball2)  {
    real radiusSum = ball1.getRadius() + ball2.getRadius();
    Vector distance = ball2.getParticle()->getPosition() - ball1.getParticle()->getPosition();
    real distanceMagnitude = distance.getMagnitude();

    // add small threshold to radius sum to reduce false collisions
    return distanceMagnitude < radiusSum;
}

void CollisionDetector::detectCollisions() {

    // Step 1: Create intervals for each ball
    createIntervals();

    // Step 2: Sort intervals along each axis
    for (int i = 0; i < 2; i++) {
        std::sort(intervals[i].begin(), intervals[i].end(),
                  [](const Interval& a, const Interval& b) {
                      return a.min < b.min;
                  });
    }

    // Step 3: Update sorted lists each frame
    for (int i = 0; i < balls.size(); i++) {
        Ball* ball = balls[i];
        intervals[0][i].min = ball->getBoundingBox().xMin;
        intervals[0][i].max = ball->getBoundingBox().xMax;
        intervals[1][i].min = ball->getBoundingBox().yMin;
        intervals[1][i].max = ball->getBoundingBox().yMax;
    }

    // Step 4: Check for overlaps along all axes
    unordered_map<int, vector<int>> overlappingPairsMap(balls.size());

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < intervals[i].size(); j++) {
            Interval& interval = intervals[i][j];
            for (int k = j + 1; k < intervals[i].size(); k++) {
                Interval& other = intervals[i][k];

                if (interval.max < other.min) {
                    break; // intervals sorted, no more overlaps possible
                }

                overlappingPairsMap[interval.objectIndex].push_back(other.objectIndex);
                overlappingPairsMap[other.objectIndex].push_back(interval.objectIndex);
            }
        }
    }

    // Do more precise collision detection for overlapping pairs
    for (int i = 0; i < balls.size(); i++) {
        for (int pair : overlappingPairsMap[i]) {
            // Do narrow phase collision detection between balls i and other
            if (ballsOverlap(*balls[i], *balls[pair])) {
                balls[i]->changeColor(sf::Color(255, 0, 0));
                balls[pair]->changeColor(sf::Color(255, 0, 0));
                collisionResolver.addCollision(balls[i]->getParticle(), balls[pair]->getParticle());
            }
        }
    }
}

void CollisionDetector::createIntervals() {
    // update bounding boxes of all balls
    updateBoundingBoxes();

    // Prepare intervals vector
    intervals.clear();
    intervals.resize(2);

    // Define bounding volumes and create intervals
    for (int i = 0; i < balls.size(); i++) {
        Ball* currentBall = balls[i];

        Interval intervalX{};
        intervalX.objectIndex = i;
        intervalX.min = currentBall->getBoundingBox().xMin;
        intervalX.max = currentBall->getBoundingBox().xMax;
        intervals[0].push_back(intervalX);

        Interval intervalY{};
        intervalY.objectIndex = i;
        intervalY.min = currentBall->getBoundingBox().yMin;
        intervalY.max = currentBall->getBoundingBox().yMax;
        intervals[1].push_back(intervalY);
    }
}
