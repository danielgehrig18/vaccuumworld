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
    possibleActions = possActions;
}

bool Actuator::getStatus()
{
    return status;
}

void Actuator::init(char* actionPtr)
{
    status = true;
    lastActionPtr = actionPtr;
    
}

bool Actuator::isApplicable(char action)
{
    return find(possibleActions.begin(), possibleActions.end(), action)
    != possibleActions.end();
}

void Actuator::execute(char action)
{
    if (status && isApplicable(action))
    {
        *lastActionPtr = action;
    }
    else
    {
        *lastActionPtr = 'n';
    }
}

