//
//  agent.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef agent_hpp
#define agent_hpp

#include <vector>

#include "dirt_sensor.hpp"
#include "proximity_sensor.hpp"
#include "direction_sensor.hpp"
#include "location_sensor.hpp"
#include "strategy.hpp"

using namespace std;

class Agent
{
public:
    /**
        Initialises the agent by linking it to the sensors and setting its state
        (dirt map for state search) and sets the strategy.
     
        @param: ptr1: pointer to the dirt sensor.
                ptr2: pointer to the proximity sensor.
                ptr1: pointer to the direction sensor.
                ptr1: pointer to the location sensor.
                state: map of the dirt in the environment.
                strategy: strategy to be followed during action selection.
    */
    void init(DirtSensor* ptr1, ProximitySensor* ptr2, DirectionSensor* ptr3,
              LocationSensor* ptr4, vector<vector<int>> state, char strategy);
    
    /**
        Select an action based on the strategy and sensor inputs of the linked 
        sensors.
     
        @param: -
    */
    char actionSelection();
    
private:
    DirtSensor* dirtSensorPtr;
    ProximitySensor* proximitySensorPtr;
    DirectionSensor* directionSensorPtr;
    LocationSensor* locationSensorPtr;
    
    vector<vector<int>> state;
    
    Strategy strategy;
};

#endif /* agent_hpp */