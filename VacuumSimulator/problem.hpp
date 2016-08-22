//
//  problem.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 19/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef problem_hpp
#define problem_hpp

#include <stdio.h>

#include "environment.hpp"

class Problem
{
private:
    int dirtSpotCost = 1;
public:
    int calculatePenalty(Environment environment);
    bool goalTest(Environment environment);
};

#endif /* problem_hpp */
