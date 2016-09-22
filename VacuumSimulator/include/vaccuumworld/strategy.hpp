//
//  strategy.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 20/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef strategy_hpp
#define strategy_hpp

#include <stdlib.h>
#include <array>
#include <vector>
#include <queue>

#include "vaccuumworld/path_searcher.hpp"
#include "vaccuumworld/model.hpp"

using namespace std;

class Strategy {
public:

    void Initialize(Visualizer &visualizer);
    /**
        Set the type of strategy. Can be one of the following: 'a' random
        search, 'b' greedy search, 'c' more greedy search, 'd' super greedy
        search, 'e' state search.
     
        @param: type of the strategy.
    */
    void SetType(char type);
    
    /**
        Gets the type of strategy.
     
        @param: -
    */
    char GetType();
    
    /**
        Test whether an action is planned.
     
        @param: -
    */
    bool ActionPlanned();
    
    /**
        Plan action depending of sensor inputs.
     
        @param: dirt: presence of dirt (see: "dirt_sensor.hpp")
                proximity: presence of walls (see: "proximity_sensor.hpp")
                direction: direction of closest dirt (see: 
                           "direction_sensor.hpp")
                location: location of agent (see: "location_sensor.hpp")
                map: dirt map of the environment.
    */
    void PlanAction(bool dirt, array<bool, 4> proximity, array<bool, 4> direction,
                    array<int, 2> location, vector<vector<int>> map);
    
    /**
        Get next action from queue and return it.
     
        @param: -
    */
    char ActionSelection();

private:
    /**
        Computes a sequence of action that brings the agent to the closest dirt
        patch.
     
        @param: location: initial location of agent.
                state: dirt map of the environment.
    */
    vector<char> StateSearch(array<int, 2> location, vector<vector<int>> state);
    
    /**
        Computes the action based on proximity, dirt and direction sensor.
     
     @param: dirt: presence of dirt (see: "dirt_sensor.hpp")
             proximity: presence of walls (see: "proximity_sensor.hpp")
             direction: direction of closest dirt (see: "direction_sensor.hpp")
    */
    char SuperGreedySearch(bool dirt, array<bool, 4> proximity, array<bool, 4> direction);
    
    /**
        Computes the action based on proximity and dirt.
     
        @param: dirt: presence of dirt (see: "dirt_sensor.hpp")
                proximity: presence of walls (see: "proximity_sensor.hpp")
    */
    char MoreGreedySearch(bool dirt, array<bool, 4> proximity);
    
    /**
        Computes the action based on dirt sensor.
     
        @param: dirt: presence of dirt (see: "dirt_sensor.hpp")
    */
    char GreedySearch(bool dirt);
    
    /**
        Computes the action without sensors.
     
        @param: -
    */
    char RandomSearch();
    
    char type_;
    vector<char> actions_ = {'u', 'r', 'd', 'l', 's'};
    
    queue<char> plan_;
    
    PathSearcher path_searcher_;
    Visualizer visualizer_;
};

#endif /* strategy_hpp */