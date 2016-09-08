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

#include "vaccuumworld/dirt_sensor.hpp"
#include "vaccuumworld/proximity_sensor.hpp"
#include "vaccuumworld/direction_sensor.hpp"
#include "vaccuumworld/location_sensor.hpp"
#include "vaccuumworld/motor.hpp"
#include "vaccuumworld/sucker.hpp"
#include "vaccuumworld/strategy.hpp"
#include "vaccuumworld/visualizer.hpp"

using namespace std;

class Agent
{
public:
    /**
        Initialises the agent by linking it to the sensors and setting its state
        (dirt map for state search) and sets the strategy.
     
        @param: ptr1: pointer to the dirt sensor.
                ptr2: pointer to the proximity sensor.
                ptr3: pointer to the direction sensor.
                ptr4: pointer to the location sensor.
                actuators: a list of actuators to be used.
                state: map of the dirt in the environment.
    */
    void init(DirtSensor* DSPtr, ProximitySensor* PSPtr, DirectionSensor* DiSPtr,
              LocationSensor* LSPtr, Motor* motorPtr, Sucker* suckerPtr,
              vector<vector<int>> state, Visualizer &visualizer);
    
    /**
        Select an action based on the strategy and sensor inputs of the linked 
        sensors.
     
        @param: -
    */
    void executeAction();
    
private:
    DirtSensor* dirtSensorPtr_;
    ProximitySensor* proximitySensorPtr_;
    DirectionSensor* directionSensorPtr_;
    LocationSensor* locationSensorPtr_;
    
    Motor* motorPtr_;
    Sucker* suckerPtr_;
    
    vector<vector<int>> state_;

    Strategy strategy_;
    Visualizer visualizer_;
};

#endif /* agent_hpp */
