#include <Wire.h>
#include <EVShield.h>
#include <EVs_EV3Touch.h>

EVShield evshield(0x34, 0x36);
EVs_EV3Touch touch;

void setup() {
  evshield.init( SH_HardwareI2C );
  evshield.bank_a.motorReset();

  touch.init( &evshield, SH_BAS1);
  setMode ????
  touch.resetBumpCount();
  //  evshield.waitForButtonPress(BTN_GO);
}

void loop() {
  if (touch.getBumpCount() % 2) {
    evshield.bank_a.motorRunDegrees(SH_Motor_1,
                                    SH_Direction_Reverse,
                                    10,
                                    30,
                                    SH_Completion_Dont_Wait,
                                    SH_Next_Action_Brake);
    delay(30);
  }
}
