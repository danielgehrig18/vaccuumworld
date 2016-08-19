//
//  simulation.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "simulation.hpp"

void Simulation::run(int timeSteps, bool visual)
{
    for (int i; i<timeSteps; i++)
    {
        environment.step();
        payoff += problem.calculatePayoff(environment);
    }
}
