//
//  simulation.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef simulation_hpp
#define simulation_hpp

#include <array>

#include "environment.hpp"
#include "problem.hpp"

class Simulation
// The simulation class runs a simulation with given starting point of the agent and grid size. It does bookkeeping on the estimated payoff that the agent will receive after execution.
{
private:
    // the environment contains the agent, sensors and grid and keeps track of the environment.
    Environment environment;
    // the problem represents the formulation of the problem and contains informatin about:
    // - step-costs for each agent action
    // - goal-testing for each state that the agent is in.
    Problem problem;
    // The payoff represents the value amassed after performing the actions and arriving at a goal state.
    float payoff=0;
    
public:
    // A simulation must be initialized with the grid dimesions, agent initial location and available sensors
    Simulation(vector<vector<int>> dimensions, array<char, 2> sensors, char strategy);
    // This function runs the simulation for timeSteps steps. The simulation can be visualized using the flag visual.
    void run(int timeSteps, bool visual);
    float getPayoff() {return payoff;};
};

#endif /* simulation_hpp */
