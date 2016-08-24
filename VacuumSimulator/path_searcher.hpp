//
//  path_searcher.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef path_searcher_hpp
#define path_searcher_hpp

#include <queue>
#include <vector>

#include "state.hpp"

using namespace std;


class CompareCosts {
public:
    bool operator()(State& s1, State& s2) {return s1.getTotalCost()<s2.getTotalCost();}
};

class PathSearcher
{
private:
    priority_queue<State*, vector<State*>, CompareCosts> frontier;
    vector<vector<int>> visitedStates;
    
    State* goalNode;
    State* rootNode;
    
    array<int,2> goal;
    
public:
    void init(array<int,2> dirtPatch, array<int,2> location, vector<vector<int>> map);
    void search();
    vector<char> getSolution();
    void expand(State* node);
};

#endif /* path_searcher_hpp */