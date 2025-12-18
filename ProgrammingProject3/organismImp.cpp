#include "organism.h"

// Constructor: initialize default values
organism::organism() {
    lifeSpan = -1;    // -1 means unspecified lifespan
    age = 0;          // initial age
    name = "";        // default name
    hasMoved = false; // default movement flag
}

// Set the organism's lifespan
void organism::setLifeSpan(int span){
    lifeSpan = span;
}

// Set the organism's current age
void organism::setAge(int a){
    age = a;
}

// Get the organism's lifespan
int organism::getLifeSpan() const {
    return lifeSpan;
}

// Get the organism's current age
int organism::getAge() const {
    return age;
}

// Set the organism's name/type
void organism::setName(const std::string& n){
    name = n;
}

// Get the organism's name/type
std::string organism::getName() const {
    return name;
}
