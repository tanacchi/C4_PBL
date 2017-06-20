#include "Tester.hpp"

Tester tester();

// sensor1 << EV3     CH_1
// sensor4 << Shileld SH_BAS1

// motor1  << EV3     OUT_A
// motor4  << Shield  Bank_A.1

void setup() {
}

void loop() {
  if (tester.is_pressed(1)) tester.run_motor(4);
  if (tester.is_pressed(4)) tester.run_motor(1);
}