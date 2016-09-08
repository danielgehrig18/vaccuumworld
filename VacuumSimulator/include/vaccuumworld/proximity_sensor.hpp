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

#include "vaccuumworld/sensor.hpp"

using namespace std;

class ProximitySensor: public Sensor
{
public:
    /**
        Constructor of proximity sensor. Default name of sensor is 'p'.
     
        @param: -
    */
    ProximitySensor();
    
    /**
        Set the value of sensor. Only possible if sensor status is true.
     
        @param: walls: presence of walls in order (up, right, down, left).
    */
    void setValue(array<bool, 4> walls);
    
    /**
        Return value of sensor.
     
        @param: -
    */
    array<bool, 4> getValue();

private:
    array<bool, 4> value_;
};

#endif /* proximity_sensor_hpp */
