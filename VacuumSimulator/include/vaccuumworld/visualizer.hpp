//
//  visualizer.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 27/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef visualizer_hpp
#define visualizer_hpp

#include <iostream>
#include <array>
#include <vector>

#include "state.hpp"

using namespace std;

class Visualizer
{
public:
    /**
        Visualize the sensor data acquired.

        @param: dirt: presence of dirt.
                proximity: presence of walls
                directions: direction of closest dirt patch
                location: coordinates of agent
    */
    static void visualizeSensors(bool dirt, array<bool, 4> proximity,
                                 array<bool, 4> directions,
                                 array<int, 2> location);
    
    /**
        Visualize the action executed.
        
        @param: action: action executed.
    */
    static void visualizeAction(char action);
    
    /**
        Visualize the dirt map and agent location
     
        @param: map: dirt map.
                location: coordinates of agent.
    */
    static void visualizeMap(vector<vector<int>> map, array<int, 2> location);
    
    /**
        Visualize the search tree of the agent.
     
        @param: root: root of the tree to be visualized.
                indent: the indent to the tree visualizerd
    */
    static void visualizeTree(State root, int indent);

    static bool visualize;
};

#endif /* visualizer_hpp */
