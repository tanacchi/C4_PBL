#include <Wire.h>
#include <EVShield.h>
EVShield evshield(0x34, 0x36);
void setup()
{
  Serial.begin(9600); // start serial for output
  delay(2000); // wait two seconds, allowing time to // activate the serial monitor
  char str[40]; 
  evshield.init( SH_HardwareI2C );
  evshield.bank_a.motorReset();
  evshield.bank_b.motorReset();
  Serial.println ("Press GO button to continue");
  evshield.waitForButtonPress(BTN_GO);
}
void loop() 
{

if (Serial.available() > 0 && Serial.read() == 0x05) {
  byte sensor_data = Serial_read();   // タイムラグが怖い

  int i;
  if (sensor_data == 8) {
    evshield.bank_a.motorRunDegrees(SH_Motor_1,
    SH_Direction_Forward, 5,
    60,
    SH_Completion_Wait_For,
    SH_Next_Action_BrakeHold);
    evshield.bank_a.motorRunDegrees(SH_Motor_1,
    SH_Direction_Reverse,
    5,
    90,
    SH_Completion_Wait_For,
    SH_Next_Action_BrakeHold);
  } 
  else if (sensor_data == 4){
    evshield.bank_a.motorRunDegrees(SH_Motor_2,
    SH_Direction_Reverse,
    5,
    30,
    SH_Completion_Wait_For,
    SH_Next_Action_BrakeHold);
    //delay(5);
  }
   else if (sensor_data == 2) {
    evshield.bank_b.motorRunDegrees(SH_Motor_1,
    SH_Direction_Forward, 5,
    60,
    SH_Completion_Wait_For,
    SH_Next_Action_BrakeHold);
    evshield.bank_a.motorRunDegrees(SH_Motor_1,
    SH_Direction_Reverse,
    5,
    90,
    SH_Completion_Wait_For,
    SH_Next_Action_BrakeHold);
  } 
  else if(sensor_data == 1) {
    evshield.bank_b.motorRunDegrees(SH_Motor_2,
    SH_Direction_Reverse,
    5,
    30,
    SH_Completion_Wait_For,
    SH_Next_Action_BrakeHold);
    //delay(5);
  }
  }
}
