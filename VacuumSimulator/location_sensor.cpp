//
//  location_sensor.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 25/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "location_sensor.hpp"

void LocationSensor::setValue(array<int, 2> location)
{
    if (Sensor::getStatus()) value = location;
};

array<int, 2> LocationSensor::getValue()
{
    return value;
}

LocationSensor::LocationSensor()
{
    Sensor::setName('l');
}

#endif /* location_sensor_hpp */