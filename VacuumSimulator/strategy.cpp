//
//  strategy.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 20/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "strategy.hpp"
#include <stdlib.h>

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

vector<char> Strategy::stateSearch(array<int,2> location, vector<vector<int>> state)
{
    return {'n'};
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