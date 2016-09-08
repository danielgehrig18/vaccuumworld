//
//  dirt_sensor.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 25/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/dirt_sensor.hpp"

DirtSensor::DirtSensor()
{
    Sensor::SetName('d');
}

void DirtSensor::SetValue(bool dirt)
{
    if (Sensor::GetStatus())
    {
        value_ = dirt;
    }
}

bool DirtSensor::GetValue()
{
    return value_;
}