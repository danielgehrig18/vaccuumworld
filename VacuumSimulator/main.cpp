//
//  main.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 04/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include <iostream>
#include <vector>
#include "simulation.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    cout << "Welcome to the vacuum world. Please Initialize the map.\n";
    
    // Ask for the dimensions of the vacuum world. It must be a rectangular array.
    int dimensions[] = {1, 2};
    
    // Ask for the lenght of the simulation.
    int timeSteps = 100;
    
    // Define which sensors will be used
    char sensors[] = {'d', 'l'};
    
    // initialize the simulation
    Simulation s = Simulation(dimensions, sensors);
    
    float start = clock();
    
    // run the simulation
    s.run(timeSteps, true);
    
    float duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    
    // evaluate the result of the simulation and display a score
    float payoff = s.getPayoff();
    cout << "The overall payoff for the agent is " << payoff << " and took " << duration << endl;
    
    return 0;
}
