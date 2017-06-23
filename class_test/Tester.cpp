#include "Tester.hpp"

Tester::Tester() {
  Serial.begin(9600);
}

Tester::~Tester() {
  Serial.write(0xff);
}

int Tester::get_sensor() {
  unsigned char sensor_data = 0x00;
  if (Serial.read() == 0xff) {
    Serial.write(0x0f);
    sensor_data = Serial.read();
  }
}

void Tester::run_motor() {
  if (Serial.read() == 0xff) {

  }
}
