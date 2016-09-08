//
//  simulation.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//
#include "vaccuumworld/simulation.hpp"

Simulation::Simulation(vector<vector<int>> map, vector<char> sensors,
                       vector<char> actuators, Visualizer &visualizer)
{
    srand (time(NULL));
    visualizer_ = visualizer;
    environment_.init(map, sensors, actuators, visualizer);
}

float Simulation::getPenalty()
{
    return penalty_;
}

int Simulation::getCompletionSteps()
{
    return completionSteps_;
}

void Simulation::run()
{
    int counter = 0;
    
    if (visualizer_.visualize_)
    {
        visualizer_.visualizeMap(environment_.getMap(),
                                environment_.getAgentLocation());
    }
    while (!problem_.goalTest(environment_))
    {
        if (visualizer_.visualize_)
        {
            cout << "--- step " << counter + 1 << " ---" << endl;
        }
        
        environment_.step();
        penalty_ += problem_.calculatePenalty(environment_);
        counter ++;
    }
    if (visualizer_.visualize_)
    {
        cout << "*** Completion in " << counter << " steps. ***" << endl;
    }
    completionSteps_ = counter;
}

void Simulation::reset()
{
    penalty_ = 0;
    completionSteps_ = -1;
    environment_.reset();
}
