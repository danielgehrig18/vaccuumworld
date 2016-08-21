//
//  simulation.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "simulation.hpp"
#include <iostream>

Simulation::Simulation(vector<vector<int>> dimensions, vector<char> sensors, char strategy)
{
    srand (time(NULL));
    environment.init(dimensions, sensors, strategy);
}

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

void Simulation::reset()
{
    environment.reset();
}
