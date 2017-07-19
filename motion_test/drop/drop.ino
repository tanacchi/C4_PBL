#include <Wire.h>
#include <Arduino.h>
#include <EVShield.h>
#include <EVs_EV3Touch.h>

EVShield evshield(0x34, 0x36);
EVs_EV3Touch shield_sensor[2];

void setup() {
  evshield.init(SH_HardwareI2C);
  evshield.bank_a.motorReset();
  shield_sensor[0].init(&evshield, SH_BAS1);
  shield_sensor[1].init(&evshield, SH_BAS2);
}

void loop() {
  if (shield_sensor[0].isPressed()) {
    evshield.bank_a.motorRunRotations(
      SH_Motor_1,
      SH_Direction_Forward,
      30,
      1,
      SH_Completion_Wait_For,
      SH_Next_Action_Brake
    );
    exit(1);
  }
  else if (shield_sensor[1].isPressed()) {
    evshield.bank_a.motorRunRotations(
      SH_Motor_1,
      SH_Direction_Reverse,
      30,
      1,
      SH_Completion_Wait_For,
      SH_Next_Action_Brake
    );
    exit(0);
  }
  else {
    evshield.bank_a.motorStop(
      SH_Motor_Both,
      SH_Next_Action_Brake
    );
  }
}
