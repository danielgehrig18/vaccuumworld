//
//  agent.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "agent.hpp"

void Agent::init(LocationSensor* ptr1, DirtSensor* ptr2, ProximitySensor* ptr3, char strgy)
{
    locationSensorPtr = ptr1;
    dirtSensorPtr = ptr2;
    proximitySensorPtr = ptr3;
    
    strategy.setType(strgy);
};

char Agent::actionSelection()
{
    array<int, 2> locationSensorValue = locationSensorPtr->getValue();
    bool dirtSensorValue = dirtSensorPtr->getValue();
    array<bool, 4> proximitySensorValue = proximitySensorPtr->getValue();
    
    return strategy.chooseAction(dirtSensorValue, proximitySensorValue);
}