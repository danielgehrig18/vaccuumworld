//
//  strategy.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 20/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//
#include "vaccuumworld/strategy.hpp"

void Strategy::SetType(char strategy)
{
    type_ = strategy;
}

char Strategy::GetType()
{
    return type_;
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
        case 'a':
            plan_.push(RandomSearch());
            break;
        case 'b':
            plan_.push(GreedySearch(dirt));
            break;
        case 'c':
            plan_.push(MoreGreedySearch(dirt, proximity));
            break;
        case 'd':
            plan_.push(SuperGreedySearch(dirt, proximity, direction));
            break;
        case 'e':
            AddActionSequence(StateSearch(location, state));
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

void Strategy::AddActionSequence(vector<char> sequence)
{
    for (char action : sequence)
    {
        plan_.push(action);
    }
}

vector<char> Strategy::StateSearch(array<int, 2> location, vector<vector<int>> map)
{
    // find closest dirt patches to location
    vector<array<int, 2>> closest_dirt = Model::GetClosestDirt(map, location);
    
    // select random dirt patch and devise plan to clean it.
    array<int, 2> dirt_patch = closest_dirt[rand() % closest_dirt.size()];
    
    cout << "from " << location[0] << " " << location[1] << " to ";
    cout << dirt_patch[0] << ' ' << dirt_patch[1] << endl;
    
    // setup path searcher with goal, initial condition and map of dirt.
    PathSearcher path_searcher;
    path_searcher.Initialize(dirt_patch, location, map);
    
    // search for solution
    path_searcher.Search();
    
    return path_searcher.GetSolution();

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