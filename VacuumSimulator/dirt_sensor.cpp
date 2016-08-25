//
//  dirt_sensor.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 25/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "dirt_sensor.hpp"

void DirtSensor::setValue(bool dirt)
{
    if (Sensor::getStatus()) value = dirt;
}

bool DirtSensor::getValue()
{
    return value;
}

DirtSensor::DirtSensor()
{
    Sensor::setName('d');
}