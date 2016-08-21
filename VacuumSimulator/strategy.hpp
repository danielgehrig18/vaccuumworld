//
//  strategy.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 20/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef strategy_hpp
#define strategy_hpp

#include <array>
#include <vector>

using namespace std;

class Strategy {
private:
    char type;
    vector<char> actions = {'u', 'r', 'd', 'l', 's'};
public:
    char chooseAction(bool dirt, array<bool, 4> proximity);
    char moreGreedySearch(bool dirt, array<bool, 4>proximity);
    char greedySearch(bool dirtSensor);
    char randomSearch();
    void setType(char strategy);
};

#endif /* strategy_hpp */
