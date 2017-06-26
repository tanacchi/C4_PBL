#include <Wire.h>
#include <EVShield.h>
#include <EVs_EV3Touch.h>

#define IBLOCK_TOUCH_NUM 4
#define SHIELD_TOUCH_NUM (6 - IBLOCK_TOUCH_NUM)

class Ev3Block {
  Ev3Block();
  ~Ev3Block();
  void init(int port);
  unsigned char get_ev_sensor();
  void run_ev_motor();
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
  Ev3Block     ev3_block;
  EVs_EV3Touch shield_touch[SHIELD_TOUCH_NUM];
};
