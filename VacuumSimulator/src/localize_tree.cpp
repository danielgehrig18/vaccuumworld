//
//  localize_tree.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 25/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/localize_tree.hpp"

using namespace std;

LocalizeTree::LocalizeTree(vector<vector<int>> map)
{
    int x_dimension = map.size();
    int y_dimension = map[0].size();
    
    vector<vector<bool>> wall_map;
    wall_map.resize(x_dimension);
    for (int x_coordinate = 0; x_coordinate < x_dimension; x_coordinate++)
    {
        wall_map[x_coordinate].resize(y_dimension);
        for (int y_coordinate = 0; y_coordinate < y_dimension; y_coordinate++)
        {
            wall_map[x_coordinate][y_coordinate] = map[x_coordinate][y_coordinate] != -1;
        }
    }
    
    State<vector<vector<bool>>> * root_node = new State<vector<vector<bool>>>();
    root_node -> Initialize(wall_map, root_node -> GetActionSequence(), 'n', 0, GetHeuristic(wall_map));
    
    frontier_.push(root_node);
}

vector<char> LocalizeTree::GetSolution()
{
    return solution_;
}

void LocalizeTree::AddChild(State<vector<vector<bool>>> &node, char action, vector<vector<bool>> belief)
{
    State<vector<vector<bool>>> * child = new State<vector<vector<bool>>>();
    child -> Initialize(belief, node.GetActionSequence(), action, node.GetPathCost() + 1, GetHeuristic(belief));
    frontier_.push(child);
}

void LocalizeTree::Search()
{
    while (!frontier_.empty())
    {
        State<vector<vector<bool>>> * next_node = frontier_.top();
        frontier_.pop();
        vector<vector<bool>> next_belief = next_node -> GetData();
        
        if (GoalTest(next_belief))
        {
            solution_ = next_node -> GetActionSequence();
            goal_ = GetEnd(next_belief);
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

array<int, 2> LocalizeTree::GetStart(vector<vector<int>> map)
{
    vector<vector<bool>> wall_map;
    wall_map.resize(map.size());
    for (int x_coordinate = 0; x_coordinate < map.size(); x_coordinate++)
    {
        wall_map[x_coordinate].resize(map[0].size());
        for (int y_coordinate = 0; y_coordinate < map[0].size(); y_coordinate++)
        {
            wall_map[x_coordinate][y_coordinate] = map[x_coordinate][y_coordinate] == -1;
        }
    }
    
    array<int, 2> end = goal_;
    unordered_map<char, array<int, 2>> directions = {{'u', {-1, 0}}, {'r', {0, 1}},
                                                    {'d', {1, 0}},  {'l', {0, -1}}};
    for (char action : solution_)
    {
        int new_x = end[0] - directions[action][0];
        int new_y = end[0] - directions[action][0];
        
        if (new_x != 0 || new_x != wall_map.size() || !wall_map[new_x][end[1]])
        {
            end[0] -= directions[action][0];
        }
                                                                       
        if (new_y != 0 || new_y != wall_map[0].size() || !wall_map[end[0]][new_y])
        {
            end[0] -= directions[action][0];
        }
    }
    
    return end;
}

array<int, 2> LocalizeTree::GetEnd(vector<vector<bool>> map)
{
    int x_dim = map.size() - 1;
    int y_dim = map[0].size() - 1;
    
    for (int row = 0; row < x_dim; row++)
    {
        for (int column = 0; column < y_dim; column++)
        {
            if (map[row][column])
            {
                return {row, column};
            }
        }
    }
    return {x_dim, y_dim};
}

void LocalizeTree::Expand(State<vector<vector<bool>>> &node)
{
    vector<vector<bool>> map = node.GetData();
    
    array<char, 4> directions = {'u', 'r', 'd', 'l'};
    vector<array<int, 2>> steps = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (int direction = 0; direction < 4; direction++)
    {
        for (int row = 0; row < map.size(); row++)
        {
            for (int column = 0; column < map[0].size(); column++)
            {
                int new_row = row += steps[direction][0];
                int new_column = row += steps[direction][1];
                
                map[row][column] = new_row < 0 ||
                                   new_row > map.size() ||
                                   map[new_row][new_column];
            }
        }
        for (vector<vector<bool>> visited_state : visited_states_)
        {
            if (visited_state == map)
            {
                break;
            }
            else
            {
                visited_states_.push_back(map);
                AddChild(node, directions[direction], map);
            }
        }
        
    }
}

int LocalizeTree::GetHeuristic(vector<vector<bool>> belief)
{
    int x_dim, y_dim, bottom;
    
    int top = x_dim = belief.size() - 1;
    int left = y_dim = belief[0].size() - 1;
    
    int right = bottom = 0;
    
    for (int row = 0; row < belief.size(); row++)
    {
        for (int column = 0; column < belief[0].size(); column++)
        {
            if (belief[row][column])
            {
                left = (column < left) ? column : left;
                right = (column > right) ? column : right;
                top = (row < top) ? row : top;
                bottom = (row < bottom) ? row : bottom;
            }
        }
    }
    
    int heuristic_1 = min(right, y_dim - left);
    int heuristic_2 = min(bottom, x_dim - top);
    
    return heuristic_1 + heuristic_2;
}

bool LocalizeTree::GoalTest(vector<vector<bool>> belief)
{
    int count = 0;
    
    for (vector<bool> row : belief)
    {
        for (bool entry : row)
        {
            if (entry)
            {
                count++;
            }
        }
    }
    
    return count == 1;
}