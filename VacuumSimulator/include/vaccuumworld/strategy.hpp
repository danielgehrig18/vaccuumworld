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

    void init(Visualizer &visualizer);
    /**
        Set the type of strategy. Can be one of the following: 'r' random
        search, 'g' greedy search, 'h' more greedy search, 'i' super greedy
        search, 's' state search.
     
        @param: DSStatus: status of dirtSensor.
                PSStatus: status of proximitySensor.
                DirSStatus: status of directionSensor.
                LSStatus: status of locationSensor.
                MStatus: status of motor.
                SStatus: status of sucker.
    */
    void setType(bool DSStatus, bool PSStatus, bool DirSStatus, bool LSStatus,
                 bool MStatus, bool SStatus);
    
    /**
        Test whether an action is planned.
     
        @param: -
    */
    bool actionPlanned();
    
    /**
        Plan action depending of sensor inputs.
     
        @param: dirt: presence of dirt (see: "dirt_sensor.hpp")
                proximity: presence of walls (see: "proximity_sensor.hpp")
                direction: direction of closest dirt (see: 
                           "direction_sensor.hpp")
                location: location of agent (see: "location_sensor.hpp")
                map: dirt map of the environment.
    */
    void planAction(bool dirt, array<bool, 4> proximity, array<bool, 4> direction,
                    array<int, 2> location, vector<vector<int>> map);
    
    /**
        Get next action from queue and return it.
     
        @param: -
    */
    char actionSelection();

private:
    /**
        Computes a sequence of action that brings the agent to the closest dirt
        patch.
     
        @param: location: initial location of agent.
                state: dirt map of the environment.
    */
    vector<char> stateSearch(array<int, 2> location, vector<vector<int>> state);
    
    /**
        Computes the action based on proximity, dirt and direction sensor.
     
     @param: dirt: presence of dirt (see: "dirt_sensor.hpp")
             proximity: presence of walls (see: "proximity_sensor.hpp")
             direction: direction of closest dirt (see:
             "direction_sensor.hpp")
    */
    char superGreedySearch(bool dirt, array<bool, 4> proximity,
                           array<bool, 4> direction);
    
    /**
        Computes the action based on proximity and dirt.
     
        @param: dirt: presence of dirt (see: "dirt_sensor.hpp")
                proximity: presence of walls (see: "proximity_sensor.hpp")
    */
    char moreGreedySearch(bool dirt, array<bool, 4>proximity);
    
    /**
        Computes the action based on dirt sensor.
     
        @param: dirt: presence of dirt (see: "dirt_sensor.hpp")
    */
    char greedySearch(bool dirt);
    
    /**
        Computes the action without sensors.
     
        @param: -
    */
    char randomSearch();
    
    char type;
    vector<char> actions = {'u', 'r', 'd', 'l', 's'};
    
    queue<char> plan;
    
    PathSearcher pathSearcher;
    Visualizer visualizer_;
};

#endif /* strategy_hpp */
