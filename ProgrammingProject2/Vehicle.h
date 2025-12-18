#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
using namespace std;

class Vehicle {
public:
    // Default constructor
    // Initializes an empty Vehicle object
    Vehicle();

    // Parameterized constructor
    // Initializes a Vehicle with make, model, color, MPG, and MSRP
    Vehicle(string mak, string mod, string rgb, int mileage, int MSRP);

    // Set the make of the vehicle
    void setMake(string mak);

    // Get the make of the vehicle
    string getMake();

    // Set the model of the vehicle
    void setModel(string mod);

    // Get the model of the vehicle
    string getModel();

    // Set the color of the vehicle
    void setColor(string rgb);

    // Get the color of the vehicle
    string getColor();

    // Set the MPG of the vehicle
    void setMPG(int mileage);

    // Get the MPG of the vehicle
    int getMPG();

    // Set the MSRP of the vehicle
    void setMSRP(int MSRP);

    // Get the MSRP of the vehicle
    int getMSRP();

    // Print all details of the vehicle
    // Virtual function to allow derived classes (Car/Truck) to override
    virtual void printDetails();

private:
    string make;   // Vehicle make (e.g., Ford, Toyota)
    string model;  // Vehicle model (e.g., Camry, F-150)
    string color;  // Vehicle color
    int mpg;       // Vehicle miles per gallon
    int msrp;      // Manufacturer's suggested retail price
};

#endif
