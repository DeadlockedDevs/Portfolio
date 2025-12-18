#include "Vehicle.h"
#include <iostream>
using namespace std;

// Default constructor
// Initializes an empty Vehicle object with default values
Vehicle::Vehicle() {}

// Parameterized constructor
// Initializes a Vehicle object with given make, model, color, MPG, and MSRP
Vehicle::Vehicle(string mak, string mod, string rgb, int mileage, int MSRP) {
    make = mak;
    model = mod;
    color = rgb;
    mpg = mileage;
    msrp = MSRP;
}

// Set the make of the vehicle
void Vehicle::setMake(string mak) {
    make = mak;
}

// Get the make of the vehicle
string Vehicle::getMake() {
    return make;
}

// Set the model of the vehicle
void Vehicle::setModel(string mod) {
    model = mod;
}

// Get the model of the vehicle
string Vehicle::getModel() {
    return model;
}

// Set the color of the vehicle
void Vehicle::setColor(string rgb) {
    color = rgb;
}

// Get the color of the vehicle
string Vehicle::getColor() {
    return color;
}

// Set the MPG of the vehicle
void Vehicle::setMPG(int mileage) {
    mpg = mileage;
}

// Get the MPG of the vehicle
int Vehicle::getMPG() {
    return mpg;
}

// Set the MSRP of the vehicle
void Vehicle::setMSRP(int MSRP) {
    msrp = MSRP;
}

// Get the MSRP of the vehicle
int Vehicle::getMSRP() {
    return msrp;
}

// Print all the details of the vehicle to the console
// This is a virtual function, so it can be overridden by derived classes
void Vehicle::printDetails() {
    cout << "\nMake: " << getMake()
         << "\nModel: " << getModel()
         << "\nColor: " << getColor()
         << "\nMPG: " << getMPG()
         << "\nMSRP: " << getMSRP() << endl;
}
