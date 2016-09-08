//
//  dirt_sensor.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 19/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef dirt_sensor_hpp
#define dirt_sensor_hpp

#include "vaccuumworld/sensor.hpp"

class DirtSensor: public Sensor
{
public:
    /**
        Constructor of dirtsensor. Default name of sensor is 'd'.
     
        @param: -
    */
    DirtSensor();
    
    /**
        Set the value of sensor. Only possible if sensor status is true.
     
        @param: dirt: presence of dirt under agent.
    */
    void setValue(bool dirt);
    
    /**
        Return value of sensor.
     
        @param: -
    */
    bool getValue();

private:
    bool value_;
};

#endif /* dirt_sensor_hpp */
