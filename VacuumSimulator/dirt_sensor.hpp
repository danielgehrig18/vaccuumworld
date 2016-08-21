//
//  dirt_sensor.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 19/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef dirt_sensor_hpp
#define dirt_sensor_hpp

#include <stdio.h>

#include "sensor.hpp"

class DirtSensor: public Sensor
{
private:
    bool value;
public:
    void setValue(bool dirt) {if (Sensor::getStatus()) value = dirt;};
    bool getValue() {return value;}
    DirtSensor() {Sensor::setName('d');}
};

#endif /* dirt_sensor_hpp */