//
//  simulation.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef simulation_hpp
#define simulation_hpp

#include <iostream>
#include <array>

#include "vaccuumworld/environment.hpp"
#include "vaccuumworld/problem.hpp"
#include "vaccuumworld/visualizer.hpp"

using namespace std;
class Simulation
{
public:
    /**
        Constructor of Simulation. Initializes random generator and environment
        with a map of the room, available sensors (see "sensor.hpp") and
        strategy to be followed (see "strategy.hpp").
     
        @param: map: grid of the environment of the agent. Entries can be 0, 1
                     or -1 corresponding to empty spots, dirty spots and walls 
                     resp.
                sensors: list of sensors to be used by the agent.
                actuators: a list of actuators to be used.
    */
    Simulation(vector<vector<int>> map, vector<char> sensors,
               vector<char> actuators, Visualizer &visualizer);
    
    /**
     Return penalty. 1 pt is penalized for every dirty square at every time
     step.
     
     @param: -
     */
    float getPenalty();
    
    /**
     Return steps that it took the agent to completely clean the map.
     
     @param: -
     */
    int getCompletionSteps();
    
    /**
        Runs the simulation. Environment, agent and sensors are updated on a
        stepwise basis and the payoff is recorded. The simulation is run until
        all squares are clean. Records stepnumber and penalty cost.
     
        @param: -
    */
    void run();
    
    /**
        Randomizes the dirt locations in the map and the initial agent location.
     
        @param: -
    */
    void reset();
    
private:
    Environment environment_;
    Problem problem_;
    Visualizer visualizer_;
    
    float penalty_ = 0;
    int completionSteps_;
};

#endif /* simulation_hpp */
