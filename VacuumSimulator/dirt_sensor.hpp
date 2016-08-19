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

class DirtSensor: public Sensor
{
private:
    bool value;
public:
    void setValue(bool dirt) {value = dirt;};
    bool getValue() {if (Sensor::getStatus()) {return value;} else {return false;}}
    void setName() {Sensor::setName('d');}
};

#endif /* dirt_sensor_hpp */