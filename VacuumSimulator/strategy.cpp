//
//  strategy.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 20/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "strategy.hpp"
#include <stdlib.h>

char Strategy::chooseAction(bool dirt, array<bool, 4> proximity)
{
    switch (type) {
        case 'r':
            return randomSearch();
        case 'g':
            return greedySearch(dirt);
        case 'h':
            return moreGreedySearch(dirt, proximity);
        default: return 'n';
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

void Strategy::setType(char strategy)
{
    type = strategy;
}