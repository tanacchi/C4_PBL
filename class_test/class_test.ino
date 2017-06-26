#include "Tester.hpp"

Tester tester();

// sensor1 << EV3     CH_1
// sensor4 << Shileld SH_BAS1

// motor1  << EV3     OUT_A
// motor4  << Shield  Bank_A.1

void setup() {
}

void loop() {
  int sensor = tester.get_sensor();
  if (sensor == 1) run_motor(4);
  if (sensor == 4) run_motor(1);
}