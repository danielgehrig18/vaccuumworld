//
//  path_searcher.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "path_searcher.hpp"
#include "state.hpp"

vector<char> PathSearcher::getSolution()
{
    vector<char> actionList;
    for (State* node = goalNode; !(node->isRoot()); node = node->getParent())
        actionList.push_back(node->getAction());
    
    reverse(actionList.begin(), actionList.end());
    
    rootNode->~State(frontier);
    
    return actionList;
}