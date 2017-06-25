#include "Tester.hpp"

void Ev3Block::init(int )
{
}

unsigned char Ev3Block::get_ev_sensor() {

}

Tester::Tester() {
  Serial.begin(9600);
}

Tester::~Tester() {
  Serial.write(0xff);
}

int Tester::get_sensor() {
  unsigned char sensor_byte = 0x00;
  while (Serial.read() != 0xff) delay(10);
  for (int i = 0; i < 4; i++) Serial.write(0x0f);
  sensor_byte = Serial.read();
}

void Tester::run_motor(int ch) {
  while (Serial.read() != 0xff) delay(10);
  for ()
}
