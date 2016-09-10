//
//  state.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/state.hpp"

void State::Initialize(array<int, 2> location, char action, int path_cost, int heuristic)
{
    location_ = location;
    heuristic_ = heuristic;
    path_cost_ = path_cost;
    action_ = action;
};

void State::PushChild(State * child)
{
    children_.push_back(child);
}

void State::RemoveChild(int index)
{
    children_.erase(children_.begin() + index);
}

void State::SetParent(State* parent)
{
    parent_ = parent;
    parent -> PushChild(this);
}

vector<State*> State::GetChildren()
{
    return children_;
}

State* State::GetParent()
{
    return parent_;
};

char State::GetAction()
{
    return action_;
};

array<int, 2> State::GetLocation()
{
    return location_;
}

int State::GetPathCost()
{
    return path_cost_;
};

int State::GetTotalCost()
{
    return path_cost_ + heuristic_;
}

bool State::IsRoot()
{
    return !parent_;
};

bool CompareStates::operator()(State * state_1, State * state_2)
{
    return state_1 -> GetTotalCost() > state_2 -> GetTotalCost();
};