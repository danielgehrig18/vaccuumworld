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
     
        @param: sensor_name: name of the sensor.
    */
    void SetName(char sensor_name);
    
    /**
        Gets the status of the sensor. Status == false means that a sensor value
        cannot be written.
     
        @param: -.
     */
    bool GetStatus();
    
    /**
        Sets the status of the sensor to active, meaning that values can be 
        written.
     
        @param: -.
     */
    void Initialize();
    
private:
    char name_;
    bool status_ = false;
};

#endif /* sensor_hpp */