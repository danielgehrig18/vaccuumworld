//
//  environment.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef environment_hpp
#define environment_hpp

#include <stdio.h>
#include "agent.hpp"
#include "location_sensor.hpp"
#include "dirt_sensor.hpp"
#include <vector>

using namespace std;

class Environment
{
private:
    // corresponds to the true location and dirt presence
    int agentLocation[2];
    bool currentDirt;
    int dimensions[2];
    
    // sensor runs all the time and collects data from environment. agent can access sensor data.
    DirtSensor dirtSensor;
    LocationSensor locationSensor;
    
    bool grid[2];
    
    Agent agent;
    
public:
    void init(int dimensions[2], char sensors[2]);
    bool* getGrid() {return grid;};
    int* getDimensions() {return dimensions;};
    void updateSensors(bool dirt, int location[2]);
    void updateEnvironment(char action, int location[2]);
    void step(bool visual);
};

#endif /* environment_hpp */
