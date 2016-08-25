//
//  strategy.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 20/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "strategy.hpp"
#include <stdlib.h>

bool Strategy::actionPlanned()
{
    return !plan.empty();
};

void Strategy::planAction(bool dirt, array<bool, 4> proximity, array<bool, 4> direction,
                            array<int, 2> location, vector<vector<int>> state)
{
    switch (type) {
        case 'r': plan.push(randomSearch()); break;
        case 'g': plan.push(greedySearch(dirt)); break;
        case 'h': plan.push(moreGreedySearch(dirt, proximity)); break;
        case 'i': plan.push(superGreedySearch(dirt, proximity, direction)); break;
        case 's': for (char a: stateSearch(location, state)) plan.push(a);
            break;
        default: plan.push('n');
            break;
    }
}

char Strategy::executeAction()
{
    char action = plan.front();
    plan.pop();
    return action;
};

vector<char> Strategy::stateSearch(array<int,2> location, vector<vector<int>> map)
{
    // find closest dirt patches to location
    vector<array<int, 2>> closestDirt;
    int closestDistance=-1;
    
    for (int i=0; i<map.size(); i++)
    {
        for (int j=0; j<map[0].size(); j++)
        {
            if (map[i][j] == 1)
            {
                int distance = abs(location[0]-i) + abs(location[1]-j);
                
                if (distance == closestDistance)
                    closestDirt.push_back({(i-location[0]), (j-location[1])});
                
                else if (distance < closestDistance || closestDistance == -1)
                {
                    closestDirt.clear();
                    closestDirt.push_back({(i-location[0]), (j-location[1])});
                    closestDistance = distance;
                }
            }
        }
    }
    
    // select random dirt patch and devise plan to clean it.
    array<int, 2> dirtPatch = closestDirt[rand()%closestDirt.size()];
    return pathSearch(dirtPatch, location, map);
}


char Strategy::randomSearch()
{
    return actions[rand()%5];
}

char Strategy::greedySearch(bool dirt)
{
    if (dirt) return 's';
    else return actions[rand()%4];
}

char Strategy::moreGreedySearch(bool dirt, array<bool, 4> proximity)
{
    if (dirt) return 's';
    else {
        vector<int> possibleActions;
        for (int i=0; i<proximity.size(); i++) if (!proximity[i]) possibleActions.push_back(i);
        int randIndex = rand()%possibleActions.size();
        return actions[possibleActions[randIndex]];
    }
    return 'n';
}

char Strategy::superGreedySearch(bool dirt, array<bool, 4> proximity, array<bool, 4> direction)
{
    array<bool, 4> combinedConstraint;
    if (dirt) return 's';
    vector<int> possibleActions;
    vector<int> bestActions;
    for (int i=0; i<proximity.size();i++)
    {
        if (direction[i]&&!proximity[i]) bestActions.push_back(i);
        if (!proximity[i]) possibleActions.push_back(i);
    }
    int x = bestActions.size();
    if (x==0) return actions[possibleActions[rand()%possibleActions.size()]];
    else return actions[bestActions[rand()%x]];
    
}

void Strategy::setType(char strategy)
{
    type = strategy;
}

vector<char> Strategy::pathSearch(array<int,2> dirtPatch, array<int,2> location,
                                  vector<vector<int>> map)
{
    pathSearcher.init(dirtPatch, location, map);
    pathSearcher.search();
    return pathSearcher.getSolution();
}