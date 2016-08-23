//
//  model.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 21/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//
#include <iostream>
#include <stdlib.h>

#include "model.hpp"

using namespace std;

array<bool, 4> Model::getProximity(vector<vector<int> > map, array<int, 2> location)
{
    int i = location[0];
    int j = location[1];
    
    int x = map.size();
    int y = map[0].size();
    
    array<bool, 4> walls;
    
    walls[0] = (i==0 || map[i-1][j] == -1);
    walls[1] = (j==y-1 || map[i][j+1] == -1);
    walls[2] = (i==x-1 || map[i+1][j] == -1);
    walls[3] = (j==0 || map[i][j-1] == -1);
    
    return walls;
}

array<int, 2> Model::getNewLocation(char action, array<int, 2> location, vector<vector<int>> dimensions)
{
    int x = dimensions.size();
    int y = dimensions[0].size();
    
    array<int, 2> newLocation = location;
    
    switch (action) {
        case 'l':
            if (location[1]!=0 && dimensions[location[0]][location[1]-1]!=-1)
                newLocation[1] -=1;
            break;
        case 'r':
            if (location[1]!=y-1 && dimensions[location[0]][location[1]+1]!=-1)
                newLocation[1] +=1;
            break;
        case 'u':
            if (location[0]!=0 && dimensions[location[0]-1][location[1]]!=-1)
                newLocation[0] -=1;
            break;
        case 'd':
            if (location[0]!=x-1 && dimensions[location[0]+1][location[1]]!=-1)
                newLocation[0] +=1;
            break;
        case 's': break;
    }
    return newLocation;
}

array<bool,4> Model::getDirections(vector<vector<int>> map, array<int, 2> location)
{
    vector<array<int, 2>> closestDirt;
    int closestDistance=-1;
    
    for (int i=0; i<map.size(); i++)
    {
        for (int j=0; j<map[0].size(); j++)
        {
            if (map[i][j] == 1)
            {
                int distance = abs(location[0]-i) + abs(location[1]-j);
                
                if (distance == closestDistance)
                    closestDirt.push_back({(i-location[0]), (j-location[1])});
                
                else if (distance < closestDistance || distance != -1)
                {
                    vector<array<int, 2>> closestDirt;
                    closestDirt.push_back({(i-location[0]), (j-location[1])});
                }
            }
        }
    }
    
    array<bool,4> directions = {false,false,false,false};
    
    if (closestDistance == -1) return directions;
    else
    {
        for (array<int, 2> coords: closestDirt)
        {
            int x=coords[0];
            int y=coords[1];
            array<bool,4> newDirt = {y>=abs(x), x>=abs(y), y<=-abs(x), x<=-abs(y)};
            
            for (int i=0; i<directions.size(); i++)
                directions[i] = directions[i]||newDirt[i];
        }
        
        return directions;
    }
    
}

vector<vector<int>> Model::getNewDimensions(char action, array<int,2> location, vector<vector<int>> dimensions)
{
    if (action=='s') dimensions[location[0]][location[1]] = false;
    return dimensions;
}

