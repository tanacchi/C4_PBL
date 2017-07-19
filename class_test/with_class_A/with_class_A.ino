#include "Tester.hpp"

Tester tester(9600);

// sensor1 << EV3     CH_1
// sensor4 << Shileld SH_BAS1

// motor1  << EV3     OUT_A
// motor4  << Shield  Bank_A.1

void setup() {
}

void loop() {
  int sensor = tester.get_sensor();
  Serial.write(0x09);
 // while (!(sensor = tester.get_sensor())) ;
  if (sensor == 1) tester.run_motor(1);
  if (sensor == 2) tester.run_motor(2);
}
