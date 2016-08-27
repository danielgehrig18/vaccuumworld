//
//  environment.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include <iostream>

#include "environment.hpp"
#include "visualizer.hpp"

using namespace std;

vector<vector<int>> Environment::getMap()
{
    return map;
};

array<int, 2> Environment::getAgentLocation()
{
    return agentLocation;
};

void Environment::init(vector<vector<int>> dim, vector<char> sensors, char strategy)
{
    map = dim;
    
    // instantiate sensors
    for (char i : sensors)
    {
        switch (i)
        {
            case 'd':
                dirtSensor.init();
                break;
            case 'p':
                proximitySensor.init();
                break;
            case 'r': // richtung
                directionSensor.init();
                break;
            case 'l':
                locationSensor.init();
                break;
        }
    };
    
    // instantiate agent
    agent.init(&dirtSensor, &proximitySensor, &directionSensor,
               &locationSensor, map, strategy);
    
    // randomize agent position and map and update environment states.
    reset();
}

void Environment::step(bool visual)
{
    // updates and visualizes sensors based on true dirt and location
    updateSensors(currentDirt, walls, directions, agentLocation);
    if (visual)
    {
        Visualizer::visualizeSensors(dirtSensor.getValue(),
                                     proximitySensor.getValue(),
                                     directionSensor.getValue(),
                                     locationSensor.getValue());
    }

    // agent makes decision depending on sensor reading
    char action = agent.actionSelection();
    
    if (visual)
    {
        Visualizer::visualizeAction(action);
    }
    
    // environment updated based on action and true location of agent.
    updateEnvironment(action, agentLocation);
    
    // display map
    if (visual)
    {
        Visualizer::visualizeMap(map, agentLocation);
    }
}

void Environment::reset()
{
    int x = map.size();
    int y = map[0].size();
    
    // set initialCoords of agent.
    agentLocation[0] = rand() % x;
    agentLocation[1] = rand() % y;
    
    while (map[agentLocation[0]][agentLocation[1]] == -1)
    {
        agentLocation[0] = rand() % x;
        agentLocation[1] = rand() % y;
    }
    
    // set dirt locations
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if (map[i][j]==0) map[i][j] = rand()%2;
        }
    };
    
    // get currentDirt
    currentDirt = model.getDirt(map, agentLocation);
    
    // set wall presence
    walls = model.getProximity(map, agentLocation);
    
    // set directions
    directions = model.getDirections(map, agentLocation);
    
}

void Environment::updateSensors(bool dirt, array<bool, 4> walls,
                                array<bool, 4> directions, array<int, 2> location)
{
    dirtSensor.setValue(dirt);
    proximitySensor.setValue(walls);
    directionSensor.setValue(directions);
    locationSensor.setValue(location);
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