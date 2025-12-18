#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include <iostream>

class Car : public Vehicle {
public:
    // Default constructor
    // Initializes an empty Car object
    Car();

    // Parameterized constructor
    // Initializes a Car with make, model, color, MPG, MSRP
    // Also sets Car-specific attributes: spare in trunk and rear windshield wiper
    Car(string mak, string mod, string rgb, int mileage, int MSRP, bool spar, bool wipe);

    // Set whether the car has a spare in the trunk
    void setSpareInTrunk(bool spar);

    // Get whether the car has a spare in the trunk
    bool getSpareInTrunk();

    // Set whether the car has a rear windshield wiper
    void setRearWindshieldWiper(bool wipe);

    // Get whether the car has a rear windshield wiper
    bool getRearWindshieldWiper();

    // Print all details of the car
    // Overrides the virtual printDetails() from Vehicle
    void printDetails() override;

private:
    bool spare;  // Whether car has a spare in the trunk
    bool wiper;  // Whether car has a rear windshield wiper
};

#endif
