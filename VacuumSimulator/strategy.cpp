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
        int randIndex = rand()%proximity.size();
        while (proximity[randIndex]) {randIndex = rand()%proximity.size();}
        return actions[randIndex];
    }
    return 'n';
}

char Strategy::superGreedySearch(bool dirt, array<bool, 4> proximity, array<bool, 4> direction)
{
    return 'n';
}

vector<char> stateSearch(array<int, 2> location, vector<vector<int>> state)
{
    return vector<char> {'n'};
}

void Strategy::setType(char strategy)
{
    type = strategy;
}