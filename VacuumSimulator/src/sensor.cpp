//
//  sensor.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 24/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/sensor.hpp"

void Sensor::setName(char sensorName)
{
    name = sensorName;
}

bool Sensor::getStatus()
{
    return status;
};

void Sensor::init()
{
    status=true;
};
