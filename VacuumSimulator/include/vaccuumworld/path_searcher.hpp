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
        Add a child to node through the action action at location location
        and heuristic h.
     
        @param: node: the node to which the child is added.
                action: the action which caused the child to spawn.
                location: coordinates of the new child node.
                h: heuristic of the new node.
    */
    void addChild(State &node, char action, array<int,2> location, int h);
    
    /**
        Initialize the search tree by defining the goal state, the root (initial
        state and the giving the pathFinder the map of the environment.
     
        @param: dirtPatch: coordinates of the goal state at the dirt patch.
                location: coordinates of the agent (initial state).
                map: map of the agent's environment.
    */
    void init(array<int,2> dirtPatch, array<int,2> location, vector<vector<int>> map, Visualizer &visualizer);
    
    /**
        Execute search for the goal and save the tree that created it.
     
        @param: -
    */
    bool search();
    
    /**
        Return the solution action sequence that led through the cheapest path 
        to the goal.
     
        @param: -
    */
    vector<char> getSolution();
    
    /**
        Clears the tree from memory.
     
        @param: root: the root of the tree to be cleared.
    */
    void clear(State &root);
    
private:
    /**
        Calculates the successors of the node node and adds them to the 
        frontier.
     
        @param: node: node that should be expanded.
    */
    void expand(State &node);
    
    priority_queue<State, vector<State>, CompareStates> frontier;
    vector<vector<int>> visitedStates;
    
    State goalNode;
    State rootNode;
    
    array<int,2> goal;

    Visualizer visualizer_;
};

#endif /* path_searcher_hpp */
