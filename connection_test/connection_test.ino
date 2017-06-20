#include <Wire.h>
#include <Arduino.h>
#include <EVShield.h>
#include <EVs_EV3Touch.h>

byte sendData[4];

EVShield evshield(0x34, 0x36);
EVs_EV3Touch touch;

int count = 0;

void setup()
{
  evshield.init( SH_HardwareI2C );
  touch.init( &evshield, SH_BAS1);

  for (int i = 0; i < 4; i++)
    sendData[i] = 0x00;
  sendData[0] = 0x02;
  sendData[3] = 0x03;
  Serial.begin(9600);
}
void loop()
{
  int analogData = 0;
  if (Serial.available() > 0)
  {
    if (Serial.read() == 1) {
      evshield.bank_a.motorRunDegrees(SH_Motor_1,
                                      SH_Direction_Reverse,
                                      10,
                                      30,
                                      SH_Completion_Dont_Wait,
                                      SH_Next_Action_Brake);
      delay(30);
    }
  }
  if (count++ > 100000) exit(0);
}
