//
//  state.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef state_hpp
#define state_hpp

#include <array>
#include <vector>

using namespace std;

class State
{
private:
    array<int, 2> location;
    State* parent=NULL;
    vector<State*> children;
    
    char action;
    int pathCost;
    int heuristic;
public:
    bool isRoot() {return !parent;};
    char getAction() {return action;};
    array<int, 2> getLocation() {return location;}
    int getPathCost() {return pathCost;};
    int getTotalCost() {return pathCost + heuristic;}
    void setParent(State* p) {parent = p;}
    void addChild(State* c) {children.push_back(c);}
    State* getParent() {return parent;};
    State* childOf(array<int,2> location, int h);
    
    bool operator==(State s) {return location==s.location;};
    
    State(array<int,2> loc, int p, int h) {location = loc; heuristic = h; pathCost = p;};
    ~State();
};

#endif /* state_hpp */
