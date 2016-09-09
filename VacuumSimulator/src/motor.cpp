//
//  motor.cpp
//  vacuumworld
//
//  Created by Daniel Gehrig on 08/09/16.
//
//

#include "vaccuumworld/motor.hpp"

Motor::Motor()
{
    SetPossibleActions({'u', 'r', 'l', 'd'});
}