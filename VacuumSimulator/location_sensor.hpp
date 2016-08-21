//
//  location_sensor.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 19/08/16.
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
    void setValue(array<int, 2> location) {value = location;};
    array<int, 2> getValue() {if (Sensor::getStatus()) {return value;} else {return {0,0};}}
    LocationSensor() {Sensor::setName('l');}
};

#endif /* location_sensor_hpp */