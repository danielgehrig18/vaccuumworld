//
//  sensor.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 24/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/sensor.hpp"

void Sensor::SetName(char sensor_name)
{
    name_ = sensor_name;
}

bool Sensor::GetStatus()
{
    return status_;
};

void Sensor::Initialize()
{
    status_ = true;
};