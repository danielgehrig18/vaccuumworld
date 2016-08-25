//
//  proximity_sensor.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 25/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "proximity_sensor.hpp"


void ProximitySensor::setValue(array<bool, 4> walls)
{
    if (Sensor::getStatus()) value = walls;
};

array<bool, 4> ProximitySensor::getValue()
{
    return value;
}

ProximitySensor::ProximitySensor()
{
    Sensor::setName('p');
}

