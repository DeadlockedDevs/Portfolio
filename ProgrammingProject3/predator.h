#ifndef PREDATOR_H
#define PREDATOR_H

#include "animal.h"
#include <vector>
class World;

// Predator class inherits from animal
class predator : public animal {
public:
    predator(); // Constructor

    // Predator-specific movement logic
    void Movement(World& world, std::vector<organism*>& vec) override;

    // Daily update: age, starvation, reproduction, movement
    void update(World& world, std::vector<organism*>& vec) override;

    // Reproduction logic for predator
    void Reproduce(World& world, std::vector<organism*>& vec) override;

    // Symbol used for display in the world grid
    std::string Symbol() const override;
};

#endif