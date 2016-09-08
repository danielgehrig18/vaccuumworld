//
//  state.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/state.hpp"

void State::init(array<int, 2> loc, char action, int pathC, int heur)
{
    location_ = loc;
    heuristic_ = heur;
    pathCost_ = pathC;
};

void State::setParent(State* p)
{
    parent_ = p;
}

void State::addChild(State* c)
{
    children_.push_back(c);
}

State* State::getParent()
{
    return parent_;
};

vector<State*> State::getChildren()
{
    return children_;
}

char State::getAction()
{
    return action_;
};

array<int, 2> State::getLocation()
{
    return location_;
}

int State::getPathCost()
{
    return pathCost_;
};

int State::getTotalCost()
{
    return pathCost_ + heuristic_;
}

bool State::isRoot()
{
    return !parent_;
};

bool CompareStates::operator()(State s1, State s2)
{
    return s1.getTotalCost() < s2.getTotalCost();
};
