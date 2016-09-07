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
    Sensor::setName('d');
}

void DirtSensor::setValue(bool dirt)
{
    if (Sensor::getStatus()) value = dirt;
}

bool DirtSensor::getValue()
{
    return value;
}
