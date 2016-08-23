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
    map = dim;
    
    // instantiate sensors
    DirtSensor* dirtSensorPtr;
    ProximitySensor* proximitySensorPtr;
    DirectionSensor* directionSensorPtr;
    LocationSensor* locationSensorPtr;
    
    for (const char i : sensors)
    {
        
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
    
    // instantiate agent
    agent.init(dirtSensorPtr, proximitySensorPtr, directionSensorPtr,
               locationSensorPtr, map, strategy);
    
    // randomize agent position and map and update environment states.
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
        array<bool, 4> richtungen = directionSensor.getValue();
        
        cout << "Sensors: " << "dirt: " << dirtSensor.getValue();
        cout << " Proximity: ";
        for (int i=0; i<directions.size(); i++) if (prox[i]) cout << directions[i];
        cout << " Directions: ";
        for (int i=0; i<directions.size(); i++) if (richtungen[i]) cout << directions[i];
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
        for (int i=0; i<map.size(); i++)
        {
            for (int j=0; j<map[0].size(); j++)
            {
                if (agentLocation[0] == i && agentLocation[1] == j)
                {
                    if (map[i][j] == 0)
                    {
                        cout << 'Q';
                    }
                    else cout << 'J';
                }
                else if (map[i][j]==-1) cout <<'x';
                else cout << map[i][j];
            }
            cout << endl;
        }
    }
}

void Environment::updateEnvironment(char action, array<int, 2> location)
{
    // get new location
    agentLocation = model.getNewLocation(action, location, map);
    
    // update map
    map = model.getNewMap(action, location, map);
    
    // update dirt
    currentDirt = model.getDirt(map, agentLocation);
    
    // set wall presence
    walls = model.getProximity(map, agentLocation);
    
    // set new directions
    directions = model.getDirections(map, agentLocation);
}

void Environment::reset()
{
    int x = map.size();
    int y = map[0].size();

    // set initialCoords of agent.
    agentLocation[0] = rand()%x;
    agentLocation[1] = rand()%y;
    
    while (map[agentLocation[0]][agentLocation[1]]==-1) {
        agentLocation[0] = rand()%x;
        agentLocation[1] = rand()%y;
    }
    
    // set dirt locations
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if (map[i][j]==0) map[i][j] = rand()%2;
        }
    };
    
    // display map
    if (true){
        cout << "MAP: " << endl;
        for (int i=0; i<map.size(); i++)
        {
            for (int j=0; j<map[0].size(); j++)
            {
                if (agentLocation[0] == i && agentLocation[1] == j)
                {
                    if (map[i][j] == 0) cout << 'Q'; else cout << 'J';
                }
                else if (map[i][j]==-1) cout <<'x';
                else cout << map[i][j];
            }
            cout << endl;
        }
    }
    
    // get currentDirt
    currentDirt = model.getDirt(map, agentLocation);
    
    // set wall presence
    walls = model.getProximity(map, agentLocation);
    
    // set directions
    directions = model.getDirections(map, agentLocation);
    
}
