#include "Tester.hpp"

Ev3Block::Ev3Block() {
  Serial.begin(9600);
}

Ev3Block::~Ev3Block() {
  Serial.write(0xff);
}

void Ev3Block::init(int ch)
{
}

unsigned char Ev3Block::get_ev_sensor() {
  unsigned char sensor_byte = 0x00;
  while (Serial.read() != 0xff) delay(10);
  for (int i = 0; i < 4; i++) Serial.write(0x0f);
  sensor_byte = Serial.read();
  return sensor_byte;
}

void Ev3Block::run_ev_motor(int ch) {
  while (Serial.read() != 0xff) delay(10);
  Serial.write(0xf0);
  Serial.write(1);
  Serial.write(100);
  Serial.write(11);
  delay(11);
}

Tester::Tester() :ev3_block(),
    evshield(0x34, 0x36)
{
}

Tester::~Tester()
{
}

int Tester::get_sensor() {
  unsigned char sensor_byte = 0x00;
  sensor_byte |= (ev3_block.get_ev_sensor() << 1);
  for (int i = 0; i < SHIELD_TOUCH_NUM; i++)
    sensor_byte |= (shield_touch[i].isPressed() << (i+IBLOCK_TOUCH_NUM));  
  for (int i = 0; i < 6; i++)
    if (sensor_byte == get_two_pow(i)) return i+1;
  return 0;
}

int Tester::get_two_pow(unsigned int n) {
  int answer = 1;
  for (int i = 0; i < n; i++) answer *= 2;
  return answer;
}

void Tester::run_motor(int ch) {
  if (0 < ch && ch <= IBLOCK_TOUCH_NUM) ev3_block.run_ev_motor(ch);
  else if (ch <= 6) {
    evshield.bank_a.motorRunDegrees(ch - 4,
                                    SH_Direction_Reverse,
                                    10,
                                    30,
                                    SH_Completion_Dont_Wait,
                                    SH_Next_Action_Brake);
    delay(30);
  }
}
