#include <Wire.h>
#include <EVShield.h>
#include <EVs_EV3Touch.h>

#define IBLOCK_TOUCH_NUM 3
#define SHIELD_TOUCH_NUM (6 - IBLOCK_TOUCH_NUM)

class Ev3Block {
  Ev3Block() = default;
  ~Ev3Block() = default;
  void init(int port);
  bool is_pressed();
private:
  unsigned char port;
};

class Tester {
public:
  Tester();
  ~Tester();
  int get_sensor();
  void run_motor(int);
private:
  IBlockTouch  bock_touch[IBLOCK_TOUCH_NUM];
  EVs_EV3Touch shield_touch[SHIELD_TOUCH_NUM];
};
