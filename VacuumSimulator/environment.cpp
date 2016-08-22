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
    DirectionSensor* directionSensorPtr;
    LocationSensor* locationSensorPtr;
    
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
                break;
            case 'r': // richtung
                directionSensorPtr = &directionSensor;
                directionSensorPtr->init();
                break;
            case 'l':
                locationSensorPtr = &locationSensor;
                locationSensorPtr->init();
                break;
        }
    };
    
    agent.init(dirtSensorPtr, proximitySensorPtr, directionSensorPtr,
               locationSensorPtr, dimensions, strategy);
    
    reset();
}

void Environment::updateSensors(bool dirt, array<bool, 4> walls,
                                array<bool, 4> directions, array<int, 2> location )
{
    dirtSensor.setValue(dirt);
    proximitySensor.setValue(walls);
    directionSensor.setValue(directions);
    locationSensor.setValue(location);
}

void Environment::step(bool visual)
{
    // updates sensors based on true dirt and location
    updateSensors(currentDirt, walls, directions, agentLocation);
    
    if (visual)
    {
        array<char, 4> directions = {'u', 'r', 'd', 'l'};
        array<bool, 4> prox = proximitySensor.getValue();
        cout << "Sensors: " << "dirt: " << dirtSensor.getValue();
        cout << " Proximity: ";
        for (int i=0; i<directions.size(); i++) if (prox[i]) cout << directions[i];
    }
    
    // agent makes decision depending on sensor reading
    char action = agent.actionSelection();
    
    if (visual)
    {
        cout <<endl<< "--> action: " << action <<  endl;
    }
    
    // environment updated based on action and true location of agent.
    updateEnvironment(action, agentLocation);
    
    // display map
    if (visual)
    {
        cout << "MAP AFTER ACTION: " << endl;
        for (int i=0; i<dimensions.size(); i++)
        {
            for (int j=0; j<dimensions[0].size(); j++)
            {
                if (agentLocation[0] == i && agentLocation[1] == j)
                {
                    if (dimensions[i][j] == 0)
                    {
                        cout << 'Q';
                    }
                    else cout << 'J';
                }
                else if (dimensions[i][j]==-1) cout <<'x';
                else cout << dimensions[i][j];
            }
            cout << endl;
        }
    }
}

void Environment::updateEnvironment(char action, array<int, 2> location)
{
    // get new location
    agentLocation = model.getNewLocation(action, location, dimensions);
    
    // update dirt
    if (action=='s') dimensions[agentLocation[0]][agentLocation[1]] = false;
    
    currentDirt = dimensions[agentLocation[0]][agentLocation[1]];
    
    // set wall presence
    walls = model.getProximity(dimensions, agentLocation);
    
    // set new directions
    directions = model.getDirections(dimensions, agentLocation);
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
    
    // get currentDirt
    currentDirt = model.getDirt(dimensions, agentLocation);
    
    // set wall presence
    walls = model.getProximity(dimensions, agentLocation);
    
    // set directions
    directions = model.getDirections(dimensions, agentLocation);
    
    //
}
