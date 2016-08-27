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
public:
    /**
        sets the name for the sensor: 'd' dirt sensor, 'p' proximity sensor, 'r'
        direction sensor, 'l' location sensor.
     
        @param: sensorName: name of the sensor.
    */
    void setName(char sensorName);
    
    /**
        Gets the status of the sensor. Status == false means that a sensor value
        cannot be written.
     
        @param: -.
     */
    bool getStatus();
    
    /**
        Sets the status of the sensor to active, meaning that values can be 
        written.
     
        @param: -.
     */
    void init();
    
private:
    char name;
    bool status=false;
};

#endif /* sensor_hpp */