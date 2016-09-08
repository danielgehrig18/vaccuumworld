//
//  environment.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef environment_hpp
#define environment_hpp

#include <iostream>
#include <vector>
#include <array>

#include "vaccuumworld/agent.hpp"
#include "vaccuumworld/dirt_sensor.hpp"
#include "vaccuumworld/proximity_sensor.hpp"
#include "vaccuumworld/motor.hpp"
#include "vaccuumworld/sucker.hpp"
#include "vaccuumworld/model.hpp"
#include "vaccuumworld/visualizer.hpp"

using namespace std;

class Environment
{
public:
    /**
        Return current map of environment.
     
        @param: -
    */
    vector<vector<int>> getMap();
    
    /**
        Return coordinates of agent.
     
        @param: -
    */
    array<int, 2> getAgentLocation();
    
    /**
        Initializes sensors, agent, and map. Instantiates and activates sensors so
        that they can be written. Randomizes the dirt pattern and agent location.
     
        @param: map: same form as in simulation (see: "simulation.hpp")
                sensors: a list of characters corresponding to used sensors.
                actuators: the used actuators, a list of characters.
    */
    void init(vector<vector<int>> map, vector<char> sensors,
              vector<char> actuators);
    
    /**
        Runs one step of the simulation. This consists of a sensor update,
        action selection by the agent and environment update after action
        execution.
     
        @param: visual: flag to visualize the sensor readings and map.
    */
    void step(bool visual);
    
    /**
        Randomizes the dirt locations in the map and the initial agent location.
     
        @param: -
     */
    void reset();
    
private:
    /**
        Writes into all sensors according to real state environment.
     
        @param: dirt: presence of dirt below agent.
                walls: in order (top, right, bottom, left) presence of walls.
                directions: direction of closest dirtpatch.
                location: coordinates of agent.
    */
    void updateSensors(bool dirt, array<bool, 4> walls,
                       array<bool, 4> directions, array<int, 2> location );
    
    /**
        Update agent location and map based on agents action.
     
        @param: action: action performed by the agent.
                location: location of the agent when it executes the action.
    */
    void updateEnvironment(char action, array<int, 2> location);
    
    array<int, 2> agentLocation;
    bool currentDirt;
    array<bool, 4> walls;
    array<bool, 4> directions;
    vector<vector<int>> map;
    
    char lastAction;

    DirtSensor dirtSensor;
    ProximitySensor proximitySensor;
    LocationSensor locationSensor;
    DirectionSensor directionSensor;
    
    Motor motor;
    Sucker sucker;
    
    Model model;
    Agent agent;
};

#endif /* environment_hpp */
