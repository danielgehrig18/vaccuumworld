//
//  state.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "state.hpp"

State::~State()
{
    for (State* node: children) node->~State();
    delete this;
    
}