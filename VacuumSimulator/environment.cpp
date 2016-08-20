//
//  environment.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "environment.hpp"
#include <iostream>

using namespace std;

void Environment::init(vector<vector<int>> dim, array<char, 2> sensors, char strategy)
{
    srand (time(NULL));
    
    unsigned long int y = dim.size();
    unsigned long int x = dim[0].size();
    
    dimensions = dim;
    
    // instantiate agent
    DirtSensor* dirtSensorPtr;
    LocationSensor* locationSensorPtr;
    
    int a = sizeof(sensors);
    int b = sizeof(sensors[0]);
    
    for (const char &i : sensors)
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
    
    while (dimensions[agentLocation[0]][agentLocation[1]]==-1) {
        agentLocation[0] = rand()%x;
        agentLocation[1] = rand()%y;
    }
    
    agent.construct(agentLocation, locationSensorPtr, dirtSensorPtr, strategy);
    
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if (dimensions[i][j]==0) dimensions[i][j] = bool(rand()%2);
        }
    };
    
    currentDirt = dimensions[agentLocation[0]][agentLocation[1]];
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
        cout << "Current Location: " << agentLocation[0] << " " << agentLocation[1] << endl;
        cout << "Map: " << endl;
        for (auto const& value: dimensions)
        {
            for (auto const& i: value)
            {
                cout << i;
            }
            cout << endl;
        }
    }
}

void Environment::updateEnvironment(char action, int location[2])
{
    int y = dimensions.size();
    int x = dimensions[0].size();
    
    switch (action) {
        case 'l':
            if (location[1]!=0 && dimensions[location[0]][location[1]-1]!=-1)
                agentLocation[1] -=1;
        case 'r':
            if (location[1]!=y && dimensions[location[0]][location[1]+1]!=-1)
                agentLocation[1] +=1;
        case 'u':
            if (location[0]!=0 && dimensions[location[0]-1][location[1]]!=-1)
                agentLocation[0] -=1;
        case 'd':
            if (location[0]!=x && dimensions[location[0]+1][location[1]]!=-1)
                agentLocation[0] +=1;
        case 'n':
        case 's': dimensions[agentLocation[0]][agentLocation[1]] = 0;
    }
    
    currentDirt = dimensions[agentLocation[0]][agentLocation[1]];
}
