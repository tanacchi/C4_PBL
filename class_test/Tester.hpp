#include <Wire.h>
#include <EVShield.h>
#include <EVs_EV3Touch.h>

#define IBLOCK_TOUCH_NUM 3
#define SHIELD_TOUCH_NUM (6 - IBLOCK_TOUCH_NUM)

class IBlockTouch {
  IBlockTouch();
  void init();
private:
  unsigned char port;
};

class Tester {
public:
  Tester();
  bool is_pressed();
  void run_motor(int);
private:
  IBlockTouch  bock_touch[IBLOCK_TOUCH_NUM];
  EVs_EV3Touch shield_touch[SHIELD_TOUCH_NUM];
};
