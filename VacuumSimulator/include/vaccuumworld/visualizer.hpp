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
    void VisualizeSensors(bool dirt, array<bool, 4> proximity, array<bool, 4> directions,
                          array<int, 2> location);
    
    /**
        Visualize the action executed.
        
        @param: action: action executed.
    */
    void VisualizeAction(char action);
    
    /**
        Visualize the dirt map and agent location
     
        @param: map: dirt map.
                location: coordinates of agent.
    */
    void VisualizeMap(vector<vector<int>> map, array<int, 2> location);
    
    /**
        Visualize the search tree of the agent.
     
        @param: root: root of the tree to be visualized.
                indent: the indent to the tree visualizerd
    */
    void VisualizeTree(State root, int indent);

    bool visualize_;
};

#endif /* visualizer_hpp */