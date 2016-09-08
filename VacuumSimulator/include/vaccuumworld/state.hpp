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
                pathCost: minimum cost of the path to the node so far.
                heuristic: estimated cost from the state to the goal.
    */
    void init(array<int,2> location, char action, int pathCost, int heuristic);
        
    /**
        Sets the parent of the node.
     
        @param: parent: pointer to the parent node of the current node.
    */
    void setParent(State* parent);
    
    /**
        Adds a child to the current node.
     
        @param: child: pointer to a child of the current node.
     */
    void addChild(State* child);
    
    /**
        Returns the parent of the current node.
     
        @param: -
    */
    State* getParent();
    
    
    /**
        Returns the children of the current node.
     
        @param: -
    */
    vector<State*> getChildren();
    
    /**
        Returns the action that was executed to achieve the current node.
     
        @param: -
    */
    char getAction();
    
    /**
        Returns the location coordinates of the current node.
     
        @param: -
    */
    array<int, 2> getLocation();
    
    /**
        Returns the cost that was used to get to the current node.
     
        @param: -
    */
    int getPathCost();
    
    /**
        Returns the estimated total cost of the path based on the sum of the 
        path cost and the heuristic.
     
        @param: -
    */
    int getTotalCost();
    
    /**
        Tests if the current node is a root node by checking that it does not
        have parents.
     
        @param: -
    */
    bool isRoot();

private:
    State* parent_ = NULL;
    vector<State*> children_;
    char action_;
    
    array<int, 2> location_;
    
    int pathCost_;
    int heuristic_;
};

class CompareStates
{
public:
    /**
        Used to define ordering on state s1 and s2 in priority queue. This is
        done based on estimated total path cost. TODO: specify order.
     
        @param: s1: first state.
                s2: second state.
    */
    bool operator()(State s1, State s2);
};

#endif /* state_hpp */
