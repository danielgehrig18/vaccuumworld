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
    int it = 10000;
    
    // Define which sensors will be used
    array<char, 2> sensors = {'d', 'l'};
    
    // Define strategy
    char strategy = 'g';
    
    float p = 0;
    
    for (int i=0; i < it; i++)
    {
        Simulation s = Simulation(dimensions, sensors, strategy);
        s.run(timeSteps, false);
        p += s.getPayoff();
    }
    
    cout << "The average overall payoff for the agent is " << p/it << endl;
    
    return 0;
}
