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
                 vector<vector<int>> map, Visualizer &visualizer)
{
    dirtSensorPtr_ = ptr1;
    proximitySensorPtr_ = ptr2;
    directionSensorPtr_ = ptr3;
    locationSensorPtr_ = ptr4;
    
    motorPtr_ = ptr5;
    suckerPtr_ = ptr6;
    
    state_ = map;
    
    visualizer_ = visualizer;
    strategy_.init(visualizer);
    
    strategy_.setType(dirtSensorPtr_->getStatus(),
                     proximitySensorPtr_->getStatus(),
                     directionSensorPtr_->getStatus(),
                     locationSensorPtr_->getStatus(),
                     motorPtr_->getStatus(), suckerPtr_->getStatus());
};

void Agent::executeAction()
{
    if (!strategy_.actionPlanned())
    {
        if (visualizer_.visualize_)
        {
            cout << "planning action..." << endl;
        }
        
        strategy_.planAction(dirtSensorPtr_->getValue(),
                            proximitySensorPtr_->getValue(),
                            directionSensorPtr_->getValue(),
                            locationSensorPtr_->getValue(), state_);
    }
    char action = strategy_.actionSelection();
    
    // TODO: make smarter decision which actuator to take.
    if (motorPtr_->isApplicable(action))
    {
        motorPtr_->execute(action);
    }
    else if (suckerPtr_->isApplicable(action))
    {
        suckerPtr_->execute(action);
    }
}
