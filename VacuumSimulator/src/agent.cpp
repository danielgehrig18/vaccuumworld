//
//  agent.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/agent.hpp"

void Agent::init(DirtSensor* ptr1, ProximitySensor* ptr2, DirectionSensor* ptr3,
                 LocationSensor* ptr4, Motor* ptr5, Sucker* ptr6,
                 vector<vector<int>> map)
{
    dirtSensorPtr = ptr1;
    proximitySensorPtr = ptr2;
    directionSensorPtr = ptr3;
    locationSensorPtr = ptr4;
    
    motorPtr = ptr5;
    suckerPtr = ptr6;
    
    state = map;
    
    strategy.setType(dirtSensorPtr->getStatus(),
                     proximitySensorPtr->getStatus(),
                     directionSensorPtr->getStatus(),
                     locationSensorPtr->getStatus(),
                     motorPtr->getStatus(), suckerPtr->getStatus());
};

void Agent::executeAction()
{
    if (!strategy.actionPlanned())
    {
        if (Visualizer::visual())
        {
            cout << "planning action..." << endl;
        }
        
        strategy.planAction(dirtSensorPtr->getValue(),
                            proximitySensorPtr->getValue(),
                            directionSensorPtr->getValue(),
                            locationSensorPtr->getValue(), state);
    }
    char action = strategy.actionSelection();
    
    // TODO: make smarter decision which actuator to take.
    if (motorPtr->isApplicable(action))
    {
        motorPtr->execute(action);
    }
    else if (suckerPtr->isApplicable(action))
    {
        suckerPtr->execute(action);
    }
}
