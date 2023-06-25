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
    intervals.resize(2);

    // Define bounding volumes and create intervals
    for (int i = 0; i < gameObjects.size(); i++) {
        GameObject* gameObject = gameObjects[i];

        Interval intervalX{};
        intervalX.objectIndex = i;
        intervalX.min = gameObject->getBoundingBox().xMin;
        intervalX.max = gameObject->getBoundingBox().xMax;
        intervals[0].push_back(intervalX);

        Interval intervalY{};
        intervalY.objectIndex = i;
        intervalY.min = gameObject->getBoundingBox().yMin;
        intervalY.max = gameObject->getBoundingBox().yMax;
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
        GameObject* gameObject = gameObjects[i];
        intervals[0][i].min = gameObject->getBoundingBox().xMin * 0.85f;
        intervals[0][i].max = gameObject->getBoundingBox().xMax * 0.85f;
        intervals[1][i].min = gameObject->getBoundingBox().yMin * 0.85f;
        intervals[1][i].max = gameObject->getBoundingBox().yMax * 0.85f;
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

                overlappingPairsMap[interval.objectIndex].push_back(other.objectIndex);
                overlappingPairsMap[other.objectIndex].push_back(interval.objectIndex);
            }
        }
    }

    // Do more precise collision detection for overlapping pairs
    for (int i = 0; i < gameObjects.size(); i++) {
        for (int pair : overlappingPairsMap[i]) {
            // Do narrow phase collision detection between balls i and other
            if (gameObjects[i]->collideWith(gameObjects[pair])) {
                collisionResolver.addCollision(gameObjects[i], gameObjects[pair]);
            }
        }
    }

    collisionResolver.resolve();
}
