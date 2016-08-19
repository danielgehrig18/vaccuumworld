//
//  simulation.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "simulation.hpp"
#include <iostream>

void Simulation::run(int timeSteps, bool visual)
{
    for (int i=0; i<timeSteps; i++)
    {
        if (visual)
        {
            cout << "----------------------------" << endl;
            cout << "step " << i + 1 << endl;
        }
        environment.step(visual);
        payoff += problem.calculatePayoff(environment);
    }
}
