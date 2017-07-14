#include <Wire.h>
#include <EVShield.h>
#include <EVs_EV3Touch.h>

#define IBLOCK_TOUCH_NUM 4
#define SHIELD_TOUCH_NUM (6 - IBLOCK_TOUCH_NUM)

class Ev3Block {
public:
  Ev3Block();
  ~Ev3Block();
  unsigned char get_ev_sensor();
};

class Tester {
public:
  Tester();
  ~Tester();
  int get_sensor();
  void run_motor(int);
  int get_two_pow(unsigned int n);
private:
  Ev3Block ev3_block;
  EVShield evshield;
  EVs_EV3Touch shield_touch[SHIELD_TOUCH_NUM];
};
