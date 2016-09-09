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
     
        @param: possible_actions: vector of characters, each corresponding to action.
    */
    void SetPossibleActions(vector<char> possible_actions);
    
    /**
        Gets the status of the actuator.
     
        @param: -
    */
    bool GetStatus();
    
    /**
        Sets the status of the actuator to true. Actions can only be performed
        if the status is true.
     
        @param: action_pointer: reference to the last action used by the
                           environment to update.
    */
    void Initialize(char* action_pointer);
    
    /**
        Checks if this action is applicable, meaning among possibleActions.
     
        @param: action: action that is queried
    */
    bool IsApplicable(char action);
    
    /**
        Execute the action action. If the action is not among possibleActions
        or the status is false the execute will return an 'n' (no action).
     
        @param: action: action to be executed.
    */
    void Execute(char action);
    
private:
    bool status_;
    char* last_action_pointer_;
    vector<char> possible_actions_;
};

#endif /* actuator_hpp */