//
//  proximity_sensor.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 21/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef proximity_sensor_hpp
#define proximity_sensor_hpp

#include <array>

#include "sensor.hpp"

using namespace std;

class ProximitySensor: public Sensor
{
private:
    array<bool, 4> value; // order is up, right, down, left
public:
    void setValue(array<bool, 4> walls) {if (Sensor::getStatus()) value = walls;};
    array<bool, 4> getValue() {return value;}
    ProximitySensor() {Sensor::setName('b');}
};

#endif /* proximity_sensor_hpp */
