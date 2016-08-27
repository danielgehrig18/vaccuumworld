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
                strategy: corresponds to the strategy to be used by the agent.
                visual: flag which visualises the sensor input and decisions of
                        the agent.
    */
    Simulation(vector<vector<int>> map, vector<char> sensors, char strategy,
               bool visualize);
    
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
    Environment environment;
    Problem problem;
    
    float penalty=0;
    int completionSteps;
    bool visualize;
};

#endif /* simulation_hpp */
