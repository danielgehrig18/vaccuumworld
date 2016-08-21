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
    
    unsigned long int x = dim.size();
    unsigned long int y = dim[0].size();
    
    dimensions = dim;
    
    // instantiate agent
    DirtSensor* dirtSensorPtr;
    LocationSensor* locationSensorPtr;
    
    for (const char i : sensors)
    {
        
        // instantiate sensors
        if (i == 'd')
        {
            dirtSensorPtr = &dirtSensor;
        }
        else
        {
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

void Environment::updateSensors(bool dirt, array<int, 2> location)
{
    dirtSensor.setValue(dirt);
    locationSensor.setValue(location);
}

void Environment::step(bool visual)
{
    int x = dimensions.size();
    int y = dimensions[0].size();
    
    if (visual)
    {
        array<int, 2> loc = locationSensor.getValue();
        cout << "BEFORE SENSING: " << endl;
        cout << "Sensors: " << "dirt: " << dirtSensor.getValue();
        cout << " location: " << loc[0] << " " << loc[1] << endl;
    }
    // updates sensors based on true dirt and location
    updateSensors(currentDirt, agentLocation);
    
    if (visual)
    {
        array<int, 2> loc = locationSensor.getValue();
        cout << "AFTER SENSING: " << endl;
        cout << "Sensors: " << "dirt: " << dirtSensor.getValue();
        cout << " location: " << loc[0] << " " << loc[1] << endl;
    }
    
    // agent makes decision depending on sensor reading
    char action = agent.actionSelection();
    
    if (visual)
    {
        cout << "ACTION SELECTION: " << endl;
        cout << "--> action: " << action <<  endl;
    }
    
    // environment updated based on action and true location of agent.
    updateEnvironment(action, agentLocation);
    
    
    if (visual)
    {

        cout << "MAP AFTER ACTION: " << endl;
        for (int i=0; i<x; i++)
        {
            for (int j=0; j<y; j++)
            {
                if (agentLocation[0] == i && agentLocation[1] == j)
                {
                    if (dimensions[i][j] == 0)
                    {
                        cout << 'Q';
                    }
                    else cout << 'J';
                }
                else cout << dimensions[i][j];
            }
            cout << endl;
        }
    }
}

void Environment::updateEnvironment(char action, array<int, 2> location)
{
    int x = dimensions.size();
    int y = dimensions[0].size();
    
    switch (action) {
        case 'l':
            if (location[1]!=0) if(dimensions[location[0]][location[1]-1]!=-1)
                agentLocation[1] -=1;
            break;
        case 'r':
            if (location[1]!=y-1) if(dimensions[location[0]][location[1]+1]!=-1)
                agentLocation[1] +=1;
            break;
        case 'u':
            if (location[0]!=0) if (dimensions[location[0]-1][location[1]]!=-1)
                agentLocation[0] -=1;
            break;
        case 'd':
            if (location[0]!=x-1) if(dimensions[location[0]+1][location[1]]!=-1)
                agentLocation[0] +=1;
            break;
        case 'n': break;
        case 's': dimensions[agentLocation[0]][agentLocation[1]] = 0;
            break;
    }
    
    currentDirt = dimensions[agentLocation[0]][agentLocation[1]];
}
