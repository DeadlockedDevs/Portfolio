#include "animal.h"
#include "World.h"
#include <cstdlib> // for rand()
#include <cmath>   // for abs()

// Constructor: initialize default values
animal::animal(){
    setStarve(0);      // start with no hunger
    setRepFrame(0);     // start ready to reproduce immediately
    setRadius(5);       // default sensing/movement radius
}

// Find the closest organism of a given type within the radius
organism* animal::closestType(World& world, const std::string& type){
    int r = getRow();
    int c = getCol();
    int bestDist = 2147483647; // initialize with a very large number
    organism* closest = nullptr;

    // Scan a square around the animal based on radius
    for(int dummyR = -getRadius(); dummyR <= getRadius(); ++dummyR){
        for(int dummyC = -getRadius(); dummyC <= getRadius(); ++dummyC) {
            if (dummyR == 0 && dummyC == 0) continue; // skip self
            int newR = r + dummyR;
            int newC = c + dummyC;

            if(!world.isInBounds(newR, newC)) continue;

            organism* org = world.getAt(newR, newC);
            if(org && org->getName() == type) {
                int dist = abs(dummyR) + abs(dummyC); // Manhattan distance
                if(dist < bestDist){
                    bestDist = dist;
                    closest = org;
                }
            }
        }
    }

    return closest;
}

// Helper wrappers for specific organism types
organism* animal::hasPrey(World& world) { return closestType(world, "Prey"); }
organism* animal::hasPredator(World& world) { return closestType(world, "Predator"); }
organism* animal::hasPlant(World& world) { return closestType(world, "Plant"); }

// Generate move vector towards a target organism
std::pair<int, int> animal::moveTowards(World& world, const std::string& type){
    organism* target = closestType(world, type);
    if(!target) return {0,0}; // no target, don't move

    std::pair<int,int> currLoc = {getRow(), getCol()};
    std::pair<int,int> otherLoc = {target->getRow(), target->getCol()};
    int rowDiff = currLoc.first - otherLoc.first;
    int colDiff = currLoc.second - otherLoc.second;
    std::pair<int,int> moveTo{0,0};

    // Decide direction based on relative position
    if(rowDiff < 0 && colDiff < 0) moveTo = {1,1};
    else if(rowDiff < 0 && colDiff > 0) moveTo = {1,-1};
    else if(rowDiff > 0 && colDiff < 0) moveTo = {-1,1};
    else if(rowDiff > 0 && colDiff > 0) moveTo = {-1,-1};
    else if(rowDiff < 0 && colDiff == 0) moveTo = {1,0};
    else if(rowDiff > 0 && colDiff == 0) moveTo = {-1,0};
    else if(rowDiff == 0 && colDiff < 0) moveTo = {0,1};
    else if(rowDiff == 0 && colDiff > 0) moveTo = {0,-1};

    return moveTo;
}

// Generate move vector away from a target organism
std::pair<int,int> animal::moveAway(World& world, const std::string& type){
    organism* target = closestType(world, type);
    if(!target) return {0,0}; // no target, don't move

    std::pair<int,int> currLoc = {getRow(), getCol()};
    std::pair<int,int> otherLoc = {target->getRow(), target->getCol()};
    int rowDiff = currLoc.first - otherLoc.first;
    int colDiff = currLoc.second - otherLoc.second;
    std::pair<int,int> moveTo{0,0};

    // Decide direction based on relative position
    if(rowDiff < 0 && colDiff < 0) moveTo = {-1,-1};
    else if(rowDiff < 0 && colDiff > 0) moveTo = {-1,1};
    else if(rowDiff > 0 && colDiff < 0) moveTo = {1,-1};
    else if(rowDiff > 0 && colDiff > 0) moveTo = {1,1};
    else if(rowDiff < 0 && colDiff == 0) moveTo = {-1,0};
    else if(rowDiff > 0 && colDiff == 0) moveTo = {1,0};
    else if(rowDiff == 0 && colDiff < 0) moveTo = {0,-1};
    else if(rowDiff == 0 && colDiff > 0) moveTo = {0,1};

    // Safeguard: don't move outside world bounds
    if(currLoc.first + moveTo.first < 0 || currLoc.first + moveTo.first >= 20) return {0,0};
    if(currLoc.second + moveTo.second < 0 || currLoc.second + moveTo.second >= 20) return {0,0};

    return moveTo;
}

// Generate random movement vector (-1,0,1) in both directions
std::pair<int,int> animal::randomMovement(){
    return {rand()%3 - 1, rand()%3 - 1};
}
