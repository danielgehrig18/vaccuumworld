//
//  simulation.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include <iostream>

#include "simulation.hpp"
#include "visualizer.hpp"

Simulation::Simulation(vector<vector<int>> map, vector<char> sensors,
                       char strategy, bool visual)
{
    srand (time(NULL));
    environment.init(map, sensors, strategy);
    visualize = visual;
}

float Simulation::getPenalty()
{
    return penalty;
}

int Simulation::getCompletionSteps()
{
    return completionSteps;
}

void Simulation::run()
{
    int counter = 0;
    
    if (visualize)
    {
        Visualizer::visualizeMap(environment.getMap(),
                                environment.getAgentLocation());
    }
    while (!problem.goalTest(environment))
    {
        if (visualize)
        {
            cout << "--- step " << counter + 1 << " ---" << endl;
        }
        
        environment.step(visualize);
        penalty += problem.calculatePenalty(environment);
        counter ++;
    }
    if (visualize)
    {
        cout << "*** Completion in " << counter << " steps. ***" << endl;
    }
    completionSteps = counter;
}

void Simulation::reset()
{
    penalty = 0;
    completionSteps = -1;
    environment.reset();
}
