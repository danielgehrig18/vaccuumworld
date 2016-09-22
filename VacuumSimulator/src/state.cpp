//
//  state.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 23/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/state.hpp"

template <class T>
void State<T>::Initialize(T data, vector<char> action_sequence, char action, int path_cost, int heuristic)
{
    data_ = data;
    heuristic_ = heuristic;
    path_cost_ = path_cost;
    action_sequence_ = action_sequence;
    action_sequence_.insert(action_sequence_.begin(), action);
};

template <class T>
vector<char> State<T>::GetActionSequence()
{
    return action_sequence_;
};

template <class T>
T State<T>::GetData()
{
    return data_;
}

template <class T>
int State<T>::GetPathCost()
{
    return path_cost_;
};

template <class T>
int State<T>::GetTotalCost()
{
    return path_cost_ + heuristic_;
}

template <class T>
bool CompareStates<T>::operator()(State<T> * state_1, State<T> * state_2)
{
    return state_1 -> GetTotalCost() > state_2 -> GetTotalCost();
};