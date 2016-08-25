//
//  environment.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef environment_hpp
#define environment_hpp

#include <vector>
#include <array>

#include "agent.hpp"
#include "dirt_sensor.hpp"
#include "proximity_sensor.hpp"
#include "model.hpp"

using namespace std;

class Environment
{
private:
    // corresponds to the true location and dirt presence
    array<int, 2> agentLocation;
    bool currentDirt;
    array<bool, 4> walls;
    array<bool, 4> directions;
    
    vector<vector<int>> map;
    
    // model
    Model model;
    
    // sensor runs all the time and collects data from environment. agent can access sensor data.
    DirtSensor dirtSensor;
    ProximitySensor proximitySensor;
    LocationSensor locationSensor;
    DirectionSensor directionSensor;
    
    Agent agent;
    
public:
    void init(vector<vector<int>> map, vector<char> sensors, char strategy);
    vector<vector<int>> getMap();
    array<int, 2> getAgentLocation();
    void updateSensors(bool dirt, array<bool, 4> walls,
                       array<bool, 4> directions, array<int, 2> location );
    void updateEnvironment(char action, array<int, 2> location);
    void step(bool visual);
    void reset();
};

#endif /* environment_hpp */
