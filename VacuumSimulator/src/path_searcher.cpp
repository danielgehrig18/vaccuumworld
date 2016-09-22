//
//  path_searcher.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/path_searcher.hpp"

using namespace std;

vector<char> PathSearcher::GetSolution()
{
    return solution_;
}

void PathSearcher::AddChild(State<array<int, 2>> &node, char action, array<int, 2> location)
{
    State<array<int, 2>> * child = new State<array<int, 2>>();
    child -> Initialize(location, node.GetActionSequence(), action, node.GetPathCost() + 1, GetHeuristic(location));
    frontier_.push(child);
    visited_states_[location[0]][location[1]] = true;
}

void PathSearcher::Initialize(array<int, 2> dirt_patch, array<int, 2> location,
                              vector<vector<int> > map, Visualizer &visualizer)
{
    visualizer_ = visualizer;

    int x_dimension = map.size();
    int y_dimension = map[0].size();
    
    visited_states_.resize(x_dimension);
    for (int x_coordinate = 0; x_coordinate < x_dimension; x_coordinate++)
    {
        visited_states_[x_coordinate].resize(y_dimension);
        for (int y_coordinate = 0; y_coordinate < y_dimension; y_coordinate++)
        {
            visited_states_[x_coordinate][y_coordinate] = map[x_coordinate][y_coordinate] == -1;
        }
    }
    
    goal_ = dirt_patch;
    
    State<array<int, 2>> * root_node = new State<array<int, 2>>();
    root_node -> Initialize(location, root_node -> GetActionSequence(), 's', 0, GetHeuristic(location));
    visited_states_[location[0]][location[1]] = true;
    
    frontier_.push(root_node);
}

void PathSearcher::Search()
{
    while (!frontier_.empty())
    {
        State<array<int, 2>> * next_node = frontier_.top();
        frontier_.pop();
        array<int, 2> next_location = next_node -> GetData();
        
        if (next_location == goal_)
        {
            solution_ = next_node -> GetActionSequence();
            while (!frontier_.empty())
            {
                delete frontier_.top();
                frontier_.pop();
            }
            break;
        }
        else
        {
            Expand(*next_node);
        }
        delete next_node;
    }
}

void PathSearcher::Expand(State<array<int, 2>> &node)
{
    array<char, 4> directions = {'u', 'r', 'd', 'l'};
    
    vector<array<int, 2>> steps = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    for (int iteration = 0; iteration < 4; iteration++)
    {
        array<int, 2> temporary = node.GetData();
        
        temporary[0] += steps[iteration][0];
        temporary[1] += steps[iteration][1];
        
        if (CheckAllowability(temporary))
        {
            AddChild(node, directions[iteration], temporary);
        }
    }
}

int PathSearcher::GetHeuristic(array<int, 2> location)
{
    return abs(location[0] - goal_[0]) + abs(location[1] - goal_[1]);
}

bool PathSearcher::CheckAllowability(array<int, 2> location)
{
    int x_dimension = visited_states_.size();
    int y_dimension = visited_states_[0].size();
    bool in_field = location[0] >= 0 && location[0] < x_dimension && location[1] >= 0
                    && location[1] < y_dimension;
    if (!in_field)
    {
        return false;
    }
    else
    {
        return !visited_states_[location[0]][location[1]];
    }
}