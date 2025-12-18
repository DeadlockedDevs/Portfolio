#include "prey.h"
#include "World.h"
#include <iostream>
using namespace std;

// Constructor
prey::prey() {
    setName("Prey");
    setLifeSpan(16);
    setRepFrame(5);
    setStarve(5);
    setAge(0);
    //cout << "[DEBUG] Prey created at initial position.\n";
}

// Symbol displayed on world grid
string prey::Symbol() const { return "🐇"; }

// Prey movement logic
void prey::Movement(World& world, vector<organism*>& vec) {
    int speed = 1;
    pair<int,int> currLoc(getRow(), getCol());
    pair<int,int> preyVec(0,0);
    pair<int,int> predatorVec(0,0);
    pair<int,int> plantVec(0,0);

    //cout << "[DEBUG] Prey at (" << currLoc.first << "," << currLoc.second << ") moving.\n";

    // Adjust movement based on reproduction frame and starvation
    if(getRepFrame() < 5) preyVec = moveTowards(world, "Prey");
    if(getStarve() < 2) speed = 3;
    else if(getStarve() < 3) speed = 2;

    predatorVec = moveAway(world, "Predator"); // avoid predators
    plantVec = moveTowards(world, "Plant");    // move towards plants
    plantVec.first *= speed;
    plantVec.second *= speed;

    int newRow = currLoc.first + preyVec.first + predatorVec.first + plantVec.first;
    int newCol = currLoc.second + preyVec.second + predatorVec.second + plantVec.second;

    // Clamp to world boundaries
    if(newRow < 0) newRow = 0; else if(newRow >= 20) newRow = 19;
    if(newCol < 0) newCol = 0; else if(newCol >= 20) newCol = 19;

    //cout << "[DEBUG] Prey target position: (" << newRow << "," << newCol << ")\n";

    // Eat plants in a 3x3 area
    for(int r = newRow-1; r <= newRow+1; r++){
        for(int c = newCol-1; c <= newCol+1; c++){
            if(world.isInBounds(r,c)){
                organism* nearby = world.getAt(r,c);
                if(nearby && nearby->getName() == "Plant"  && world.getAt(r,c) == nearby){
                    //cout << "[DEBUG] Prey eating plant at (" << r << "," << c << ")\n";
                    world.removeOrganism(r,c, vec);
                    setStarve(getStarve() + 3);
                }
            }
        }
    }

    // Handle movement into new cell
    organism* target = world.getAt(newRow,newCol);
    if(world.isEmpty(newRow,newCol)){
        //cout << "[DEBUG] Prey moving to empty cell.\n";
        world.moveOrganism(this, newRow, newCol);
    } else if(target){
        string type = target->getName();
        if(type == "Prey"){
            pair<int,int> adj = world.findEmptyAdjacent(newRow,newCol);
            if(adj.first != -1){
                //cout << "[DEBUG] Prey avoiding another prey, moving to (" << adj.first << "," << adj.second << ")\n";
                world.moveOrganism(this, adj.first, adj.second);
            }
        } else if(type == "Plant"){
            //cout << "[DEBUG] Prey replacing plant at (" << newRow << "," << newCol << ")\n";
            world.removeOrganism(newRow,newCol, vec);
            world.moveOrganism(this, newRow,newCol);
            setStarve(getStarve() + 3);
        } else if(type == "Predator"){
            //cout << "[DEBUG] Prey dies due to predator at (" << getRow() << "," << getCol() << ")\n";
            world.removeOrganism(getRow(), getCol(), vec);
        }
    }
}

// Reproduction logic
void prey::Reproduce(World& world, vector<organism*>& vec){
    if(getRepFrame() > 0) return;

    // Try empty adjacent spot first
    pair<int,int> emptySpot = world.findEmptyAdjacent(getRow(), getCol());
    if(emptySpot.first != -1){
        //cout << "[DEBUG] Prey reproducing at (" << emptySpot.first << "," << emptySpot.second << ")\n";
        prey* baby = new prey();
        world.addOrganism(baby, emptySpot.first, emptySpot.second);
        setRepFrame(5);
        return;
    }

    // Otherwise try replacing a plant nearby
    int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    for(auto& d : directions){
        int nr = getRow() + d[0];
        int nc = getCol() + d[1];
        if(world.isInBounds(nr,nc)){
            organism* org = world.getAt(nr,nc);
            if(org && org->getName() == "Plant"){
                //cout << "[DEBUG] Prey reproducing by replacing plant at (" << nr << "," << nc << ")\n";
                world.removeOrganism(nr,nc, vec);
                prey* baby = new prey();
                world.addOrganism(baby, nr, nc);
                setStarve(getStarve() + 3);
                setRepFrame(5);
                break;
            }
        }
    }
}

// Daily update
void prey::update(World& world, vector<organism*>& vec){
    if(getHasMoved()) return;

    // Age and hunger
    setAge(getAge() + 1);
    setRepFrame(getRepFrame() - 1);
    setStarve(getStarve() - 1);

    // Die if too old or starving
    if(getAge() >= getLifeSpan() || getStarve() <= 0){
        world.removeOrganism(getRow(), getCol(), vec);
        return;
    }

    // Try to reproduce first
    bool reproduced = false;

    if(getRepFrame() <= 0){
        pair<int,int> emptySpot = world.findEmptyAdjacent(getRow(), getCol());
        if(emptySpot.first != -1){
            prey* baby = new prey();
            world.addOrganism(baby, emptySpot.first, emptySpot.second);
            setRepFrame(5);
            reproduced = true;
        } else {
            // try replacing plant if no empty spot
            int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
            for(auto& d : directions){
                int nr = getRow() + d[0];
                int nc = getCol() + d[1];
                if(world.isInBounds(nr,nc)){
                    organism* org = world.getAt(nr,nc);
                    if(org && org->getName() == "Plant"){
                        world.removeOrganism(nr,nc, vec);
                        prey* baby = new prey();
                        world.addOrganism(baby, nr, nc);
                        setStarve(getStarve() + 3); // optional: gain energy from plant
                        setRepFrame(5);
                        reproduced = true;
                        break;
                    }
                }
            }
        }
    }

    // Only move if reproduction didn't happen
    if(!reproduced){
        Movement(world, vec);
    }

    setHasMoved(true);
}
