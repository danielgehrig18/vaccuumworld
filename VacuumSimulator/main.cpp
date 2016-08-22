//
//  main.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 04/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include <iostream>
#include <vector>
#include <array>

#include "simulation.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    cout << "Welcome to the vacuum world. Please Initialize the map.\n";
    
    // Ask for the dimensions of the vacuum world. It must be a rectangular array.
    vector<vector<int>> dimensions ={{0, 0},
                                     {0, 0}};
    
    // Ask for the lenght of the simulation.
    int timeSteps = 20;
    
    // Ask for number of iterations
    int it = 1000;
    
    // Define which sensors will be used
    // d : dirt
    // p : proximity sensor
    vector<char> sensors = {'d', 'p'};
    
    // Define strategy
    char strategy = 'r';
    
    float p = 0;
    
    Simulation s = Simulation(dimensions, sensors, strategy);
    
    for (int i=0; i < it; i++)
    {
        s.run(timeSteps, true);
        p += s.getPayoff();
    }
    
    cout << "The average overall payoff for the agent is " << p/it << endl;
    
    return 0;
}
