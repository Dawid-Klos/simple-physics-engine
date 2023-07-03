//
// Created by dave on 17.04.23.
//
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

    // Step 3: Check for overlaps along all axes
    unordered_map<int, vector<int>> overlappingPairsMap(intervals.size());

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < intervals[i].size(); j++) {
            Interval& interval = intervals[i][j];
            for (int k = j + 1; k < intervals[i].size(); k++) {
                Interval& other = intervals[i][k];

                if (interval.max < other.min) {
                    // if this point is reached - intervals sorted, no more overlaps possible
                    break;
                }

                // Skip collision detection between stationary objects
                if ((gameObjects[interval.objectIndex]->objectType == WALL || gameObjects[interval.objectIndex]->objectType == FLOOR) &&
                    (gameObjects[other.objectIndex]->objectType == WALL || gameObjects[other.objectIndex]->objectType == FLOOR))
                {
                    continue;
                }

                // Add overlapping pairs to map
                overlappingPairsMap[interval.objectIndex].push_back(other.objectIndex);
                overlappingPairsMap[other.objectIndex].push_back(interval.objectIndex);
            }
        }
    }

    sf::Color collisionColor = sf::Color::Red;

    // Step 4: Do more precise collision detection for overlapping pairs
    for (int i = 0; i < gameObjects.size(); i++) {
        for (int pair : overlappingPairsMap[i]) {
            // Do narrow phase collision detection between game objects
            if (objectsCollides(gameObjects[i], gameObjects[pair])) {
                gameObjects[i]->indicateCollision(collisionColor);
                gameObjects[pair]->indicateCollision(collisionColor);

                collisionResolver.addCollision(gameObjects[i], gameObjects[pair]);
            }
        }
    }
}

bool CollisionDetector::objectsCollides(GameObject *collider, GameObject *otherCollider) {
    BoundingBox colliderBox = collider->getBoundingBox();
    BoundingBox otherColliderBox = otherCollider->getBoundingBox();

    // Use bounding boxes to determine narrow collision detection
    if(colliderBox.xMin < otherColliderBox.xMax &&
       colliderBox.xMax > otherColliderBox.xMin &&
       colliderBox.yMin < otherColliderBox.yMax &&
       colliderBox.yMax > otherColliderBox.yMin) {
        return true;
    }

    return false;
}