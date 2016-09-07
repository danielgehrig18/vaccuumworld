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

#include "vaccuumworld/sensor.hpp"

using namespace std;

class DirectionSensor: public Sensor
{
public:
    /**
        Constructor of direction sensor. Default name of sensor is 'r'.
     
        @param: -
    */
    DirectionSensor();
    
    /**
        Set the value of sensor. Only possible if sensor status is true.
     
        @param: directions: direction of closest dirt in order (up, right, 
                down, left).
    */
    void setValue(array<bool, 4> directions);
    
    /**
        Return value of sensor.
     
        @param: -
    */
    array<bool, 4> getValue();
    
private:
    array<bool, 4> value;
};

#endif /* direction_sensor_hpp */
