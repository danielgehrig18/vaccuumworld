//
//  actuator.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 02/09/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef actuator_hpp
#define actuator_hpp

#include <vector>

class Actuator
{
public:
    void init();
    char execute(char action);
    
private:
    bool status;
    vector<char> possibleActions;
    
};

#endif /* actuator_hpp */
