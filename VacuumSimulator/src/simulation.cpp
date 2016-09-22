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
    environment_.Initialize(map, sensors, actuators, visualizer);
}

float Simulation::GetPenalty()
{
    return penalty_;
}

int Simulation::GetCompletionSteps()
{
    return completion_steps_;
}

void Simulation::Run()
{
    int counter = 0;
    
    if (visualizer_.visualize_)
    {
        visualizer_.VisualizeMap(environment_.GetMap(),
                                environment_.GetAgentLocation());
    }
    while (!problem_.GoalTest(environment_))
    {
        if (visualizer_.visualize_)
        {
            cout << "--- step " << counter + 1 << " ---" << endl;
        }
        
        environment_.Step();
        penalty_ += problem_.CalculatePenalty(environment_);
        counter ++;
    }
    if (visualizer_.visualize_)
    {
        cout << "*** Completion in " << counter << " steps. ***" << endl;
    }
    completion_steps_ = counter;
}

void Simulation::Reset()
{
    penalty_ = 0;
    completion_steps_ = -1;
    environment_.Reset();
}