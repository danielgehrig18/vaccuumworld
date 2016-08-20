//
//  strategy.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 20/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "strategy.hpp"
#include <stdlib.h>

char Strategy::chooseAction(int locationSensorValue[2], bool dirtSensorValue)
{
    switch (type) {
        case 'r':
            return actions[rand()%6];
        case 'g':
            if (dirtSensorValue) return 's';
            else return actions[rand()%4];
        default: return 'n';
    }
}

void Strategy::setType(char strategy)
{
    type = strategy;
}