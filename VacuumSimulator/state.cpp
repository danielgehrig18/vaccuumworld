//
//  state.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "state.hpp"

State::State(array<int, 2> loc, char action, int pathC, int heur)
{
    location = loc;
    heuristic = heur;
    pathCost = pathC;
};

State::~State()
{
    for (State* node : children) node -> ~State();
    delete this;
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

bool State::isRoot()
{
    return !parent;
};

bool CompareStates::operator()(State* s1, State* s2)
{
    return s1 -> getTotalCost() < s2 -> getTotalCost();
};