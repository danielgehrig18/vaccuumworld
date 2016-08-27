//
//  strategy.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 20/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include <stdlib.h>

#include "strategy.hpp"
#include "model.hpp"

void Strategy::setType(char strategy)
{
    type = strategy;
}

bool Strategy::actionPlanned()
{
    return !plan.empty();
};

void Strategy::planAction(bool dirt, array<bool, 4> proximity,
                          array<bool, 4> direction, array<int, 2> location,
                          vector<vector<int>> state)
{
    switch (type)
    {
        case 'r':
            plan.push(randomSearch());
            break;
        case 'g':
            plan.push(greedySearch(dirt));
            break;
        case 'h':
            plan.push(moreGreedySearch(dirt, proximity));
            break;
        case 'i':
            plan.push(superGreedySearch(dirt, proximity, direction));
            break;
        case 's':
            for (char a : stateSearch(location, state))
            {
                plan.push(a);
            }
            break;
        default:
            plan.push('n');
            break;
    }
}

char Strategy::executeAction()
{
    char action = plan.front();
    plan.pop();
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
    pathSearcher.init(dirtPatch, location, map);
    
    // search for solution
    pathSearcher.search();
    
    // return solution
    return pathSearcher.getSolution();
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
        return actions[possibleActions[rand() % possibleActions.size()]];
    }
    else
    {
        return actions[bestActions[rand() % bestActions.size()]];
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
        
        return actions[possibleActions[randIndex]];
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
        return actions[rand() % 4];
    }
}

char Strategy::randomSearch()
{
    return actions[rand() % 5];
}