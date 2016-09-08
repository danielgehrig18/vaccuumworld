//
//  actuator.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 02/09/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/actuator.hpp"

void Actuator::setPossibleActions(vector<char> possActions)
{
    possibleActions_ = possActions;
}

bool Actuator::getStatus()
{
    return status_;
}

void Actuator::init(char* actionPtr)
{
    status_ = true;
    lastActionPtr_ = actionPtr;
    
}

bool Actuator::isApplicable(char action)
{
    return find(possibleActions_.begin(), possibleActions_.end(), action)
    != possibleActions_.end();
}

void Actuator::execute(char action)
{
    if (status_ && isApplicable(action))
    {
        *lastActionPtr_ = action;
    }
    else
    {
        *lastActionPtr_ = 'n';
    }
}

