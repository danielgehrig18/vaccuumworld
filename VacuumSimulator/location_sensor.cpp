//
//  location_sensor.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 25/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "location_sensor.hpp"

LocationSensor::LocationSensor()
{
    Sensor::setName('l');
}

void LocationSensor::setValue(array<int, 2> location)
{
    if (Sensor::getStatus()) value = location;
};

array<int, 2> LocationSensor::getValue()
{
    return value;
}