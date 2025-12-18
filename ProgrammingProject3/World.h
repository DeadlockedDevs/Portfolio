#ifndef WORLD_H
#define WORLD_H

// Compile commands:
// g++ -o run.exe main.cpp organismImp.cpp plantImp.cpp animalImp.cpp preyImp.cpp predatorImp.cpp WorldImp.cpp
// g++ -g -o run.exe main.cpp organismImp.cpp plantImp.cpp animalImp.cpp preyImp.cpp predatorImp.cpp WorldImp.cpp

#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include "organism.h"

// Grid dimensions
const int ROWS = 20;
const int COLS = 20;

class World {
public:
    World();  // Constructor: initialize world grid and any other variables
    ~World(); // Destructor: clean up dynamically allocated organisms

    // Randomly sprout plants in empty grid cells
    void randomPlantSprout(std::vector<organism*>& vec);

    // Update all organisms in the world (movement, reproduction, death)
    void update();

    // Display the current state of the grid
    void display();

    // Check if a grid cell is empty
    bool isEmpty(int row, int col) const;

    // Add an organism to the world at specified location
    void addOrganism(organism* org, int row, int col);

    // Remove an organism immediately (delete memory and remove from vector)
    void removeOrganism(int row, int col, std::vector<organism*>& vec);

    // Check if given row and column are within grid bounds
    bool isInBounds(int row, int col) const;

    // Get a pointer to the organism at a given location
    organism* getAt(int row, int col) const;

    // Find an empty cell adjacent to a given location (-1,-1 if none)
    std::pair<int,int> findEmptyAdjacent(int row, int col) const;

    // Move an organism to a new location (updates grid coordinates)
    void moveOrganism(organism* org, int newRow, int newCol);

    // Randomly generate organisms on the grid based on provided probabilities
    void randomGenerate(double plantChance, double preyChance, double predatorChance);

private:
    // 2D grid storing pointers to organisms (nullptr if empty)
    std::vector<std::vector<organism*>> grid;

    // Track the number of days that have passed in the simulation
    int days;
};

#endif
