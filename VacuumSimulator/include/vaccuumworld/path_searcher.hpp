//
//  path_searcher.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef path_searcher_hpp
#define path_searcher_hpp

#include <stdlib.h>
#include <queue>
#include <vector>
#include <algorithm>

#include "vaccuumworld/state.hpp"
#include "vaccuumworld/visualizer.hpp"

using namespace std;

class PathSearcher
{
public:
    /** 
        Get the solution that is found after search. Calling this function
        before search returns an empty list of actions.
     
        @param: -
    */
    vector<char> GetSolution();
    
    /**
        Add a child to node through the action action at location location
        and heuristic h.
     
        @param: node: the node to which the child is added.
                action: the action which caused the child to spawn.
                location: coordinates of the new child node.
    */
    void AddChild(State &node, char action, array<int,2> location);
    
    /**
        Initialize the search tree by defining the goal state, the root (initial
        state and the giving the pathFinder the map of the environment.
     
        @param: dirt_patch: coordinates of the goal state at the dirt patch.
                location: coordinates of the agent (initial state).
                map: map of the agent's environment.
                visualizer: visualizer that visualizes the path planning.
    */
    void Initialize(array<int,2> dirt_patch, array<int,2> location, vector<vector<int>> map,
                    Visualizer &visualizer);
    
    /**
        Execute search for the goal and save the solution that is found that created it.
     
        @param: -
    */
    void Search();
    
private:
    /**
        Clear the subtree under node and clear frontier.
     
        @param: node: clears the subtree under node.
    */
    void Clear(State* node);
    
    /**
        Return the solution action sequence that led through the cheapest path 
        to the goal.
     
        @param: -
    */
    vector<char> CalculateSolution();
    
    /**
        Calculates the successors of the node node and adds them to the 
        frontier.
     
        @param: node: node that should be expanded.
    */
    void Expand(State &node);
    
    /**
        Calculates the heuristic function of the location to the goal. Based on the 
        taxi cab distance.
     
        @param: location: coordinates describing the location.
    */
    int GetHeuristic(array<int, 2> location);
    
    
    /**
        Checks whether the location is within the bounds of the map and not an
        already visited state.
     
        @param: location: coordinates describing the location.
    */
    bool CheckAllowability(array<int, 2> location);
    
    priority_queue<State, vector<State*>, CompareStates> frontier_;
    vector<vector<bool>> visited_states_;
    
    State goal_node_;
    State root_node_;
    
    vector<char> solution_;
    
    array<int,2> goal_;

    Visualizer visualizer_;
};

#endif /* path_searcher_hpp */