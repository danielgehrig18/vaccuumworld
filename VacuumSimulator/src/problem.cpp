//
//  problem.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 19/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/problem.hpp"

int Problem::CalculatePenalty(Environment environment)
{
    int penalty=0;
    vector<vector<int>> map = environment.GetMap();
    
    // count dirty spots
    for (vector<int> x_column : map)
    {
        for (int spot : x_column)
        {
            if (spot == 1)
            {
                penalty += dirt_spot_cost_;
            }
        }
    }
    
    return penalty;
}

bool Problem::GoalTest(Environment environment)
{
    vector<vector<int>> map = environment.GetMap();
    
    // return false if any spot is dirty
    for (vector<int> x_column : map)
    {
        for (int spot : x_column)
        {
            if (spot == 1)
            {
                return false;
            }
        }
    }
    
    return true;
}