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
};

void State::SetParent(State* parent)
{
    parent_ = parent;
}

void State::AddChild(State* child)
{
    children_.push_back(child);
}

State* State::GetParent()
{
    return parent_;
};

vector<State*> State::GetChildren()
{
    return children_;
}

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

bool CompareStates::operator()(State state_1, State state_2)
{
    return state_1.GetTotalCost() < state_2.GetTotalCost();
};