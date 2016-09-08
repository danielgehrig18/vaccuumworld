//
//  proximity_sensor.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 25/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/proximity_sensor.hpp"

ProximitySensor::ProximitySensor()
{
    Sensor::setName('p');
}

void ProximitySensor::setValue(array<bool, 4> walls)
{
    if (Sensor::getStatus())
    {
        value_ = walls;
    }
};

array<bool, 4> ProximitySensor::getValue()
{
    return value_;
}
