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
    bool status=false;
public:
    void setName(char sensorName);
    bool getStatus();
    void init();
};

#endif /* sensor_hpp */