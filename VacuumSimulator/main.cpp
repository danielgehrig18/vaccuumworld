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
    
    // Ask for the map of the vacuum world. It must be a rectangular array.
    vector<vector<int>> map ={{0,  0,  0, -1,  0,  0,  0},
                              {0,  0,  0,  0,  0,  0,  0},
                              {0,  0,  0, -1,  0,  0,  0}};
    
    // Ask for number of iterations
    int it = 1;
    
    // Define which sensors will be used
    // d : dirt
    // p : proximity sensor
    vector<char> sensors = {'d', 'p', 'l', 'r'};
    
    // Define strategy
    // r: random
    // g: greedy (uses dirt sensor)
    // h: smart greedy (uses proximity and dirt sensor)
    char strategy = 'r';
    
    float p = 0;
    float st = 0;
    
    Simulation s = Simulation(map, sensors, strategy);
    
    for (int i=0; i < it; i++)
    {
        cout << "Iteration " << i+1 << endl;
        s.run(true);
        p += s.getPenalty();
        st += s.getCompletionSteps();
        s.reset();
    }
    
    cout << "The average penalty for the agent is " << p/it << endl;
    cout << "with completion in " << st/it<< endl;
    
    return 0;
}
