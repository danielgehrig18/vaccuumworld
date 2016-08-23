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

void Simulation::run(bool visual)
{
    int counter = 0;
    while (!problem.goalTest(environment))
    {
        if (visual) cout << "--- step " << counter + 1 << " ---" << endl;
        
        environment.step(visual);
        penalty += problem.calculatePenalty(environment);
        counter++;
    }
    if (visual) cout << "*** Completion in " << counter << " steps. ***" << endl;
    completionSteps = counter;
}

void Simulation::reset()
{
    penalty = 0;
    completionSteps = -1;
    environment.reset();
}
