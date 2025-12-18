#include "predator.h"
#include "World.h"
#include <iostream>
#include <algorithm>
using namespace std;

predator::predator() {
    setName("Predator");
    setLifeSpan(40);
    setRepFrame(15);
    setStarve(15);
    setAge(0);
    //cout << "[DEBUG] Predator created.\n";
}

string predator::Symbol() const { return "🦊"; }

void predator::Movement(World& world, vector<organism*>& vec) {
    int speed = 1;
    pair<int,int> currLoc(getRow(), getCol());
    pair<int,int> predatorVec(0,0), preyVec(0,0), randomVec(0,0);

    if(getRepFrame() < 5) predatorVec = moveTowards(world,"Predator");
    if(getStarve() < 2) speed = 3;
    else if(getStarve() < 3) speed = 2;

    preyVec = moveTowards(world,"Prey");
    preyVec.first *= speed;
    preyVec.second *= speed;

    randomVec = randomMovement();

    int newRow = currLoc.first + predatorVec.first + preyVec.first + randomVec.first;
    int newCol = currLoc.second + predatorVec.second + preyVec.second + randomVec.second;

    if(newRow < 0) newRow = 0; else if(newRow >= 20) newRow = 19;
    if(newCol < 0) newCol = 0; else if(newCol >= 20) newCol = 19;

    organism* target = world.getAt(newRow,newCol);

    // SAFEGUARD 1 — pointer sanity check
    if(target && (target == this || target->getRow() < 0 || target->getCol() < 0)) return;

    if(!target){
        world.moveOrganism(this,newRow,newCol);
    }
    else if(target->getName() == "Prey"){
        // SAFEGUARD 2 — ensure target still in vector
        if(std::find(vec.begin(), vec.end(), target) != vec.end()) {
            world.removeOrganism(target->getRow(), target->getCol(), vec);
            setStarve(getStarve() + 5);
        }
        world.moveOrganism(this,newRow,newCol);
    }
    else if(target->getName() == "Predator"){
        pair<int,int> adj = world.findEmptyAdjacent(newRow,newCol);
        if(adj.first != -1){
            world.moveOrganism(this, adj.first, adj.second);
        }
    }
    else if(target->getName() == "Plant"){
        if(std::find(vec.begin(), vec.end(), target) != vec.end()) {
            world.removeOrganism(target->getRow(), target->getCol(), vec);
            setStarve(getStarve() + 1);
        }
        world.moveOrganism(this,newRow,newCol);
    }

    // SAFEGUARD 3 — safe eating nearby prey
    for(int dr=-1; dr<=1; dr++){
        for(int dc=-1; dc<=1; dc++){
            int r = getRow() + dr;
            int c = getCol() + dc;

            if(!world.isInBounds(r,c)) continue;

            organism* nearby = world.getAt(r,c);
            if(nearby && nearby->getName() == "Prey") {
                // only delete if still in vector
                if(std::find(vec.begin(), vec.end(), nearby) != vec.end()) {
                    world.removeOrganism(r, c, vec);
                    setStarve(getStarve() + 5);
                }
            }
        }
    }
}

void predator::Reproduce(World& world, vector<organism*>& vec){
    if(getRepFrame() > 0 ) return;
    
    pair<int,int> emptySpot = world.findEmptyAdjacent(getRow(), getCol());
    if(emptySpot.first != -1 && hasPredator(world) != nullptr){
        predator* baby = new predator();
        world.addOrganism(baby, emptySpot.first, emptySpot.second);
        setRepFrame(9);
        return;
    }

    int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    for(auto& d : directions){
        int nr = getRow() + d[0];
        int nc = getCol() + d[1];
        if(world.isInBounds(nr,nc) && hasPredator(world) != nullptr){
            organism* org = world.getAt(nr,nc);
            if(org && org->getName() == "Plant"){
                world.removeOrganism(nr,nc, vec);
                predator* baby = new predator();
                world.addOrganism(baby,nr,nc);
                setStarve(getStarve() + 1);
                setRepFrame(9);
                break;
            }
        }
    }
}

void predator::update(World& world, vector<organism*>& vec){
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
            predator* baby = new predator();
            world.addOrganism(baby, emptySpot.first, emptySpot.second);
            setRepFrame(9);
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
                        predator* baby = new predator();
                        world.addOrganism(baby, nr, nc);
                        setStarve(getStarve() + 1); // optional: gain energy from plant
                        setRepFrame(9);
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


