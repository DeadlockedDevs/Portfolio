#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"
#include <iostream>

class Truck : public Vehicle {
public:
    // Default constructor
    // Initializes an empty Truck object
    Truck();

    // Parameterized constructor
    // Initializes a Truck with make, model, color, MPG, MSRP
    // Also sets Truck-specific attributes: side panel storage and auto-release tailgate
    Truck(string mak, string mod, string rgb, int mileage, int MSRP, bool store, bool tail);

    // Set whether the truck has side panel storage
    void setSidePanelStorage(bool store);

    // Get whether the truck has side panel storage
    bool getSidePanelStorage();

    // Set whether the truck has an auto-release tailgate
    void setAutoReleaseTailgate(bool tail);

    // Get whether the truck has an auto-release tailgate
    bool getAutoReleaseTailgate();

    // Print all details of the truck
    // Overrides the virtual printDetails() from Vehicle
    void printDetails() override;

private:
    bool storage;   // Whether the truck has side panel storage
    bool tailgate;  // Whether the truck has an auto-release tailgate
};

#endif
