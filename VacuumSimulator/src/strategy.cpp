//
//  strategy.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 20/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//
#include "vaccuumworld/strategy.hpp"

void Strategy::Initialize(Visualizer &visualizer)
{
    visualizer_ = visualizer;
}

void Strategy::SetType(bool dirt_sensor_status, bool proximity_sensor_status,
                       bool direction_sensor_status, bool location_sensor_status,
                       bool motor_status, bool sucker_status)
{
    if (!dirt_sensor_status)
    {
        type_ = 'r';
    }
    else if (dirt_sensor_status && !proximity_sensor_status)
    {
        type_ = 'g';
    }
    else if (dirt_sensor_status && proximity_sensor_status && !direction_sensor_status)
    {
        type_ = 'h';
    }
    else if (dirt_sensor_status && proximity_sensor_status && direction_sensor_status
             && !location_sensor_status)
    {
        type_ = 'i';
    }
    else
    {
        type_ = 's';
    }
}

bool Strategy::ActionPlanned()
{
    return !plan_.empty();
};

void Strategy::PlanAction(bool dirt, array<bool, 4> proximity, array<bool, 4> direction,
                          array<int, 2> location, vector<vector<int>> state)
{
    switch (type_)
    {
        case 'r':
            plan_.push(RandomSearch());
            break;
        case 'g':
            plan_.push(GreedySearch(dirt));
            break;
        case 'h':
            plan_.push(MoreGreedySearch(dirt, proximity));
            break;
        case 'i':
            plan_.push(SuperGreedySearch(dirt, proximity, direction));
            break;
        case 's':
            for (char action : StateSearch(location, state))
            {
                plan_.push(action);
            }
            break;
        default:
            plan_.push('n');
            break;
    }
}

char Strategy::ActionSelection()
{
    char action = plan_.front();
    plan_.pop();
    return action;
};

vector<char> Strategy::StateSearch(array<int, 2> location, vector<vector<int>> map)
{
    // find closest dirt patches to location
    vector<array<int, 2>> closest_dirt = Model::GetClosestDirt(map, location);
    
    // select random dirt patch and devise plan to clean it.
    array<int, 2> dirt_patch = closest_dirt[rand() % closest_dirt.size()];
    
    cout << "from " << location[0] << " " << location[1] << " to ";
    cout << dirt_patch[0] << ' ' << dirt_patch[1] << endl;
    
    // setup path searcher with goal, initial condition and map of dirt.
    path_searcher_.Initialize(dirt_patch, location, map, visualizer_);
    
    // search for solution
    if (path_searcher_.Search())
    {
        return path_searcher_.CalculateSolution();
    }
    else
    {
        return {};
    }
}

char Strategy::SuperGreedySearch(bool dirt, array<bool, 4> proximity,
                                 array<bool, 4> directions)
{
    if (dirt)
    {
        return 's';
    }
    
    vector<int> possible_actions;
    vector<int> best_actions;
    
    for (int direction = 0; direction < proximity.size(); direction++)
    {
        if (directions[direction] && !proximity[direction])
        {
            best_actions.push_back(direction);
        }
        if (!proximity[direction])
        {
            possible_actions.push_back(direction);
        }
    }
    
    if (best_actions.size() == 0)
    {
        return actions_[possible_actions[rand() % possible_actions.size()]];
    }
    else
    {
        return actions_[best_actions[rand() % best_actions.size()]];
    }
    
}

char Strategy::MoreGreedySearch(bool dirt, array<bool, 4> proximity)
{
    if (dirt)
    {
        return 's';
    }
    else
    {
        vector<int> possible_actions;
        
        for (int direction = 0; direction < proximity.size(); direction++)
        {
            if (!proximity[direction])
            {
                possible_actions.push_back(direction);
            }
        }
        
        int random_index = rand() % possible_actions.size();
        
        return actions_[possible_actions[random_index]];
    }
    return 'n';
}

char Strategy::GreedySearch(bool dirt)
{
    if (dirt)
    {
        return 's';
    }
    else
    {
        return actions_[rand() % 4];
    }
}

char Strategy::RandomSearch()
{
    return actions_[rand() % 5];
}