//
//  actuator.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 02/09/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef actuator_hpp
#define actuator_hpp

#include <vector>

using namespace std;

class Actuator
{
public:
    /**
        Sets the actions that are possible for the actuator.
     
        @param: possibleActions: vector of characters, each corresponding to action.
    */
    void setPossibleActions(vector<char> possibleActions);
    
    /**
        Sets the status of the actuator to true. Actions can only be performed
        if the status is true.
     
        @param: -
    */
    void init();
    
    /**
        Execute the action action. If the action is not among possibleActions
        or the status is false the execute will return an 'n' (no action).
     
        @param: action: action to be executed.
    */
    char execute(char action);
    
private:
    bool status;
    vector<char> possibleActions;
};

#endif /* actuator_hpp */
