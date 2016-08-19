//
//  environment.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "environment.hpp"
#include "dirt_sensor.hpp"
#include "location_sensor.hpp"
#include <string.h>
#include <stdlib.h>

Environment::Environment(int* dimensions, char sensors[2])
{
    int x = dimensions[1];
    int y = dimensions[2];
    
    // instantiate agent
    DirtSensor* dirtSensorPtr;
    LocationSensor* locationSensorPtr;
    
    for (int i = 0; i < sizeof(sensors); i++)
    {
        
        // instantiate sensors
        char name = sensors[i];
        if (name == 'd')
        {
            dirtSensor.init();
            dirtSensorPtr = &dirtSensor;
        }
        else
        {
            locationSensor.init();
            locationSensorPtr = &locationSensor;
        }
    };
    
    // set initialCoords of agent.
    agentLocation[0] = rand()%x;
    agentLocation[1] = rand()%y;

    agent.construct(agentLocation, locationSensorPtr, dirtSensorPtr);
    
    // create 2d grid
    bool** array2d;
    bool* temp = new bool[x * y];
    array2d = new bool*[y];
    
    for (int i = 0; i < y; ++i)
    {
        array2d[i] = (temp + i * x);
    };
    
    grid = array2d;
    
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < x; j++)
        {
            grid[i][j] = bool(rand()%2);
        }
    };
    
    currentDirt = grid[agentLocation[0]][agentLocation[1]];
}

void Environment::updateSensors(bool dirt, int location[2])
{
    
    dirtSensor.setValue(dirt);
    locationSensor.setValue(location);
}
