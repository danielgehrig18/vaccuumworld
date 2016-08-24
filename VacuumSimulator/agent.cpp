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
    bool dirtSensorValue = dirtSensorPtr->getValue();
    array<bool, 4> proximitySensorValue = proximitySensorPtr->getValue();
    array<bool, 4> directionSensorValue = directionSensorPtr->getValue();
    array<int, 2> locationSensorValue = locationSensorPtr->getValue();
    
    if (!strategy.actionPlanned())
        strategy.planAction(dirtSensorValue, proximitySensorValue,
                            directionSensorValue, locationSensorValue, state);
    
    return strategy.executeAction();
}