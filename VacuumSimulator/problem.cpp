//
//  problem.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 19/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "problem.hpp"

int Problem::calculatePenalty(Environment environment)
{
    int penalty=0;
    
    vector<vector<int>> map = environment.getMap();
    
    for (vector<int> a:map) for (int i:a) if (i==1) penalty += dirtSpotCost;
    
    return penalty;
}

bool Problem::goalTest(Environment environment)
{
    vector<vector<int>> map = environment.getMap();
    
    for (vector<int> a:map) for (int i:a) if (i==1) return false;
    
    return true;
}