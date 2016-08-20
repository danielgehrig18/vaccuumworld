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
#include <iostream>

using namespace std;

void Environment::init(int dim[2], char sensors[2])
{
    int x = dim[0];
    int y = dim[1];
    
    memcpy(dimensions, dim, sizeof(dimensions));
    
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
    
    for (int i = 0; i < x*y; i++)
    {
        grid[i] = bool(rand()%2);
    };
    
    currentDirt = grid[agentLocation[0] + (y-1) * agentLocation[1]];
}

void Environment::updateSensors(bool dirt, int location[2])
{
    
    dirtSensor.setValue(dirt);
    locationSensor.setValue(location);
}

void Environment::step(bool visual)
{
    // updates sensors based on true dirt and location
    updateSensors(currentDirt, agentLocation);
    
    // agent makes decision depending on sensor reading
    char action = agent.actionSelection();
    
    // environment updated based on action and true location of agent.
    updateEnvironment(action, agentLocation);
    
    
    if (visual)
    {
        int* loc = locationSensor.getValue();
        cout << "Sensors: " << endl;
        cout << "dirt: " << dirtSensor.getValue() << endl;
        cout << "loc: " << loc[0] << " " << loc[1] << endl;
        cout << "action: " << action <<  endl;
        cout << "Current Location:" << endl;
        cout << agentLocation[0] << " " << agentLocation[1] << endl;
    }
}

void Environment::updateEnvironment(char action, int location[2])
{
    if (action=='s') {
        grid[agentLocation[0] + (dimensions[1]-1) * agentLocation[1]] = false;
    }
    else if (action=='l')
    {
        if (location[1]==1) {
            agentLocation[1] = 0;
        }
    }
    else if (action=='r')
    {
        if (location[1]==0) {
            agentLocation[1] = 1;
        }
    }
    
    currentDirt = grid[agentLocation[0] + (dimensions[1]-1) * agentLocation[1]];
}
