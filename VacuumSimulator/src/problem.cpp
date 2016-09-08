//
//  problem.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 19/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/problem.hpp"

int Problem::calculatePenalty(Environment environment)
{
    int penalty=0;
    vector<vector<int>> map = environment.getMap();
    
    // count dirty spots
    for (vector<int> a : map)
    {
        for (int spot : a)
        {
            if (spot == 1) penalty += dirtSpotCost_;
        }
    }
    
    return penalty;
}

bool Problem::goalTest(Environment environment)
{
    vector<vector<int>> map = environment.getMap();
    
    // return false if any spot is dirty
    for (vector<int> a : map)
    {
        for (int i : a)
        {
            if (i == 1) return false;
        }
    }
    
    return true;
}
