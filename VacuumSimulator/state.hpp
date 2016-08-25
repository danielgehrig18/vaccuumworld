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
    bool isRoot();
    char getAction();
    array<int, 2> getLocation();
    int getPathCost();
    int getTotalCost();
    
    void setParent(State* p);
    void addChild(State* c);
    
    State* getParent();
    State* childOf(array<int,2> location, int h);
    bool operator()(State s1, State s2);

    bool operator==(State s);
    
    State(array<int,2> loc, int p, int h);
    ~State();
};

#endif /* state_hpp */
