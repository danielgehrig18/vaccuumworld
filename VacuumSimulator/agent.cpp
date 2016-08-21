//
//  agent.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "agent.hpp"

void Agent::construct(array<int, 2> initialCoords, LocationSensor* ptr1, DirtSensor* ptr2, char strgy)
{
    coords[0] = initialCoords[0];
    coords[1] = initialCoords[1];
    
    locationSensorPtr = ptr1;
    dirtSensorPtr = ptr2;
    
    strategy.setType(strgy);
};

char Agent::actionSelection()
{
    array<int, 2> locationSensorValue = locationSensorPtr->getValue();
    bool dirtSensorValue = dirtSensorPtr->getValue();
    
    return strategy.chooseAction(locationSensorValue, dirtSensorValue);
}