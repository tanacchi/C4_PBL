#ifndef BODY_CONTROLLER_H_
#define BODY_CONTROLLER_H_

#include <EVShield.h>
#include <EVs_EV3Touch.h>

#define SHIELD_TOUCH_NUM 3
#define BLOCK_TOUCH_NUM  3

class IBlockTouch {
  unsigned char chnum;
public:
  IBlockTouch();
  void init();
  bool is_pressed();
}

class BodyController {
  Evshield evshield;
  Evs_EV3Touch shield_touch[SHIELD_TOUCH_NUM];
  IBlockTouch  block_touch[BLOCK_TOUCH_NUM];
public:
  BodyController();
  bool is_pressed(int ch);
}; 

#endif // BODY_CONTROLLER_H_
