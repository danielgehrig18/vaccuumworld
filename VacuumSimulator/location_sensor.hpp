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
private:
    array<int, 2> value;
public:
    void setValue(array<int, 2> location) {if (Sensor::getStatus()) value = location;};
    array<int, 2> getValue() {return value;}
    LocationSensor() {Sensor::setName('l');}
};

#endif /* location_sensor_hpp */