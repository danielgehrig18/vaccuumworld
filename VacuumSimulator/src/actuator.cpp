//
//  actuator.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 02/09/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/actuator.hpp"

void Actuator::SetPossibleActions(vector<char> possible_actions)
{
    possible_actions_ = possible_actions;
}

bool Actuator::GetStatus()
{
    return status_;
}

void Actuator::Initialize(char* action_pointer)
{
    status_ = true;
    last_action_pointer_ = action_pointer;
    
}

bool Actuator::IsApplicable(char action)
{
    return find(possible_actions_.begin(), possible_actions_.end(), action)
    != possible_actions_.end();
}

void Actuator::Execute(char action)
{
    if (status_ && IsApplicable(action))
    {
        *last_action_pointer_ = action;
    }
    else
    {
        *last_action_pointer_ = 'n';
    }
}