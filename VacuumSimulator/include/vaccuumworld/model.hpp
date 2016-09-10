//
//  model.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 21/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef model_hpp
#define model_hpp

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <array>
#include <vector>

using namespace std;

class Model
{
public:
    /**
        Return whether there is dirt in location.
     
        @param: map: dirt map of the environment.
                location: coordinates of location where dirt is queried.
    */
    int GetDirt(vector<vector<int>> map, array<int, 2> location);
    
    /**
        Calculate new location of agent based on location and action.
     
        @param: action: action that was executed by the agent.
                location: initial coordinates of the agent
                map: dirt map of the environment.
    */
    void UpdateLocation(char action, array<int, 2> &location, vector<vector<int>> map);
    
    /**
        Calculate the directions of the walls based on the agent location.
     
        @param: map: dirt map of the environment.
                location: coordinates of the agent.
    */
    array<bool, 4> GetProximity(vector<vector<int>> map, array<int, 2> location);
    
    /**
        Calculate the direction of the closest dirt patch based on the agent
        location and map.
     
        @param: map: dirt map of the environment.
                location: coordinates of the agent.
    */
    array<bool, 4> GetDirections(vector<vector<int>> map, array<int, 2> location);
    
    /**
        Returns a list of coordinates corresponding to the closest dirt patches
        with respect to the taxi-cab distance.
     
        @param: map: dirt map of the environment.
                location: coordinates of the agent.
    */
    static vector<array<int, 2>> GetClosestDirt(vector<vector<int>> map, array<int, 2> location);
    
    /**
        Calculates the new dirt map based on the agent action and location.
     
        @param: action: action executed
                location: coordinates at which the action was executed
                map: dirt map of the environment.
    */
    void UpdateMap(char action, array<int,2> location, vector<vector<int>> &map);

};

#endif /* model_hpp */