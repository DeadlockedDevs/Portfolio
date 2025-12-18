#ifndef PLANT_H
#define PLANT_H

#include "organism.h"
#include <vector>
class World;

// Plant class inherits from organism
class plant : public organism {
public:
    plant(); // Constructor

    // Returns the symbol for display purposes
    std::string Symbol() const override;

    // Plant reproduction logic
    void Reproduce(World& world, std::vector<organism*>& vec) override;

    // Daily update: grow, reproduce, etc.
    void update(World& world, std::vector<organism*>& vec) override;

private:
    std::string symbol; // Display symbol for the plant
    int reproduce;      // Tracks reproduction counter or cooldown
};

#endif
