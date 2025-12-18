#ifndef ORGANISM_H
#define ORGANISM_H

#include <string>
#include <vector>

// Forward declaration to avoid circular dependency
class World;

class organism {
public:
    organism();  // Constructor
    virtual ~organism() {}  // Virtual destructor for safe polymorphic deletion

    // Pure virtual functions: must be implemented by derived classes
    virtual void Reproduce(World& world, std::vector<organism*>& vec) = 0;
    virtual void update(World& world, std::vector<organism*>& vec) = 0;
    virtual std::string Symbol() const = 0; // Character representation of organism

    // Position management
    void setPosition(int r, int c) { row = r; col = c; }
    int getRow() const { return row; }
    int getCol() const { return col; }

    // Name management
    void setName(const std::string& n);
    std::string getName() const;

    // Age management
    void setAge(int a);
    int getAge() const;

    // Lifespan management
    void setLifeSpan(int ls);
    int getLifeSpan() const;

    // Movement flag for daily update
    void setHasMoved(bool b) { hasMoved = b; }
    bool getHasMoved() const { return hasMoved; }

protected:
    std::string name;  // Organism type name
    int row, col;      // Position in the world grid
    int age;           // Current age
    int lifeSpan;      // Maximum lifespan
    bool hasMoved;     // Flag to prevent double movement in a single update
};

#endif
