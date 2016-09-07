//
//  actuator.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 02/09/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/actuator.hpp"

void Actuator::init()
{
    status = true;
}

char Actuator::execute(char action)
{
    if (status && find(possibleActions.begin(), possibleActions.end(), action)
        != possibleActions.end())
    {
        return action;
    }
    else
    {
        return 'n';
    }
}

