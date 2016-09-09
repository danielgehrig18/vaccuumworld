//
//  location_sensor.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 25/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/location_sensor.hpp"

LocationSensor::LocationSensor()
{
    Sensor::SetName('l');
}

void LocationSensor::SetValue(array<int, 2> location)
{
    if (Sensor::GetStatus())
    {
        value_ = location;
    }
};

array<int, 2> LocationSensor::GetValue()
{
    return value_;
}