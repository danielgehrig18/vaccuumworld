//
//  agent.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef agent_hpp
#define agent_hpp

#include <stdio.h>
#include "sensor.hpp"
#include "dirt_sensor.hpp"
#include "location_sensor.hpp"

class Agent
// The agent is an object that can perform actions by consulting its strategy and update its belief state based on sensor input.
{
private:
    // sensor that is used to update the belief-state of the agent.
    LocationSensor* locationSensorPtr;
    DirtSensor* dirtSensorPtr;
    
    // initial position of the agent.
    int coords[2];
    
public:
    void construct(int initialCoords[2],LocationSensor* ptr1, DirtSensor* ptr2);
    char actionSelection();
};

#endif /* agent_hpp */