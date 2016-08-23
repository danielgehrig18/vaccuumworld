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
#include <queue>

using namespace std;

class Strategy {
private:
    char type;
    vector<char> actions = {'u', 'r', 'd', 'l', 's'};
    queue<char> plan;
    
public:
    bool actionPlanned() {return !plan.empty();};
    void planAction(bool dirt, array<bool, 4> proximity, array<bool, 4> direction,
                    array<int, 2> location, vector<vector<int>> state);
    char executeAction();
    
    char moreGreedySearch(bool dirt, array<bool, 4>proximity);
    char greedySearch(bool dirt);
    char randomSearch();
    char superGreedySearch(bool dirt, array<bool, 4> proximity, array<bool, 4> direction);
    vector<char> stateSearch(array<int, 2> location, vector<vector<int>> state);
    void setType(char strategy);
};

#endif /* strategy_hpp */
