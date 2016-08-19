//
//  location_sensor.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 19/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef location_sensor_hpp
#define location_sensor_hpp

#include <stdio.h>
#include <string.h>
#include "sensor.hpp"

class LocationSensor: public Sensor
{
private:
    int value[2];
public:
    void setValue(int location[2]) {memcpy(value,location,sizeof(value));};
    int* getValue() {if (Sensor::getStatus()) {return value;} else {return nullptr;}}
    LocationSensor() {Sensor::setName('l');}
};

#endif /* location_sensor_hpp */