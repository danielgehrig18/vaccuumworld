//
//  simulation.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "simulation.hpp"
#include <iostream>

Simulation::Simulation(vector<vector<int>> dimensions, vector<char> sensors, char strategy)
{
    srand (time(NULL));
    environment.init(dimensions, sensors, strategy);
}

void Simulation::run(bool visual)
{
    // display map
    if (visual){
        vector<vector<int>> dimensions = environment.getDimensions();
        array<int, 2> agentLocation = environment.getAgentLocation();
        cout << "MAP: " << endl;
        for (int i=0; i<dimensions.size(); i++)
        {
            for (int j=0; j<dimensions[0].size(); j++)
            {
                if (agentLocation[0] == i && agentLocation[1] == j)
                {
                    if (dimensions[i][j] == 0)
                    {
                        cout << 'Q';
                    }
                    else cout << 'J';
                }
                else if (dimensions[i][j]==-1) cout <<'x';
                else cout << dimensions[i][j];
            }
            cout << endl;
        }
    }
    
    int counter = 0;
    while (!problem.goalTest(environment))
    {
        if (visual) cout << "--- step " << counter + 1 << " ---" << endl;
        
        environment.step(visual);
        penalty += problem.calculatePenalty(environment);
        counter++;
    }
    if (visual) cout << "*** Completion in " << counter << " steps. ***" << endl;
    completionSteps = counter;
}

void Simulation::reset()
{
    penalty = 0;
    completionSteps = -1;
    environment.reset();
}
