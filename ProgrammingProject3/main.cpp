#include <iostream>
#include <fstream>
#include "World.h"
#include "organism.h"
#include "plant.h"
#include "animal.h"
#include "prey.h"
#include "predator.h"
#include <vector>
#include <limits> 
using namespace std;

// Global world object
World world;




// Function to clear invalid input from the input buffer
void clearInput() {
    cin.clear(); // clear error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
}

// Get an integer input in a specific range
int getIntInRange(string message, int minVal, int maxVal) {
    int x;
    while (true) {
        cout << message;
        if (cin >> x && x >= minVal && x <= maxVal) return x; // valid input
        cout << "Invalid input! Please enter a number between " << minVal << " and " << maxVal << ".\n";
        clearInput(); // remove invalid input from buffer
    }
}

// Get a double input in a specific range
double getDoubleInRange(string message, double minVal, double maxVal) {
    double x;
    while (true) {
        cout << message;
        if (cin >> x && x >= minVal && x <= maxVal) return x; // valid input
        cout << "Invalid input! Please enter a decimal between " << minVal << " and " << maxVal << ".\n";
        clearInput(); // remove invalid input from buffer
    }
}
// Display Panel for Graphical User Interface
void runner() {
    int choice = -1;

    while (true) {
        // Display menu
        cout << "-----World User Interface-----\n";
        cout << "0. Exit the program.\n";
        cout << "1. Go to the next day.\n";
        cout << "2. Add an organism.\n";
        cout << "3. Random generate world.\n";

        // Get valid menu choice
        choice = getIntInRange("Enter option: ", 0, 3);

        if (choice == 0) break; // Exit program

        // Option 1: Advance simulation by one day
        if (choice == 1) {
            world.update();   // update all organisms
            world.display();  // show current world state
        }

        // Option 2: Add a single organism at a specific location
        if (choice == 2) {
            int typeChoice;
            int r, c;

            cout << "\n--- Add Organism Menu ---\n";
            cout << "1. Add Plant\n";
            cout << "2. Add Prey\n";
            cout << "3. Add Predator\n";

            // Get valid organism type and coordinates
            typeChoice = getIntInRange("Enter organism type: ", 1, 3);
            r = getIntInRange("Enter row (0-19): ", 0, 19);
            c = getIntInRange("Enter col (0-19): ", 0, 19);

            // Boundary check
            if (!world.isInBounds(r, c)) {
                cout << "Invalid location! Must be inside the 20x20 grid.\n\n";
                continue;
            }

            // Check if spot is empty
            if (world.getAt(r, c) != nullptr) {
                cout << "That spot is already occupied!\n\n";
                continue;
            }

            // Add chosen organism
            switch (typeChoice) {
                case 1:
                    world.addOrganism(new plant(), r, c);
                    cout << "Plant added.\n";
                    break;
                case 2:
                    world.addOrganism(new prey(), r, c);
                    cout << "Prey added.\n";
                    break;
                case 3:
                    world.addOrganism(new predator(), r, c);
                    cout << "Predator added.\n";
                    break;
            }

            world.display(); // show updated world
        }

        // Option 3: Randomly generate organisms in the world
        if (choice == 3) {
            double pPlant, pPrey, pPred;

            // Get valid probabilities
            pPlant = getDoubleInRange("Enter plant chance (0-1): ", 0.0, 1.0);
            pPrey  = getDoubleInRange("Enter prey chance (0-1): ", 0.0, 1.0);
            pPred  = getDoubleInRange("Enter predator chance (0-1): ", 0.0, 1.0);

            // Check total probability
            if (pPlant + pPrey + pPred > 1.0) {
                cout << "Total probability cannot exceed 1.0!\n\n";
                continue;
            }

            world.randomGenerate(pPlant, pPrey, pPred);
            cout << "Random world generated.\n\n";
            world.display(); // show generated world
        }
    }
}


int main() {
    // Add plants
    //world.addOrganism(new plant(), 3, 3);
    //world.addOrganism(new plant(), 3, 10);
    //world.addOrganism(new plant(), 3, 17);
    //world.addOrganism(new plant(), 8, 4);
    //world.addOrganism(new plant(), 8, 15);
    //world.addOrganism(new plant(), 12, 7);
    //world.addOrganism(new plant(), 12, 13);
    //world.addOrganism(new plant(), 17, 2);
    //world.addOrganism(new plant(), 17, 10);
    //world.addOrganism(new plant(), 17, 18);

    // Add preys
    //world.addOrganism(new prey(), 5, 5);
    //world.addOrganism(new prey(), 6, 14);
    //world.addOrganism(new prey(), 10, 8);
    //world.addOrganism(new prey(), 14, 4);
    //world.addOrganism(new prey(), 15, 15);

    // Add predators
    //world.addOrganism(new predator(), 10, 3);
    //world.addOrganism(new predator(), 5, 16);
    //world.addOrganism(new predator(), 5, 12);

    // Initial display (optional)
    //world.update();
    //world.display();

    // Start the interactive runner loop
    runner();
}
