#include <Wire.h>
#include <EVShield.h>
#include <EVs_EV3Touch.h>

class Tester {
public:
  Tester();
  ~Tester();
  int get_sensor();
  void run_motor(int);
  int get_two_pow(unsigned int n);
private:
  EVShield evshield;
  EVs_EV3Touch shield_touch[2];
};
