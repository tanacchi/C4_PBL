#include "Tester.hpp"

Tester::Tester(int cycle)
  : evshield(0x34, 0x36)
{
  evshield.init(SH_HardwareI2C);
 // for (int i = 0; i < SHIELD_TOUCH_NUM; i++) shield_touch[i].init(&evshield, i);
  shield_touch[0].init(&evshield, SH_BAS1);
  shield_touch[1].init(&evshield, SH_BAS2);
  evshield.bank_a.motorReset();
  Serial.begin(cycle);
  delay(2000);
}

Tester::~Tester()
{
}

int Tester::get_sensor()
{
  unsigned char sensor_byte = 0;
  for (int i = 0; i < 2; i++) sensor_byte |= (shield_touch[i].isPressed() << i);
  for (int i = 0; i < 6; i++)
    if (sensor_byte == get_two_pow(i)) return i + 1;
  return 0;
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
