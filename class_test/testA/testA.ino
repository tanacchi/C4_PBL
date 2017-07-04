#include <Wire.h>
#include <Arduino.h>
#include <EVShield.h>
#include <EVs_EV3Touch.h>

EVShield evshield(0x34, 0x36);
EVs_EV3Touch touch[4];

byte sendData[4];
void setup()
{
  for (int i = 0; i < 4; i++)
    sendData[i] = 0x00;
  sendData[0] = 0x02;
  sendData[3] = 0x03;
  evshield.init( SH_HardwareI2C );
   touch[0].init( &evshield, SH_BAS1);
   touch[1].init( &evshield, SH_BAS2);
   touch[2].init( &evshield, SH_BBS1);
   touch[3].init( &evshield, SH_BBS2);
  Serial.begin(9600);
}
void loop()
{
  int analogData = 0;
  if (Serial.available() > 0)
  {
    if (Serial.read() == 0x05)
    {
      sendData[2] = 0x00;
      for (int i = 0; i < 4; i++)
        sendData[2] |=(touch[i].isPressed() << i);
      for (int i = 0; i < 4; i++)
        Serial.write(sendData[i]);
    }
  }
}

