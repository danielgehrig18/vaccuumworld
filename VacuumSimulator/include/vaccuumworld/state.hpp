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
                path_cost: minimum cost of the path to the node so far.
                heuristic: estimated cost from the state to the goal.
    */
    void Initialize(array<int,2> location, char action, int path_cost, int heuristic);
        
    /**
        Sets the parent of the node.
     
        @param: parent: pointer to the parent node of the current node.
    */
    void SetParent(State* parent);
    
    /**
        Adds a child to the current node.
     
        @param: child: pointer to a child of the current node.
     */
    void AddChild(State* child);
    
    /**
        Returns the parent of the current node.
     
        @param: -
    */
    State* GetParent();
    
    
    /**
        Returns the children of the current node.
     
        @param: -
    */
    vector<State*> GetChildren();
    
    /**
        Returns the action that was executed to achieve the current node.
     
        @param: -
    */
    char GetAction();
    
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
    
    /**
        Tests if the current node is a root node by checking that it does not
        have parents.
     
        @param: -
    */
    bool IsRoot();

private:
    State* parent_ = NULL;
    vector<State*> children_;
    char action_;
    
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
    bool operator()(State state_1, State state_2);
};

#endif /* state_hpp */