//
//  simulation.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "simulation.hpp"
#include "problem.hpp"
#include "environment.hpp"

Simulation::Simulation(int* dimensions, int* sensors)
{
    problem = Problem();
    environment = Environment(dimensions, sensors);
}

void Simulation::run(int timeSteps, bool visual)
{
    
}
