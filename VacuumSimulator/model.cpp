//
//  model.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 21/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "model.hpp"

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

array<int, 2> Model::getLocation(char action, array<int, 2> location, vector<vector<int>> dimensions)
{
    int x = dimensions.size();
    int y = dimensions[0].size();
    
    array<int, 2> newLocation = location;
    
    switch (action) {
        case 'l':
            if (location[1]!=0) if(dimensions[location[0]][location[1]-1]!=-1)
                newLocation[1] -=1;
                break;
        case 'r':
            if (location[1]!=y-1) if(dimensions[location[0]][location[1]+1]!=-1)
                newLocation[1] +=1;
                break;
        case 'u':
            if (location[0]!=0) if (dimensions[location[0]-1][location[1]]!=-1)
                newLocation[0] -=1;
                break;
        case 'd':
            if (location[0]!=x-1) if(dimensions[location[0]+1][location[1]]!=-1)
                newLocation[0] +=1;
                break;
        case 's': break;
    }
    return newLocation;
}

int Model::getDirt(vector<vector<int>> map, array<int, 2> location)
{
    return map[location[0]][location[1]];
}