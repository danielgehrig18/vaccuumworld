//
//  environment.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//
#include "vaccuumworld/environment.hpp"

using namespace std;

vector<vector<int>> Environment::getMap()
{
    return map;
};

array<int, 2> Environment::getAgentLocation()
{
    return agentLocation;
};

void Environment::init(vector<vector<int>> dim, vector<char> sensors,
                       vector<char> actuators)
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
    
    // instantiate actuators
    for (char i : actuators)
    {
        switch (i)
        {
            case 'm':
                motor.init(&lastAction);
                break;
            case 's':
                sucker.init(&lastAction);
                break;
        }
    }
    // randomize agent position and map and update environment states.
    reset();
    
    // instantiate agent
    agent.init(&dirtSensor, &proximitySensor, &directionSensor,
               &locationSensor, &motor, &sucker, map);
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
    agent.executeAction();
    
    if (visual)
    {
        Visualizer::visualizeAction(lastAction);
    }
    
    // environment updated based on action and true location of agent.
    updateEnvironment(lastAction, agentLocation);
    
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
    agentLocation = {rand() % x, rand() % y};
    
    while (map[agentLocation[0]][agentLocation[1]] == -1)
    {
        agentLocation = {rand() % x, rand() % y};
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
