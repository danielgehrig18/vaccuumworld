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

bool State::operator()(State s1, State s2)
{
    return s1.getTotalCost()<s2.getTotalCost();
}

bool State::isRoot()
{
    return !parent;
};

char State::getAction()
{
    return action;
};

array<int, 2> State::getLocation()
{
    return location;
}

int State::getPathCost()
{
    return pathCost;
};

int State::getTotalCost()
{
    return pathCost + heuristic;
}

void State::setParent(State* p)
{
    parent = p;
}

void State::addChild(State* c)
{
    children.push_back(c);
}

State* State::getParent()
{
    return parent;
};

bool State::operator==(State s)
{
    return location==s.getLocation();
};

State::State(array<int,2> loc, int p, int h)
{
    location = loc; heuristic = h; pathCost = p;
};