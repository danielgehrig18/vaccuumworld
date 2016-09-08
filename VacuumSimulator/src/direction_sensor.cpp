//
//  direction_sensor.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 25/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/direction_sensor.hpp"

DirectionSensor::DirectionSensor()
{
    Sensor::SetName('d');
}

void DirectionSensor::SetValue(array<bool, 4> directions)
{
    if (Sensor::GetStatus())
    {
        value_ = directions;
    }
};

array<bool, 4> DirectionSensor::GetValue()
{
    return value_;
}