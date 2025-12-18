#ifndef PREY_H
#define PREY_H

#include "animal.h"
#include <vector>
class World;

// Prey class inherits from animal
class prey : public animal {
public:
    prey(); // Constructor

    // Prey-specific movement logic
    void Movement(World& world, std::vector<organism*>& vec) override;

    // Daily update: age, starvation, reproduction, movement
    void update(World& world, std::vector<organism*>& vec) override;

    // Reproduction logic for prey
    void Reproduce(World& world, std::vector<organism*>& vec) override;

    // Symbol used for display in the world grid
    std::string Symbol() const override;
};

#endif
