//
//  agent.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "location_sensor.hpp"
#include "dirt_sensor.hpp"
#include "agent.hpp"
#include <string.h>

void Agent::construct(int initialCoords[2], LocationSensor* ptr1, DirtSensor* ptr2)
{
    coords[0] = initialCoords[0];
    coords[1] = initialCoords[1];
    
    locationSensorPtr = ptr1;
    dirtSensorPtr = ptr2;
};

char Agent::actionSelection()
{
    int* locationSensorValue = locationSensorPtr->getValue();
    bool dirtSensorValue = dirtSensorPtr->getValue();
    
    if (dirtSensorValue){
        return 's';
    }
    else
        if (locationSensorValue[1] == 1) {
            return 'l';
        }
        else
            return 'r';
}