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

State* State::childOf(array<int,2> location, int h)
{
    State child = State(location, pathCost+1, h);
    child.setParent(this);
    this->addChild(&child);
    
    return &child;
}