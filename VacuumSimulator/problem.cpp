//
//  problem.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 19/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "problem.hpp"

int Problem::calculatePayoff(Environment environment)
{
    int payoff;
    bool** grid = environment.getGrid();
    
    for (int i; i<2; i++)
    {
        if (!grid[0][i]) {
            payoff += freeSpotCost;
        }
    }
    return payoff;
}