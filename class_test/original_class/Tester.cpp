#include "Tester.hpp"

Ev3Block::Ev3Block()
{
 Serial.begin(9600);
  delay(2000);
}

Ev3Block::~Ev3Block()
{
}

unsigned char Ev3Block::get_ev_sensor()
{
  unsigned char receive_data = 0;
  while (!(receive_data = Serial.read())) ;
  return receive_data;
}

Tester::Tester()
  :  ev3_block(),
     evshield(0x34, 0x36)
{
  evshield.init(SH_HardwareI2C);
 // for (int i = 0; i < SHIELD_TOUCH_NUM; i++) shield_touch[i].init(&evshield, i);
  shield_touch[0].init(&evshield, SH_BAS1);
  shield_touch[1].init(&evshield, SH_BAS2);
  evshield.bank_a.motorReset();
}

Tester::~Tester()
{
}

int Tester::get_sensor()
{
  unsigned char sensor_byte = ev3_block.get_ev_sensor();
  for (int i = 0; i < SHIELD_TOUCH_NUM; i++)
    sensor_byte |= (shield_touch[i].isPressed() << (i + IBLOCK_TOUCH_NUM));
//  for (int i = 0; i < 6; i++)
//    if (sensor_byte == get_two_pow(i)) return i + 1;
//  return 0;
  return sensor_byte;
}

int Tester::get_two_pow(unsigned int n)
{
  int answer = 1;
  for (int i = 0; i < n; i++) answer *= 2;
  return answer;
}

void Tester::run_motor(int ch)
{
  evshield.bank_a.motorRunDegrees(ch,
                                  SH_Direction_Reverse,
                                  10,
                                  300,
                                  SH_Completion_Dont_Wait,
                                  SH_Next_Action_Brake);
  delay(100);
}


