//
//  model.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 21/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef model_hpp
#define model_hpp

#include <stdio.h>
#include <array>
#include <vector>

using namespace std;

class Model
{
public:
    int getDirt(vector<vector<int>> map, array<int, 2> location);
    array<bool, 4> getProximity(vector<vector<int>> map, array<int, 2> location);
};

#endif /* model_hpp */
