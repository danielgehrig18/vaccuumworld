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
    Sensor::setName('d');
}

void DirectionSensor::setValue(array<bool, 4> directions)
{
    if (Sensor::getStatus())
    {
        value_ = directions;
    }
};

array<bool, 4> DirectionSensor::getValue()
{
    return value_;
}
