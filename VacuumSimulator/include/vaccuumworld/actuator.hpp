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
#include <algorithm>

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
        Gets the status of the actuator.
     
        @param: -
    */
    bool getStatus();
    
    /**
        Sets the status of the actuator to true. Actions can only be performed
        if the status is true.
     
        @param: actionPtr: reference to the last action used by the 
                           environment to update.
    */
    void init(char* actionPtr);
    
    /**
        Checks if this action is applicable, meaning among possibleActions.
     
        @param: action: action that is queried
    */
    bool isApplicable(char action);
    
    /**
        Execute the action action. If the action is not among possibleActions
        or the status is false the execute will return an 'n' (no action).
     
        @param: action: action to be executed.
    */
    void execute(char action);
    
private:
    bool status;
    char* lastActionPtr;
    vector<char> possibleActions;
};

#endif /* actuator_hpp */
