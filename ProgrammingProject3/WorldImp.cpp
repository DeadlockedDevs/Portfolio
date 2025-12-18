#include "World.h"
#include "organism.h"
#include "plant.h"
#include "prey.h"
#include "predator.h"
#include <fstream>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm> // needed for std::remove
using namespace std;

// Constructor: initialize the grid and day counter
World::World() : days(0) {
    grid.resize(ROWS, vector<organism*>(COLS, nullptr));
    //cout << "[DEBUG] World created.\n";
}

// Destructor: delete all organisms in the grid to free memory
World::~World() {
    //cout << "[DEBUG] World destroyed. Cleaning up organisms.\n";
    for(int i = 0; i < ROWS; ++i){
        for(int j = 0; j < COLS; ++j){
            if(grid[i][j] != nullptr){
                //cout << "[DEBUG] Deleting organism at (" << i << "," << j << ") type=" << grid[i][j]->getName() << "\n";
            }
            delete grid[i][j]; // delete dynamically allocated organism
        }
    }
}

// Update all organisms in the world
void World::update() {
    vector<organism*> organisms;

    // Step 1: Collect all organisms at start of day
    for(int i = 0; i < ROWS; ++i){
        for(int j = 0; j < COLS; ++j){
            if(grid[i][j] != nullptr){
                organisms.push_back(grid[i][j]);
                //grid[i][j]->setHasMoved(true);
            }
        }
    }

    // Step 2: Update all collected organisms safely
    for(size_t i = 0; i < organisms.size(); ++i){
        organism* org = organisms[i];

        // Skip if organism already deleted or moved
        if(org == nullptr) continue;
        if(grid[org->getRow()][org->getCol()] != org) continue;

        // Pass reference to update vector for safe removal
        org->update(*this, organisms);
    }

    // Randomly sprout plants after organism updates
    randomPlantSprout(organisms);

    // Step 3: Reset hasMoved flags for all alive organisms
    for(int i = 0; i < ROWS; ++i){
        for(int j = 0; j < COLS; ++j){
            if(grid[i][j] != nullptr){
                grid[i][j]->setHasMoved(false);
            }
        }
    }
}

// Display the current state of the world grid
void World::display() {
    ofstream outfile("world_state.txt", ios::app);
    days++;
    //cout << "[DEBUG] Displaying world for Day " << days << "\n";
    outfile << "Day " << days << ":\n";

    for(int i = 0; i < ROWS; ++i){
        for(int j = 0; j < COLS; ++j){
            if(grid[i][j] == nullptr) outfile << "🟩"; // empty cell
            else {
                outfile << grid[i][j]->Symbol();
                //cout << "[DEBUG] Cell (" << i << "," << j << ") contains " << grid[i][j]->getName() << "\n";
            }
        }
        outfile << "\n";
    }
    outfile << "\n";
    outfile.close();
}

// Check if a cell is empty
bool World::isEmpty(int row, int col) const {
    return isInBounds(row, col) && grid[row][col] == nullptr;
}

// Add an organism to a specific location in the grid
void World::addOrganism(organism* org, int row, int col){
    if(isInBounds(row, col) && isEmpty(row, col)){
        grid[row][col] = org;
        org->setPosition(row, col);
        //cout << "[DEBUG] Added organism " << org->getName() << " at (" << row << "," << col << ")\n";
    }
}

// Remove organism immediately (safe delete + vector removal)
void World::removeOrganism(int row, int col, vector<organism*>& vec){
    if(isInBounds(row, col) && grid[row][col] != nullptr){
        organism* org = grid[row][col];
        grid[row][col] = nullptr;

        // Remove from vector first
        vec.erase(remove(vec.begin(), vec.end(), org), vec.end());

        // Delete organism
        delete org;
        //cout << "[DEBUG] Removed organism at (" << row << "," << col << ")\n";
    }
}

// Check if a row and column are within grid bounds
bool World::isInBounds(int row, int col) const {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

// Get pointer to organism at given location
organism* World::getAt(int row, int col) const {
    if(!isInBounds(row, col)) return nullptr;
    return grid[row][col];
}

// Find an empty cell adjacent to given row/col (-1,-1 if none)
pair<int,int> World::findEmptyAdjacent(int row, int col) const{
    vector<pair<int,int>> emptySpots;
    int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    for(auto& d : directions){
        int nr = row + d[0];
        int nc = col + d[1];
        if(isEmpty(nr, nc)){
            emptySpots.push_back({nr, nc});
        }
    }
    if(emptySpots.empty()) return {-1,-1};
    int index = rand() % emptySpots.size();
    //cout << "[DEBUG] Found empty adjacent spot at (" << emptySpots[index].first << "," << emptySpots[index].second << ")\n";
    return emptySpots[index];
}

// Move organism to a new location
void World::moveOrganism(organism* org, int newRow, int newCol){
    if(!isInBounds(newRow, newCol)) return;
    int oldRow = org->getRow();
    int oldCol = org->getCol();

    // Only move if organism is still at old position
    if(grid[oldRow][oldCol] != org) {
        //cout << "[DEBUG] Move skipped for " << org->getName() 
            // << " because it is no longer at (" << oldRow << "," << oldCol << ")\n";
        return;
    }

    // Debug message
    //cout << "[DEBUG] Moving " << org->getName() << " from (" 
        // << oldRow << "," << oldCol << ") to (" << newRow << "," << newCol << ")\n";

    // Move in the grid
    grid[oldRow][oldCol] = nullptr;
    grid[newRow][newCol] = org;

    // Update organism’s internal position
    org->setPosition(newRow, newCol);
}

// Randomly sprout a plant with 10% chance
void World::randomPlantSprout(std::vector<organism*>& vec) {
    int chance = rand() % 100;
    if (chance >= 10) return;

    int attempts = 50; // try 50 times to find empty spot
    while (attempts-- > 0) {
        int r = rand() % ROWS;
        int c = rand() % COLS;
        if (isEmpty(r, c)) {
            plant* baby = new plant();
            addOrganism(baby, r, c);
            //cout << "[DEBUG] Plant randomly sprouted at (" << r << "," << c << ")\n";
            break;
        }
    }
}

// Randomly generate organisms on the grid with given probabilities
#include <cstdlib>
#include <ctime>

void World::randomGenerate(double plantChance, double preyChance, double predatorChance) {
    // initialize RNG
    srand(time(0));

    // clear the world first
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] != nullptr) {
                delete grid[i][j];
                grid[i][j] = nullptr;
            }
        }
    }

    // generate organisms on grid
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            double roll = (rand() % 10000) / 10000.0; // random 0–1

            if (roll < plantChance) {
                addOrganism(new plant(), i, j);
            }
            else if (roll < plantChance + preyChance) {
                addOrganism(new prey(), i, j);
            }
            else if (roll < plantChance + preyChance + predatorChance) {
                addOrganism(new predator(), i, j);
            }
            // else leave empty
        }
    }
}
