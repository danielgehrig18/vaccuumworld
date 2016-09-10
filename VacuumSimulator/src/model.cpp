//
//  model.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 21/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//
#include "vaccuumworld/model.hpp"

using namespace std;


int Model::GetDirt(vector<vector<int>> map, array<int, 2> location)
{
    return map[location[0]][location[1]];
};

void Model::UpdateLocation(char action, array<int, 2> &location,
                                    vector<vector<int>> map)
{
    int x_dimension = map.size();
    int y_dimension = map[0].size();
    
    int x_coordinate = location[0];
    int y_coordinate = location[1];

    switch (action)
    {
        case 'l':
            if (y_coordinate != 0 && map[x_coordinate][y_coordinate - 1] != -1)
            {
                location[1] -= 1;
                break;
            }
        case 'r':
            if (y_coordinate != y_dimension - 1 && map[x_coordinate][y_coordinate + 1] != -1)
            {
                location[1] += 1;
                break;
            }
        case 'u':
            if (x_coordinate != 0 && map[x_coordinate - 1][y_coordinate] != -1)
            {
                location[0] -= 1;
                break;
            }
        case 'd':
            if (x_coordinate != x_dimension - 1 && map[x_coordinate + 1][y_coordinate] != -1)
            {
                location[0] += 1;
                break;
            }
        case 's':
            break;
    }
}

array<bool, 4> Model::GetProximity(vector<vector<int>> map, array<int, 2> location)
{
    int x_dimension = map.size();
    int y_dimension = map[0].size();
    
    int x_coordinate = location[0];
    int y_coordinate = location[1];
    
    array<bool, 4> walls;
    
    walls[0] = (x_coordinate == 0 || map[x_coordinate - 1][y_coordinate] == -1);
    walls[1] = (y_coordinate == y_dimension - 1 || map[x_coordinate][y_coordinate + 1] == -1);
    walls[2] = (x_coordinate == x_dimension - 1 || map[x_coordinate + 1][y_coordinate] == -1);
    walls[3] = (y_coordinate == 0 || map[x_coordinate][y_coordinate - 1] == -1);
    
    return walls;
}

array<bool, 4> Model::GetDirections(vector<vector<int>> map, array<int, 2> location)
{
    vector<array<int, 2>> closest_dirt = GetClosestDirt(map, location);
    
    array<bool, 4> directions = {false, false, false, false};
    if (closest_dirt.empty())
    {
        return directions;
    }
    else
    {
        for (array<int, 2> coordinates : closest_dirt)
        {
            int x_direction = coordinates[0] - location[0];
            int y_direction = coordinates[1] - location[1];
            
            array<bool,4> new_dirt = {x_direction <= -abs(y_direction),
                                      y_direction >= abs(x_direction),
                                      x_direction >= abs(y_direction),
                                      y_direction <= -abs(x_direction)};
            
            for (int direction = 0; direction < directions.size(); direction++)
            {
                directions[direction] = directions[direction] || new_dirt[direction];
            }
        }
        
        return directions;
    }
}

vector<array<int, 2>> Model::GetClosestDirt(vector<vector<int>> map, array<int, 2> location)
{
    vector<array<int, 2>> closest_dirt;
    int closest_distance =- 1;
    
    for (int x_coordinate = 0; x_coordinate < map.size(); x_coordinate++)
    {
        for (int y_coordinate = 0; y_coordinate < map[0].size(); y_coordinate++)
        {
            if (map[x_coordinate][y_coordinate] == 1)
            {
                int distance = abs(location[0] - x_coordinate) + abs(location[1] - y_coordinate);
                
                if (distance == closest_distance)
                {
                    closest_dirt.push_back({x_coordinate, y_coordinate});
                }
                else if (distance < closest_distance || closest_distance == -1)
                {
                    closest_dirt.clear();
                    closest_dirt.push_back({x_coordinate, y_coordinate});
                    closest_distance = distance;
                }
            }
        }
    }
    
    return closest_dirt;
}

void Model::UpdateMap(char action, array<int,2> location, vector<vector<int>> &map)
{
    if (action == 's')
    {
        map[location[0]][location[1]] = 0;
    }
}