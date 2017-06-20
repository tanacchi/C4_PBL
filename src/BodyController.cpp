#include "../include/BodyController.hpp"

IBlockTouch::IBlockTouch()
{
}

void IBlockTouch::init(unsigned char port) {
  chnum = port;
}

bool IBlockTouch::is_pressed() {
  
}

BodyController::BodyController()
  : evshield(0x34, 0x36)
{
  evshield.init(SH_HardwareI2C);
  for (int i = 0; i < SHIELD_TOUCH_NUM; i++) shield_touch[i].init(&evshield, (SH_BankPort)i);
  for (int i = 0; i < BLOCK_TOUCH_NUM; i++) block_touch[i].init((unsigned char)i);
  delay(100);
}

bool BodyController::is_pressed(int ch) {
  for (int i = 0; i < BLOCK_TOUCH_NUM; i++);
}
