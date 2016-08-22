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
    int freeSpotCost = 1;
public:
    int calculatePayoff(Environment environment);
    bool goalTest(Environment environment);
};

#endif /* problem_hpp */
