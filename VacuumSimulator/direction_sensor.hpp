//
//  direction_sensor.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 22/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef direction_sensor_hpp
#define direction_sensor_hpp

#include <array>

#include "sensor.hpp"

using namespace std;

class DirectionSensor: public Sensor
{
private:
    array<bool, 4> value; // order is up, right, down, left
public:
    void setValue(array<bool, 4> directions);
    array<bool, 4> getValue();
    DirectionSensor();
};

#endif /* direction_sensor_hpp */
