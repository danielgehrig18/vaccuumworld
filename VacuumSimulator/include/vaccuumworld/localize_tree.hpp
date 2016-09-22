//
//  localize_tree.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 22/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef localize_tree_hpp
#define localize_tree_hpp

#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <unordered_map>

#include "state.hpp"

using namespace std;

class LocalizeTree
{
public:
    /**
        Initializes the search tree with the current map of the walls.
        
        @param: map: map of the environment.
    */
    LocalizeTree(vector<vector<int>> map);
    
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
                belief: belief state of the new child node.
    */
    void AddChild(State<vector<vector<bool>>> &node, char action, vector<vector<bool>> belief);
    
    /**
        Execute search for the goal and save the solution that is found that created it.
     
        @param: -
    */
    void Search();
    
    /**
        Backtracks from the solution and gives a start location for the agent.
     
        @param: wall_map: map of all the walls
    */
    array<int, 2> GetStart(vector<vector<int>> wall_map);
    
    /**
        Returns the end position of the agent.
     
        @param: belief: map of the belief state.
     */
    array<int, 2> GetEnd(vector<vector<bool>> belief);
    
private:
    /**
        Clear all allocated memory.
     
        @param: node: clears frontier of allocated memory.
    */
    void Clear();
    
    /**
        Calculates the successors of the node node and adds them to the
        frontier.
     
        @param: node: node that should be expanded.
    */
    void Expand(State<vector<vector<bool>>> &node);
    
    /**
        Calculates the heuristic function of belief state to the goal.
     
        @param: location: coordinates describing the location.
    */
    int GetHeuristic(vector<vector<bool>> belief);
    
    /**
        Determines whether a state is the goal state. Returns true if only one
        spot is in the belief state.
     
        @param: belief: Map of believed locations of the agent.
    */
    bool GoalTest(vector<vector<bool>> belief);
    
    priority_queue<State<vector<vector<bool>>>,
                   vector<State<vector<vector<bool>>>*>,
                   CompareStates<vector<vector<bool>>>> frontier_;
    vector<vector<vector<bool>>> visited_states_;
    
    vector<char> solution_;
    
    array<int, 2> goal_;
};

#endif /* localize_tree_hpp */