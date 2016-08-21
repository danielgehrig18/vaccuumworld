//
//  agent.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "agent.hpp"

void Agent::construct(LocationSensor* ptr1, DirtSensor* ptr2, char strgy)
{
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