#include "plant.h"
#include "World.h"
#include <iostream>

// Constructor
plant::plant() {
    setName("Plant");        // Set organism type
    setLifeSpan(100);        // Plants live 100 days
    symbol = "🌱";           // Symbol for display
    reproduce = 2;           // Reproduce every 2 days
}

// Daily update function
void plant::update(World& world, std::vector<organism*>& vec){
    if(getHasMoved()) return;          // Skip if already updated this day

    setAge(getAge() + 1);              // Age the plant

    // Remove if plant has reached lifespan
    if(getAge() >= getLifeSpan()){
        world.removeOrganism(getRow(), getCol(), vec);
        return;
    }

    Reproduce(world, vec);             // Try to reproduce
    setHasMoved(true);                 // Mark as updated for today
}

// Symbol used for display in the grid
std::string plant::Symbol() const { 
    return "🌱"; 
}

// Plant reproduction logic
void plant::Reproduce(World& world, std::vector<organism*>& vec){
    // Only reproduce at intervals defined by 'reproduce'
    if(getAge() % reproduce != 0) return;

    int r = getRow();
    int c = getCol();

    // Find an empty adjacent cell
    std::pair<int,int> target = world.findEmptyAdjacent(r, c);
    if(target.first == -1) return;     // No empty spots, skip reproduction

    // Create new plant in empty spot
    plant* baby = new plant();
    world.addOrganism(baby, target.first, target.second);
}
