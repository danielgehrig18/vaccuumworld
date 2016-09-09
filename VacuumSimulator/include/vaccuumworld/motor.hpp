//
//  motor.hpp
//  vacuumworld
//
//  Created by Daniel Gehrig on 08/09/16.
//
//

#ifndef motor_hpp
#define motor_hpp

#include "actuator.hpp"

class Motor : public Actuator
{
public:
    /**
        Sets the possible actions to up, right, down, left.
     
        @param: -
    */
    Motor();
};

#endif /* motor_hpp */