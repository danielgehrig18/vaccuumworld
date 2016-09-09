//
//  main.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 04/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include <iostream>

#include "vaccuumworld/simulation.hpp"
#include "vaccuumworld/visualizer.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    // Ask for the map of the vacuum world. It must be a rectangular array.
    vector<vector<int>> map = {{0,  0,  0, -1,  0,  0,  0},
                               {0,  0,  0,  0,  0,  0,  0},
                               {0,  0,  0, -1,  0,  0,  0}};
    
    // Ask for number of iterations
    int iterations = 1;
    
    // Define which sensors will be used
    // d : dirt
    // p : proximity sensor
    vector<char> sensors = {'d', 'p', 'r', 'l'};

    // Define which actuators will be used
    vector<char> actuators = {'m', 's'};
    
    // visualize
    bool visualize = true;
    
    Visualizer visualizer;
    visualizer.visualize_ = visualize;
    
    float penalty = 0;
    float steps = 0;
    
    Simulation simulation = Simulation(map, sensors, actuators, visualizer);
    
    for (int iteration = 0; iteration < iterations; iteration++)
    {
        cout << "Iteration " << iteration + 1 << endl;
        simulation.Run();
        penalty += simulation.GetPenalty();
        steps += simulation.GetCompletionSteps();
        simulation.Reset();
    }
    
    cout << "The average penalty for the agent is " << penalty / iterations << endl;
    cout << "with completion in " << steps / iterations << endl;
    
    return 0;
}