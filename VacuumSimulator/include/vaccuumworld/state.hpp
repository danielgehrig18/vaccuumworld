//
//  state.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef state_hpp
#define state_hpp

#include <array>
#include <vector>

using namespace std;

class State
{
public:
    /**
        Constructor of a state node. The node is identified by its location in
        coordinates, the action taken to get to the node, its path cost and its
        heuristic cost to the goal.
     
        @param: location: coordinates of the state.
                action_sequence: sequence of actions of parent.
                action: action that was performed to get to this node.
                path_cost: minimum cost of the path to the node so far.
                heuristic: estimated cost from the state to the goal.
    */
    void Initialize(array<int,2> location, vector<char> action_sequence, char action, int path_cost, int heuristic);
    
    /**
        Returns the action sequence that was executed to achieve the current node.
     
        @param: -
    */
    vector<char> GetActionSequence();
    
    /**
        Returns the location coordinates of the current node.
     
        @param: -
    */
    array<int, 2> GetLocation();
    
    /**
        Returns the cost that was used to get to the current node.
     
        @param: -
    */
    int GetPathCost();
    
    /**
        Returns the estimated total cost of the path based on the sum of the 
        path cost and the heuristic.
     
        @param: -
    */
    int GetTotalCost();

private:
    vector<char> action_sequence_;
    
    array<int, 2> location_;
    
    int path_cost_;
    int heuristic_;
};

class CompareStates
{
public:
    /**
        Used to define ordering on state s1 and s2 in priority queue. This is
        done based on estimated total path cost. TODO: specify order.
     
        @param: state_1: first state.
                state_2: second state.
    */
    bool operator()(State * state_1, State * state_2);
};

#endif /* state_hpp */