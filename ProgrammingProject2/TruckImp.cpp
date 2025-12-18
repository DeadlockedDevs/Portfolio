#include "Truck.h"
#include <iostream>
using namespace std;

// Default constructor
// Initializes an empty Truck object with default values
Truck::Truck() {}

// Parameterized constructor
// Initializes a Truck object with given make, model, color, MPG, MSRP
// Also sets Truck-specific attributes: side panel storage and auto-release tailgate
Truck::Truck(string mak, string mod, string rgb, int mileage, int MSRP, bool store, bool tail)
    : Vehicle(mak, mod, rgb, mileage, MSRP) 
{
    storage = store;
    tailgate = tail;
}

// Set whether the truck has side panel storage
void Truck::setSidePanelStorage(bool store) {
    storage = store;
}

// Get whether the truck has side panel storage
bool Truck::getSidePanelStorage() {
    return storage;
}

// Set whether the truck has an auto-release tailgate
void Truck::setAutoReleaseTailgate(bool tail) {
    tailgate = tail;
}

// Get whether the truck has an auto-release tailgate
bool Truck::getAutoReleaseTailgate() {
    return tailgate;
}

// Print all details of the truck
// Calls the base class printDetails() to print common vehicle info
// Then prints Truck-specific attributes
void Truck::printDetails() {
    Vehicle::printDetails();
    cout << "Storage: " << getSidePanelStorage()
         << "\nTailgate: " << getAutoReleaseTailgate() << endl;
}
