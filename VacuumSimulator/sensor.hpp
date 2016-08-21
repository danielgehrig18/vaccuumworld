//
//  sensor.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 09/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef sensor_hpp
#define sensor_hpp

#include <stdio.h>

class Sensor
{
private:
    char name;
    bool status=true;
public:
    void setName(char sensorName) {name = sensorName;};
    bool getStatus() {return status;};
};

#endif /* sensor_hpp */