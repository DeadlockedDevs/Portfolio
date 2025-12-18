#include "Car.h"
#include <iostream>
using namespace std;

// Default constructor
// Initializes an empty Car object with default values
Car::Car() {}

// Parameterized constructor
// Initializes a Car object with given make, model, color, MPG, MSRP
// Also sets Car-specific attributes: spare in trunk and rear windshield wiper
Car::Car(string mak, string mod, string rgb, int mileage, int MSRP, bool spar, bool wipe)
    : Vehicle(mak, mod, rgb, mileage, MSRP) 
{
    spare = spar;
    wiper = wipe;
}

// Set whether the car has a spare in the trunk
void Car::setSpareInTrunk(bool spar) {
    spare = spar;
}

// Get whether the car has a spare in the trunk
bool Car::getSpareInTrunk() {
    return spare;
}

// Set whether the car has a rear windshield wiper
void Car::setRearWindshieldWiper(bool wipe) {
    wiper = wipe;
}

// Get whether the car has a rear windshield wiper
bool Car::getRearWindshieldWiper() {
    return wiper;
}

// Print all details of the car
// Calls the base class printDetails() to print common vehicle info
// Then prints Car-specific attributes
void Car::printDetails() {
    Vehicle::printDetails();
    cout << "Spare: " << getSpareInTrunk()
         << "\nWiper: " << getRearWindshieldWiper() << endl;
}
