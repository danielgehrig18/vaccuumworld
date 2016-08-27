//
//  location_sensor.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 22/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef location_sensor_hpp
#define location_sensor_hpp

#include <array>

#include "sensor.hpp"

using namespace std;

class LocationSensor: public Sensor
{
public:
    /**
        Constructor of location sensor. Default name of sensor is 'l'.
     
        @param: -
    */
    LocationSensor();
    
    /**
        Set the value of sensor. Only possible if sensor status is true.
     
        @param: location: coordinates of the agent.
    */
    void setValue(array<int, 2> location);
    
    /**
        Return value of sensor.
     
        @param: -
    */
    array<int, 2> getValue();
    
private:
    array<int, 2> value;
};

#endif /* location_sensor_hpp */