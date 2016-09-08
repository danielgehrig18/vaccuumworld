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
    return map_;
};

array<int, 2> Environment::getAgentLocation()
{
    return agentLocation_;
};

void Environment::init(vector<vector<int>> dim, vector<char> sensors,
                       vector<char> actuators, Visualizer &visualizer)
{
    visualizer_ = visualizer;
    map_ = dim;
    
    // instantiate sensors
    for (char i : sensors)
    {
        switch (i)
        {
            case 'd':
                dirtSensor_.init();
                break;
            case 'p':
                proximitySensor_.init();
                break;
            case 'r': // richtung
                directionSensor_.init();
                break;
            case 'l':
                locationSensor_.init();
                break;
        }
    };
    
    // instantiate actuators
    for (char i : actuators)
    {
        switch (i)
        {
            case 'm':
                motor_.init(&lastAction_);
                break;
            case 's':
                sucker_.init(&lastAction_);
                break;
        }
    }
    // randomize agent position and map and update environment states.
    reset();
    
    // instantiate agent
    agent.init(&dirtSensor_, &proximitySensor_, &directionSensor_,
               &locationSensor_, &motor_, &sucker_, map_, visualizer_);
}

void Environment::step()
{
    // updates and visualizes sensors based on true dirt and location
    updateSensors(currentDirt_, walls_, directions_, agentLocation_);
    if (visualizer_.visualize_)
    {
        visualizer_.visualizeSensors(dirtSensor_.getValue(),
                                     proximitySensor_.getValue(),
                                     directionSensor_.getValue(),
                                     locationSensor_.getValue());
    }

    // agent makes decision depending on sensor reading
    agent_.executeAction();
    
    if (visualizer_.visualize_)
    {
        visualizer_.visualizeAction(lastAction_);
    }
    
    // environment updated based on action and true location of agent.
    updateEnvironment(lastAction_, agentLocation_);
    
    // display map
    if (visualizer_.visualize_)
    {
        visualizer_.visualizeMap(map_, agentLocation_);
    }
}

void Environment::reset()
{
    int x = map_.size();
    int y = map_[0].size();
    
    // set initialCoords of agent.
    agentLocation_ = {rand() % x, rand() % y};
    
    while (map_[agentLocation_[0]][agentLocation_[1]] == -1)
    {
        agentLocation_ = {rand() % x, rand() % y};
    }
    
    // set dirt locations
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if (map_[i][j]==0) map_[i][j] = rand()%2;
        }
    };
    
    // get currentDirt
    currentDirt_ = model_.getDirt(map_, agentLocation_);
    
    // set wall presence
    walls_ = model_.getProximity(map_, agentLocation_);
    
    // set directions
    directions_ = model_.getDirections(map_, agentLocation_);
    
}

void Environment::updateSensors(bool dirt, array<bool, 4> walls,
                                array<bool, 4> directions, array<int, 2> location)
{
    dirtSensor_.setValue(dirt);
    proximitySensor_.setValue(walls);
    directionSensor_.setValue(directions);
    locationSensor_.setValue(location);
}

void Environment::updateEnvironment(char action, array<int, 2> location)
{
    // get new location
    agentLocation_ = model_.getNewLocation(action, location, map_);
    
    // update map
    map_ = model_.getNewMap(action, location, map_);
    
    // update dirt
    currentDirt_ = model_.getDirt(map_, agentLocation_);
    
    // set wall presence
    walls_ = model_.getProximity(map_, agentLocation_);
    
    // set new directions
    directions_ = model_.getDirections(map_, agentLocation_);
}
