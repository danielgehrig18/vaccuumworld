//
//  path_searcher.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/path_searcher.hpp"

using namespace std;

void PathSearcher::AddChild(State &node, char action, array<int, 2> location, int heuristic)
{
    State child = State();
    child.Initialize(location, action, node.GetPathCost() + 1, heuristic);
    child.SetParent(&node);
    node.AddChild(&child);
    frontier_.push(child);
}

void PathSearcher::Initialize(array<int, 2> dirt_patch, array<int, 2> location,
                              vector<vector<int> > map, Visualizer &visualizer)
{
    visualizer_ = visualizer;

    int x_dimension = map.size();
    int y_dimension = map[0].size();
    
    for (int x_coordinate = 0; x_coordinate < x_dimension; x_coordinate++)
    {
        for (int y_coordinate = 0; y_coordinate < y_dimension; y_coordinate++)
        {
            if (map[x_coordinate][y_coordinate] != -1)
            {
                map[x_coordinate][y_coordinate] = 0;
            }
        }
    }
    map[location[0]][location[1]] = 2;
    
    visited_states_ = map;
    goal_ = dirt_patch;
    
    int heuristic = abs(dirt_patch[0] - location[0]) + abs(dirt_patch[1] - location[1]);
    
    root_node_.Initialize(location, ' ', 0, heuristic);
    
    frontier_.push(root_node_);
}

bool PathSearcher::Search()
{
    while (!frontier_.empty())
    {
        if (visualizer_.visualize_)
        {
            visualizer_.VisualizeTree(root_node_, 0);
        }
        
        State next_node = frontier_.top();
        frontier_.pop();
        
        if (next_node.GetLocation() == goal_)
        {
            goal_node_ = next_node;
            return true;
        }
        else
        {
            array<int, 2> location = next_node.GetLocation();
            visited_states_[location[0]][location[1]]++;
            Expand(next_node);
        }
    }
    return false;
}

vector<char> PathSearcher::CalculateSolution()
{
    vector<char> action_list;
    for (State node = goal_node_; !(node.IsRoot());
         node = *node.GetParent())
    {
        action_list.push_back(node.GetAction());
    }
    
    reverse(action_list.begin(), action_list.end());
    
    Clear(root_node_);
    
    return action_list;
}

void PathSearcher::Clear(State &root)
{
    for (State* child : root.GetChildren())
    {
        Clear(*child);
    }
    delete &root;
}

void PathSearcher::Expand(State &node)
{
    array<int, 2> location = node.GetLocation();
    
    int x_dimension = visited_states_.size();
    int y_dimension = visited_states_[0].size();
    
    array<int, 2> top_location = {location[0] - 1, location[1]};
    array<int, 2> right_location = {location[0], location[1] + 1};
    array<int, 2> left_location = {location[0], location[1] - 1};
    array<int, 2> bottom_location = {location[0] + 1, location[1]};
    
    int heuristic_top = abs(top_location[0] - goal_[0]) + abs(top_location[1] - goal_[1]);
    int heuristic_right = abs(right_location[0] - goal_[0]) + abs(right_location[1] - goal_[1]);
    int heuristic_left = abs(left_location[0] - goal_[0]) + abs(left_location[1] - goal_[1]);
    int heuristic_bottom = abs(bottom_location[0] - goal_[0]) + abs(bottom_location[1] - goal_[1]);
    
    if (top_location[0] >= 0 &&
        visited_states_[top_location[0]][top_location[1]] == 0)
    {
        visited_states_[top_location[0]][top_location[1]]++;
        AddChild(node, 'u', top_location, heuristic_top);
    }
    
    if (right_location[1] < y_dimension &&
        visited_states_[right_location[0]][right_location[1]] == 0)
    {
        visited_states_[right_location[0]][right_location[1]]++;
        AddChild(node, 'r', right_location, heuristic_right);
    }
    
    if (left_location[1] >= 0 &&
        visited_states_[left_location[0]][left_location[1]] == 0)
    {
        visited_states_[left_location[0]][left_location[1]]++;
        AddChild(node, 'l', left_location, heuristic_left);
    }
    
    if (bottom_location[0] < x_dimension &&
        visited_states_[bottom_location[0]][bottom_location[1]] == 0)
    {
        visited_states_[bottom_location[0]][bottom_location[1]]++;
        AddChild(node, 'd', bottom_location, heuristic_bottom);
    }
}