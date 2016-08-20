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
    int payoff=0;
    vector<vector<int>> dimensions = environment.getDimensions();
    
    int y = sizeof(dimensions[0])/sizeof(dimensions[0][0]);
    int x = sizeof(dimensions)/(y*sizeof(dimensions[0][0]));
    
    for (int i=0; i<x; i++)
    {
        for (int j=0; j<y; j++)
        {
            if (dimensions[i][j]!=0) {
                payoff += freeSpotCost;
            }
        }
    }
    return payoff;
}