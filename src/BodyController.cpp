#include "../include/BodyController.hpp"

BodyController::BodyController()
  : evshield(0x34, 0x36)
{
  evshield.init(SH_HardwareI2C);
  for (int i = 0; i < LANE_NUM; i++) touch[i].init(&evshield, i);
}
