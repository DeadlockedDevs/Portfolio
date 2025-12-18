#ifndef ANIMAL_H
#define ANIMAL_H

#include "organism.h"
#include <utility>
#include <string>
#include <vector>
class World;

using std::pair;
using std::string;

// Base class for all moving organisms (animals)
class animal : public organism {
public:
    animal();
    virtual ~animal() {} // virtual destructor for proper cleanup in derived classes

    // Pure virtual function: every animal must implement its own movement
    virtual void Movement(World& world, std::vector<organism*>& vec) = 0;

    // Reproduction frame management
    void setRepFrame(int r) { repFrame = r; }
    int getRepFrame() const { return repFrame; }

    // Hunger/starvation management
    void setStarve(int s) { starve = s; }
    int getStarve() const { return starve; }

    // Sensing/movement radius
    void setRadius(int r) { radius = r; }
    int getRadius() const { return radius; }

    // Movement helper functions
    pair<int,int> moveTowards(World& world, const string& type); // move towards nearest type
    pair<int,int> moveAway(World& world, const string& type);    // move away from nearest type
    pair<int,int> randomMovement();                               // random move if no target
    organism* closestType(World& world, const string& type);      // find closest organism of a type

    // Detection helpers
    organism* hasPrey(World& world);       // check for nearby prey
    organism* hasPredator(World& world);   // check for nearby predator
    organism* hasPlant(World& world);      // check for nearby plant

protected:
    int repFrame;   // countdown until reproduction possible
    int starve;     // countdown until death by starvation
    int radius;     // detection/movement radius
};

#endif
