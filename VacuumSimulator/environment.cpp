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

void Environment::init(vector<vector<int>> dim, vector<char> sensors, char strategy)
{
    dimensions = dim;
    
    // instantiate agent
    DirtSensor* dirtSensorPtr;
    ProximitySensor* proximitySensorPtr;
    
    for (const char i : sensors)
    {
        
        // instantiate sensors
        switch (i) {
            case 'd':
                dirtSensorPtr = &dirtSensor;
                dirtSensorPtr->init();
                break;
            case 'p':
                proximitySensorPtr = &proximitySensor;
                proximitySensorPtr->init();
  
        }
    };
    
    agent.init(dirtSensorPtr, proximitySensorPtr, strategy);
    
    reset();
}

void Environment::updateSensors(bool dirt, array<bool, 4> walls)
{
    dirtSensor.setValue(dirt);
    proximitySensor.setValue(walls);
}

void Environment::step(bool visual)
{
    int x = dimensions.size();
    int y = dimensions[0].size();
    
    if (visual)
    {
        cout << "BEFORE SENSING: " << endl;
        cout << "Sensors: " << "dirt: " << dirtSensor.getValue();
    }
    // updates sensors based on true dirt and location
    updateSensors(currentDirt, walls);
    
    if (visual)
    {
        cout << "AFTER SENSING: " << endl;
        cout << "Sensors: " << "dirt: " << dirtSensor.getValue();
    }
    
    // agent makes decision depending on sensor reading
    char action = agent.actionSelection();
    
    if (visual)
    {
        cout << "ACTION SELECTION: --> action: " << action <<  endl;
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
    
    // set wall presence
    walls = model.getProximity(dimensions, agentLocation);
}

void Environment::reset()
{
    int x = dimensions.size();
    int y = dimensions[0].size();

    // set initialCoords of agent.
    agentLocation[0] = rand()%x;
    agentLocation[1] = rand()%y;
    
    while (dimensions[agentLocation[0]][agentLocation[1]]==-1) {
        agentLocation[0] = rand()%x;
        agentLocation[1] = rand()%y;
    }
    
    // set dirt locations
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if (dimensions[i][j]==0) dimensions[i][j] = rand()%2;
        }
    };
    
    currentDirt = dimensions[agentLocation[0]][agentLocation[1]];
    
    // set wall presence
    walls = model.getProximity(dimensions, agentLocation);
}
