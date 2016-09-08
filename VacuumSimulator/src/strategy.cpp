//
//  strategy.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 20/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//
#include "vaccuumworld/strategy.hpp"

void Strategy::init(Visualizer &visualizer)
{
    visualizer_ = visualizer;
}

void Strategy::setType(bool DSStatus, bool PSStatus, bool DirSStatus,
                       bool LSStatus, bool MStatus, bool SStatus)
{
    if (!DSStatus)
    {
        type_ = 'r';
    }
    else if (DSStatus && !PSStatus)
    {
        type_ = 'g';
    }
    else if (DSStatus && PSStatus && !DirSStatus)
    {
        type_ = 'h';
    }
    else if (DSStatus && PSStatus && DirSStatus && !LSStatus)
    {
        type_ = 'i';
    }
    else
    {
        type_ = 's';
    }
}

bool Strategy::actionPlanned()
{
    return !plan_.empty();
};

void Strategy::planAction(bool dirt, array<bool, 4> proximity,
                          array<bool, 4> direction, array<int, 2> location,
                          vector<vector<int>> state)
{
    switch (type_)
    {
        case 'r':
            plan_.push(randomSearch());
            break;
        case 'g':
            plan_.push(greedySearch(dirt));
            break;
        case 'h':
            plan_.push(moreGreedySearch(dirt, proximity));
            break;
        case 'i':
            plan_.push(superGreedySearch(dirt, proximity, direction));
            break;
        case 's':
            for (char a : stateSearch(location, state))
            {
                plan_.push(a);
            }
            break;
        default:
            plan_.push('n');
            break;
    }
}

char Strategy::actionSelection()
{
    char action = plan_.front();
    plan_.pop();
    return action;
};

vector<char> Strategy::stateSearch(array<int, 2> location,
                                   vector<vector<int>> map)
{
    // find closest dirt patches to location
    vector<array<int, 2>> closestDirt = Model::getClosestDirt(map, location);
    
    // select random dirt patch and devise plan to clean it.
    array<int, 2> dirtPatch = closestDirt[rand() % closestDirt.size()];
    
    // setup path searcher with goal, initial condition and map of dirt.
    pathSearcher_.init(dirtPatch, location, map, visualizer_);
    
    // search for solution
    if (pathSearcher_.search())
    {
        return pathSearcher_.getSolution();
    }
    else
    {
        return {};
    }
}

char Strategy::superGreedySearch(bool dirt, array<bool, 4> proximity,
                                 array<bool, 4> direction)
{
    if (dirt)
    {
        return 's';
    }
    
    vector<int> possibleActions;
    vector<int> bestActions;
    
    for (int i = 0; i < proximity.size(); i++)
    {
        if (direction[i] && !proximity[i])
        {
            bestActions.push_back(i);
        }
        if (!proximity[i])
        {
            possibleActions.push_back(i);
        }
    }
    
    if (bestActions.size() == 0)
    {
        return actions_[possibleActions[rand() % possibleActions.size()]];
    }
    else
    {
        return actions_[bestActions[rand() % bestActions.size()]];
    }
    
}

char Strategy::moreGreedySearch(bool dirt, array<bool, 4> proximity)
{
    if (dirt)
    {
        return 's';
    }
    else
    {
        vector<int> possibleActions;
        
        for (int i = 0; i < proximity.size(); i++)
        {
            if (!proximity[i])
            {
                possibleActions.push_back(i);
            }
        }
        
        int randIndex = rand() % possibleActions.size();
        
        return actions_[possibleActions[randIndex]];
    }
    return 'n';
}

char Strategy::greedySearch(bool dirt)
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

char Strategy::randomSearch()
{
    return actions_[rand() % 5];
}
