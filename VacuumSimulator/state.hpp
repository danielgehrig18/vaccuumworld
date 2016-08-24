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
public:
    bool isRoot() {return !parent;};
    char getAction() {return action;};
    State* getParent() {return parent;};
    
    ~State();
};

#endif /* state_hpp */
