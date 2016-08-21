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

using namespace std;

class Strategy {
private:
    char type;
    char actions[6] = {'u', 'd', 'l', 'r', 's', 'n'};
public:
    char chooseAction(array<int, 2> locationSensorValue, bool dirtSensorValue);
    void setType(char strategy);
};

#endif /* strategy_hpp */
