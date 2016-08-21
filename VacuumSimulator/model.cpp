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
    
    (i==0 || map[i-1][j] == -1) ? walls[3] = true : walls[3] = false;
    (i==x-1 || map[i+1][j] == -1) ? walls[1] = true : walls[1] = false;
    (j==0 || map[i][j-1] == -1) ? walls[0] = true : walls[0] = false;
    (i==y-1 || map[i][j+1] == -1) ? walls[2] = true : walls[2] = false;
    
    return walls;
}

int Model::getDirt(vector<vector<int>> map, array<int, 2> location)
{
    return map[location[0]][location[1]];
}