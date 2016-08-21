//
//  agent.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "agent.hpp"

void Agent::init(DirtSensor* ptr1, ProximitySensor* ptr2, char strgy)
{
    dirtSensorPtr = ptr1;
    proximitySensorPtr = ptr2;
    
    strategy.setType(strgy);
};

char Agent::actionSelection()
{
    bool dirtSensorValue = dirtSensorPtr->getValue();
    array<bool, 4> proximitySensorValue = proximitySensorPtr->getValue();
    
    return strategy.chooseAction(dirtSensorValue, proximitySensorValue);
}