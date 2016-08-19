//
//  simulation.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef simulation_hpp
#define simulation_hpp

#include <stdio.h>
#include "environment.hpp"
#include "problem.hpp"
#include <string>

class Simulation
// The simulation class runs a simulation with given starting point of the agent and grid size. It does bookkeeping on the estimated payoff that the agent will receive after execution.
{
private:
    // the environment contains the agent, sensors and grid and keeps track of the environment.
    Environment environment = Environment();
    // the problem represents the formulation of the problem and contains informatin about:
    // - step-costs for each agent action
    // - goal-testing for each state that the agent is in.
    Problem problem = Problem();
    // The payoff represents the value amassed after performing the actions and arriving at a goal state.
    float payoff;
    
public:
    // A simulation must be initialized with the grid dimesions, agent initial location and available sensors
    Simulation(int* dimensions, char sensors[2]) {environment.init(dimensions, sensors);};
    // This function runs the simulation for timeSteps steps. The simulation can be visualized using the flag visual.
    void run(int timeSteps, bool visual);
    float getPayoff() {return payoff;};
};

#endif /* simulation_hpp */
