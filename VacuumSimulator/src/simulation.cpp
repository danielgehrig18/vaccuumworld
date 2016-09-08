//
//  simulation.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//
#include "vaccuumworld/simulation.hpp"

Simulation::Simulation(vector<vector<int>> map, vector<char> sensors,
                       vector<char> actuators)
{
    srand (time(NULL));
    environment.init(map, sensors, actuators);
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
    
    if (Visualizer::visualize)
    {
        Visualizer::visualizeMap(environment.getMap(),
                                environment.getAgentLocation());
    }
    while (!problem.goalTest(environment))
    {
        if (Visualizer::visualize)
        {
            cout << "--- step " << counter + 1 << " ---" << endl;
        }
        
        environment.step();
        penalty += problem.calculatePenalty(environment);
        counter ++;
    }
    if (Visualizer::visualize)
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
