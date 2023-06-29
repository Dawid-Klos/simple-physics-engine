//
// Created by dave on 17.04.23.
//
#include <iostream>
#include "engine/collision_detector.h"

using namespace engine;

void CollisionDetector::addObject(GameObject* gameObject) {
    gameObjects.push_back(gameObject);
}

void CollisionDetector::createIntervals() {
    // Prepare intervals vector
    intervals.clear();
    intervals.resize(gameObjects.size() * 2);

    // Define bounding volumes and create intervals
    for (int i = 0; i < gameObjects.size(); i++) {
        Interval intervalX{};
        intervalX.objectIndex = i;
        intervalX.min = gameObjects[i]->getBoundingBox().xMin;
        intervalX.max = gameObjects[i]->getBoundingBox().xMax;
        intervals[0].push_back(intervalX);

        Interval intervalY{};
        intervalY.objectIndex = i;
        intervalY.min = gameObjects[i]->getBoundingBox().yMin;
        intervalY.max = gameObjects[i]->getBoundingBox().yMax;
        intervals[1].push_back(intervalY);
    }
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
    for (int i = 0; i < gameObjects.size(); i++) {
        intervals[0][i].min = gameObjects[i]->getBoundingBox().xMin * 0.95f;
        intervals[0][i].max = gameObjects[i]->getBoundingBox().xMax * 0.95f;
        intervals[1][i].min = gameObjects[i]->getBoundingBox().yMin * 0.95f;
        intervals[1][i].max = gameObjects[i]->getBoundingBox().yMax * 0.95f;
    }

    // Step 4: Check for overlaps along all axes
    unordered_map<int, vector<int>> overlappingPairsMap(intervals.size());

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < intervals[i].size(); j++) {
            Interval& interval = intervals[i][j];
            for (int k = j + 1; k < intervals[i].size(); k++) {
                Interval& other = intervals[i][k];

                if (interval.max < other.min) {
                    break; // intervals sorted, no more overlaps possible
                }

                // Skip collision detection between stationary objects
                if ((gameObjects[interval.objectIndex]->objectType == WALL &&
                     gameObjects[other.objectIndex]->objectType == WALL) ||
                    (gameObjects[interval.objectIndex]->objectType == WALL &&
                     gameObjects[other.objectIndex]->objectType == FLOOR) ||
                    (gameObjects[interval.objectIndex]->objectType == FLOOR &&
                     gameObjects[other.objectIndex]->objectType == WALL) ||
                    (gameObjects[interval.objectIndex]->objectType == FLOOR &&
                     gameObjects[other.objectIndex]->objectType == FLOOR)
                        )
                {
                    continue;
                }

                if (objectsCollides(gameObjects[interval.objectIndex], gameObjects[other.objectIndex])) {
                    overlappingPairsMap[interval.objectIndex].push_back(other.objectIndex);
                    overlappingPairsMap[other.objectIndex].push_back(interval.objectIndex);
                }
            }
        }
    }

    sf::Color collisionColor = sf::Color::Red;
    // Step 5: Do more precise collision detection for overlapping pairs
    for (int i = 0; i < gameObjects.size(); i++) {
        for (int pair : overlappingPairsMap[i]) {
            // Do narrow phase collision detection between game objects
            if (objectsCollides(gameObjects[i], gameObjects[pair])) {
                gameObjects[i]->changeColor(collisionColor);
                gameObjects[pair]->changeColor(collisionColor);

                collisionResolver.addCollision(gameObjects[i], gameObjects[pair]);
            }
        }
    }
}

bool CollisionDetector::objectsCollides(GameObject *collider, GameObject *otherCollider) {
    // Use bounding boxes to determine narrow collision detection
    if (collider->getBoundingBox().xMin < otherCollider->getBoundingBox().xMax &&
        collider->getBoundingBox().xMax > otherCollider->getBoundingBox().xMin &&
        collider->getBoundingBox().yMin < otherCollider->getBoundingBox().yMax &&
        collider->getBoundingBox().yMax > otherCollider->getBoundingBox().yMin) {
        return true;
    }
    return false;
}

