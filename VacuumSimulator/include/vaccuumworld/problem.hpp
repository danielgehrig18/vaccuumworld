//
//  problem.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 19/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef problem_hpp
#define problem_hpp

#include "vaccuumworld/environment.hpp"

class Problem
{
public:
    /**
        Calculates and returns penalty for one step. One point is penalized for 
        every dirty square.
     
        @param: environment: Environment object with true dirt distribution.
    */
    int CalculatePenalty(Environment environment);
    
    /**
        Test if the goal has been achieved. This is when all spots are clean.
     
        @param: environment: Environment object with true dirt distribution.
    */
    bool GoalTest(Environment environment);
    
private:
    int dirt_spot_cost_ = 1;
};

#endif /* problem_hpp */