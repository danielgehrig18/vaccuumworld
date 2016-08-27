//
//  agent.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "agent.hpp"

void Agent::init(DirtSensor* ptr1, ProximitySensor* ptr2, DirectionSensor* ptr3,
                 LocationSensor* ptr4, vector<vector<int>> map, char strtgy)
{
    dirtSensorPtr = ptr1;
    proximitySensorPtr = ptr2;
    directionSensorPtr = ptr3;
    locationSensorPtr = ptr4;
    
    state = map;
    
    strategy.setType(strtgy);
};

char Agent::actionSelection()
{
    if (!strategy.actionPlanned())
    {
        strategy.planAction(dirtSensorPtr->getValue(),
                            proximitySensorPtr->getValue(),
                            directionSensorPtr->getValue(),
                            locationSensorPtr->getValue(), state);
    }
    
    return strategy.executeAction();
}