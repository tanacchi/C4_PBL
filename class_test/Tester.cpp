#include "Tester.hpp"

Tester::Tester() {
  Serial.begin(9600);
}

Tester::~Tester() {
  Serial.write(0xff);
}

int Tester::get_sensor() {
  if (Serial.read() == 0xff) {
    
  }
}
