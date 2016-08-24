//
//  path_searcher.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//
# include <stdlib.h>

#include "path_searcher.hpp"
#include "state.hpp"

vector<char> PathSearcher::getSolution()
{
    vector<char> actionList;
    for (State* node = goalNode; !(node->isRoot()); node = node->getParent())
        actionList.push_back(node->getAction());
    
    reverse(actionList.begin(), actionList.end());
    
    rootNode->~State();
    
    return actionList;
}

void PathSearcher::init(array<int,2> dirtPatch, array<int,2> location, vector<vector<int>> map)
{
    goal = dirtPatch;
    
    int h = abs(dirtPatch[0]-location[0])+abs(dirtPatch[1]-location[1]);
    
    State node = State(location, 0, h);
    rootNode = &node;
    
    visitedStates[location[0]][location[1]] = true;
    frontier.push(rootNode);
}

void PathSearcher::search()
{
    while (!frontier.empty()) {
        State* nextNode = frontier.top();
        frontier.pop();
        
        if (nextNode->getLocation()==goal)
        {
            goalNode = nextNode;
            break;
        }
        
        else
        {
            array<int,2> location = nextNode->getLocation();
            visitedStates[location[0]][location[1]]++;
            expand(nextNode);
        }
    }
}

void PathSearcher::expand(State* node)
{
    array<int, 2> loc = node->getLocation();
    
    array<int, 2> top = {loc[0]-1,loc[1]};
    array<int, 2> right = {loc[0],loc[1]+1};
    array<int, 2> left = {loc[0],loc[1]-1};
    array<int, 2> bottom = {loc[0]+1,loc[1]};
    
    int hTop = abs(top[0]-goal[0])+abs(top[1]-goal[1]);
    int hRight = abs(right[0]-goal[0])+abs(right[1]-goal[1]);
    int hLeft = abs(left[0]-goal[0])+abs(left[1]-goal[1]);
    int hBottom = abs(bottom[0]-goal[0])+abs(bottom[1]-goal[1]);
    
    if (visitedStates[top[0]][top[1]] == 0)
    {
        visitedStates[top[0]][top[1]]++;
        frontier.push(node->childOf(top, hTop));
    }
    
    if (visitedStates[right[0]][right[1]] == 0)
    {
        visitedStates[right[0]][right[1]]++;
        frontier.push(node->childOf(right, hRight));
    }
    
    if (visitedStates[left[0]][left[1]] == 0)
    {
        visitedStates[left[0]][left[1]]++;
        frontier.push(node->childOf(left, hLeft));
    }
    
    if (visitedStates[bottom[0]][bottom[1]] == 0)
    {
        visitedStates[bottom[0]][bottom[1]]++;
        frontier.push(node->childOf(bottom, hBottom));
    }
}