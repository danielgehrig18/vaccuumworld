//
//  environment.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//
#include "vaccuumworld/environment.hpp"

using namespace std;

vector<vector<int>> Environment::GetMap()
{
    return map_;
};

array<int, 2> Environment::GetAgentLocation()
{
    return agent_location_;
};

void Environment::Initialize(vector<vector<int> > map, vector<char> sensors,
                             vector<char> actuators, Visualizer &visualizer)
{
    visualizer_ = visualizer;
    map_ = map;
    
    // instantiate sensors
    for (char sensor_name : sensors)
    {
        switch (sensor_name)
        {
            case 'd':
                dirt_sensor_.Initialize();
                break;
            case 'p':
                proximity_sensor_.Initialize();
                break;
            case 'r': // richtung
                direction_sensor_.Initialize();
                break;
            case 'l':
                location_sensor_.Initialize();
                break;
        }
    };
    
    // instantiate actuators
    for (char actuator : actuators)
    {
        switch (actuator)
        {
            case 'm':
                motor_.Initialize(&last_action_);
                break;
            case 's':
                sucker_.Initialize(&last_action_);
                break;
        }
    }
    // randomize agent position and map and update environment states.
    Reset();
    
    // instantiate agent
    agent_.Initialize(&dirt_sensor_, &proximity_sensor_, &direction_sensor_,
                      &location_sensor_, &motor_, &sucker_, map_, visualizer_);
}

void Environment::Step()
{
    // updates and visualizes sensors based on true dirt and location
    UpdateSensors(current_dirt_, walls_, directions_, agent_location_);
    
    if (visualizer_.visualize_)
    {
        visualizer_.VisualizeSensors(dirt_sensor_.GetValue(),
                                     proximity_sensor_.GetValue(),
                                     direction_sensor_.GetValue(),
                                     location_sensor_.GetValue());
    }

    // agent makes decision depending on sensor reading
    agent_.ExecuteAction();
    
    if (visualizer_.visualize_)
    {
        visualizer_.VisualizeAction(last_action_);
    }
    
    // environment updated based on action and true location of agent.
    UpdateEnvironment(last_action_, agent_location_);
    
    // display map
    if (visualizer_.visualize_)
    {
        visualizer_.VisualizeMap(map_, agent_location_);
    }
}

void Environment::Reset()
{
    int x_dimension = map_.size();
    int y_dimension = map_[0].size();
    
    // set initialCoords of agent.
    agent_location_ = {rand() % x_dimension, rand() % y_dimension};
    
    while (map_[agent_location_[0]][agent_location_[1]] == -1)
    {
        agent_location_ = {rand() % x_dimension, rand() % y_dimension};
    }
    
    // set dirt locations
    for (int x_coordinate = 0; x_coordinate < x_dimension; x_coordinate++)
    {
        for (int y_coordinate = 0; y_coordinate < y_dimension; y_coordinate++)
        {
            if (map_[x_coordinate][y_coordinate] == 0)
            {
                map_[x_coordinate][y_coordinate] = rand() % 2;
            }
        }
    };
    
    // get currentDirt
    current_dirt_ = model_.GetDirt(map_, agent_location_);
    
    // set wall presence
    walls_ = model_.GetProximity(map_, agent_location_);
    
    // set directions
    directions_ = model_.GetDirections(map_, agent_location_);
}

void Environment::UpdateSensors(bool dirt, array<bool, 4> walls,
                                array<bool, 4> directions, array<int, 2> location)
{
    dirt_sensor_.SetValue(dirt);
    proximity_sensor_.SetValue(walls);
    direction_sensor_.SetValue(directions);
    location_sensor_.SetValue(location);
}

void Environment::UpdateEnvironment(char action, array<int, 2> location)
{
    // gets new location
    model_.UpdateLocation(action, agent_location_, map_);
    
    // updates map
    model_.UpdateMap(action, location, map_);
    
    // updates dirt
    current_dirt_ = model_.GetDirt(map_, agent_location_);
    
    // sets wall presence
    walls_ = model_.GetProximity(map_, agent_location_);
    
    // sets new directions
    directions_ = model_.GetDirections(map_, agent_location_);
}