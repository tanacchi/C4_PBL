#include <Wire.h>
#include <EVShield.h>
EVShield evshield(0x34, 0x36);

byte receive_data, receive_buff;

void setup()
{
  Serial.begin(9600);
  delay(2000);
  char str[40];
  evshield.init( SH_HardwareI2C );
  evshield.bank_a.motorReset();

  receive_data = 0x00;

}

void loop()
{
  if (Serial.available() > 0) {
    Serial.write(receive_buff);
    receive_buff = 0;
    if ((receive_buff = Serial.read()) != receive_data) {
      receive_data = receive_buff;
      // Serial.write(0x08);
      // Serial.write(receive_data);
      if (receive_data == 1) {
        evshield.bank_a.motorRunDegrees(
          SH_Motor_1,
          SH_Direction_Forward,
          1000,
          60,
          SH_Completion_Wait_For,
          SH_Next_Action_BrakeHold);
        delay(1000);
      }
      else if (receive_data == 2) {
        evshield.bank_a.motorRunDegrees(
          SH_Motor_2,
          SH_Direction_Reverse,
          1000,
          60,
          SH_Completion_Wait_For,
          SH_Next_Action_BrakeHold);
        delay(1000);
      }
    }
  }
}
