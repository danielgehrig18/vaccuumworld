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
     
        @param: dirt_sensor_pointer: pointer to the dirt sensor.
                proximity_sensor_pointer: pointer to the proximity sensor.
                direction_sensor_pointer: pointer to the direction sensor.
                location_sensor_pointer: pointer to the location sensor.
                motor_pointer: pointer to the motor
                sucker_pointer: pointer to the sucker
                map: map of the dirt in the environment.
                visualizer: visualizes the agent decision
    */
    void Initialize(DirtSensor* dirt_sensor_pointer,
                    ProximitySensor* proximity_sensor_pointer,
                    DirectionSensor* direction_sensor_pointer,
                    LocationSensor* location_sensor_pointer, Motor* motor_pointer,
                    Sucker* sucker_pointer, vector<vector<int>> map, Visualizer &visualizer);
    
    /**
        Select an action based on the strategy and sensor inputs of the linked 
        sensors.
     
        @param: -
    */
    void ExecuteAction();
    
private:
    DirtSensor* dirt_sensor_pointer_;
    ProximitySensor* proximity_sensor_pointer_;
    DirectionSensor* direction_sensor_pointer_;
    LocationSensor* location_sensor_pointer_;
    
    Motor* motor_pointer_;
    Sucker* sucker_pointer_;
    
    vector<vector<int>> state_;

    Strategy strategy_;
    Visualizer visualizer_;
};

#endif /* agent_hpp */