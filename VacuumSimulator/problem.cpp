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
    
    for (vector<int> a:dimensions) for (int i:a) if (i==0) payoff += freeSpotCost;
    
    return payoff;
}

bool Problem::goalTest(Environment environment)
{
    vector<vector<int>> dimensions = environment.getDimensions();
    
    for (vector<int> a:dimensions) for (int i:a) if (i) return false;
    
    return true;
}