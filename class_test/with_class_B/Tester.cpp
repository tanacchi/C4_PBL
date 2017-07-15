#include "Tester.hpp"

Tester::Tester()
  : evshield(0x34, 0x36)
{
  evshield.init(SH_HardwareI2C);
  evshield.bank_a.motorReset();

  Serial.begin(9600);
  delay(2000);
}

Tester::~Tester()
{
}

int Tester::get_sensor()
{
  // unsigned char sensor_byte = 0;
  // sensor_byte = Serial.read();
  // if (sensor_byte == get_two_pow(i)) return i + 1;
  // return 0;
  return Serial.read();
}

int Tester::get_two_pow(unsigned int n)
{
  int answer = 1;
  for (int i = 0; i < n; i++) answer *= 2;
  return answer;
}

void Tester::run_motor(int ch)
{
  if (ch == 1)
    evshield.bank_a.motorRunDegrees(SH_Motor_1,
                                    SH_Direction_Reverse,
                                    10,
                                    300,
                                    SH_Completion_Dont_Wait,
                                    SH_Next_Action_Brake);
  if (ch == 2)
    evshield.bank_a.motorRunDegrees(SH_Motor_2,
                                    SH_Direction_Reverse,
                                    10,
                                    300,
                                    SH_Completion_Dont_Wait,
                                    SH_Next_Action_Brake);
  delay(100);
}
