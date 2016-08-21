//
//  strategy.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 20/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "strategy.hpp"
#include <stdlib.h>

char Strategy::chooseAction(array<int, 2> locationSensorValue, bool dirtSensorValue, array<int, 2>gridDimensions)
{
    switch (type) {
        case 'r':
            return randomSearch();
        case 'g':
            return greedySearch(dirtSensorValue);
        case 'h':
            return moreGreedySearch(locationSensorValue, dirtSensorValue, gridDimensions);
        break;
        default: return 'n';
    }
}

char Strategy::randomSearch()
{
    return actions[rand()%5];
}

char Strategy::greedySearch(bool dirtSensor)
{
    if (dirtSensor) return 's';
    else return actions[rand()%4];
}

char Strategy::moreGreedySearch(array<int, 2> locationSensorValue, bool dirtSensorValue, array<int, 2>gridDimensions)
{
    if (dirtSensorValue) return 's';
    else {
        int x = locationSensorValue[0];
        int y = locationSensorValue[1];
        
        int xMax = gridDimensions[0]-1;
        int yMax = gridDimensions[1]-1;
        
        if ((x > 0 && x < xMax) && (y > 0 && y < yMax)) int randIndex = rand()%4;
        else if 
        
        
        
    }
    
    
}

void Strategy::setType(char strategy)
{
    type = strategy;
}