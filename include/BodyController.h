#ifndef BODY_CONTROLLER_H_
#define BODY_CONTROLLER_H_

#include <EVShield.h>
#include <EVs_EV3Touch.h>

#define LANE_NUM 6

class BodyController {
  Evshield evshield;
  Evs_EV3Touch touch_sensor[LANE_NUM];
 public:
  BodyController();  
}; 

#endif // BODY_CONTROLLER_H_
