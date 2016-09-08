//
//  path_searcher.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/path_searcher.hpp"

using namespace std;

void PathSearcher::addChild(State &node, char action, array<int, 2> location, int h)
{
    State child = State();
    child.init(location, action, node.getPathCost() + 1, h);
    child.setParent(&node);
    node.addChild(&child);
    frontier.push(child);
}

void PathSearcher::init(array<int, 2> dirtPatch, array<int, 2> location,
                        vector<vector<int>> map)
{
    int x = map.size();
    int y = map[0].size();
    
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if (map[i][j] != -1)
            {
                map[i][j] = 0;
            }
        }
    }
    map[location[0]][location[1]] = 2;
    
    visitedStates = map;
    goal = dirtPatch;
    
    int h = abs(dirtPatch[0] - location[0]) + abs(dirtPatch[1] - location[1]);
    
    rootNode.init(location, ' ', 0, h);
    
    frontier.push(rootNode);
}

bool PathSearcher::search()
{
    while (!frontier.empty())
    {
        if (Visualizer::visualize)
        {
            Visualizer::visualizeTree(rootNode, 0);
        }
        
        State nextNode = frontier.top();
        frontier.pop();
        
        if (nextNode.getLocation() == goal)
        {
            goalNode = nextNode;
            return true;
        }
        else
        {
            array<int, 2> location = nextNode.getLocation();
            visitedStates[location[0]][location[1]]++;
            expand(nextNode);
        }
    }
    return false;
}

vector<char> PathSearcher::getSolution()
{
    vector<char> actionList;
    for (State node = goalNode; !(node.isRoot());
         node = *node.getParent())
    {
        actionList.push_back(node.getAction());
    }
    
    reverse(actionList.begin(), actionList.end());
    
    clear(rootNode);
    
    return actionList;
}

void PathSearcher::clear(State &root)
{
    for (State* child : root.getChildren())
    {
        clear(*child);
    }
    delete &root;
}

void PathSearcher::expand(State &node)
{
    array<int, 2> loc = node.getLocation();
    
    int x = visitedStates.size();
    int y = visitedStates[0].size();
    
    array<int, 2> top = {loc[0] - 1, loc[1]};
    array<int, 2> right = {loc[0], loc[1] + 1};
    array<int, 2> left = {loc[0], loc[1] - 1};
    array<int, 2> bottom = {loc[0] + 1, loc[1]};
    
    int hTop = abs(top[0] - goal[0]) + abs(top[1] - goal[1]);
    int hRight = abs(right[0] - goal[0]) + abs(right[1] - goal[1]);
    int hLeft = abs(left[0] - goal[0]) + abs(left[1] - goal[1]);
    int hBottom = abs(bottom[0] - goal[0]) + abs(bottom[1] - goal[1]);
    
    if (top[0] >= 0 && visitedStates[top[0]][top[1]] == 0)
    {
        visitedStates[top[0]][top[1]]++;
        addChild(node, 'u', top, hTop);
    }
    
    if (right[1] < y && visitedStates[right[0]][right[1]] == 0)
    {
        visitedStates[right[0]][right[1]]++;
        addChild(node, 'r', right, hRight);
    }
    
    if (left[1] >= 0 && visitedStates[left[0]][left[1]] == 0)
    {
        visitedStates[left[0]][left[1]]++;
        addChild(node, 'l', left, hLeft);
    }
    
    if (bottom[0] < x && visitedStates[bottom[0]][bottom[1]] == 0)
    {
        visitedStates[bottom[0]][bottom[1]]++;
        addChild(node, 'd', bottom, hBottom);
    }
}
