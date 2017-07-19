#include <Wire.h>
#include <Arduino.h>
#include <EVShield.h>
#include <EVs_EV3Touch.h>

#include "include/VirtualPlate.hpp"
#include "include/HandSeeker.hpp"

const int TaskInit   = 0;
const int TaskOp     = 1;
const int TaskSelect = 2;
const int TaskPut    = 3;
const int TaskJudge  = 4;
const int TaskEd     = 5;
const int TaskClone  = 6;

EVShield evshield(0x34, 0x36);
EVs_EV3Touch shield_sensor[2];

VirtualPlate plate;
HandSeeker* seeker;
int turn;
int task;
int select_x;

void setup()
{ // 最初の設定とか
turn  = 1;
task = TaskInit;
select_x = -1;
for (int i = 0; i < 2; i++) shield_sensor[i].init(&evshield, i);
Serial.begin(9600);
delay(2000);
}

void loop()
{
  if (task != TaskClose) task = run(task); 
  else exit(0);
}

int run(int task)
{
  switch (task) {
  case TaskInit:   return task_init();
  case TaskOp:     return task_op();
  case TaskSelect: return task_select();
  case TaskPut:    return task_put();
  case TaskJudge:  return task_judge();
  case TaskEd:     return task_ed();
  default:         return TaskClose;
  }
}

int task_init()
{
  return TaskOp;
}

int task_op()
{
  return TaskSelect;
}

int task_select()
{
  if (!(turn % 2)) {
    int pushed_sensor = 0, receive_b;
    while (pushed_sensor = get_sensor()) ;
    select_x = pushed_sensor;
  }
  else {
    seeker = new HandSeeker();
    select_x = (*seeker)(plate);
    delete seeker;
  }
  return (plate.is_valid_hand(select_x)) ? TaskPut : TaskSelect;
}

int task_put()
{
  plate_.insert(select_x);
      // evshield.bank_a.motorRunDegrees(
      //     SH_Motor_1,
      //     SH_Direction_Forward,
      //     1000,
      //     60,
      //     SH_Completion_Wait_For,
      //     SH_Next_Action_BrakeHold);
      //   delay(1000);    evshield.bank_a.motorRunDegrees(
      //     SH_Motor_1,
      //     SH_Direction_Forward,
      //     1000,
      //     60,
      //     SH_Completion_Wait_For,
      //     SH_Next_Action_BrakeHold);
      //   delay(1000);    evshield.bank_a.motorRunDegrees(
      //     SH_Motor_1,
      //     SH_Direction_Forward,
      //     1000,
      //     60,
      //     SH_Completion_Wait_For,
      //     SH_Next_Action_BrakeHold);
      //   delay(1000);
  return TaskJudge;
}

int task_judge()
{
  if (plate.is_game_finish()) return TaskEd; // 引き分けかどうかで分岐させたい
  else if (plate.can_continue())   return TaskEd;
  plate.switch_active_stone();
  turn++;
  return TaskSelect;
}

int task_ed()
{
  return TaskClose;
}

int get_sensor()
{
int sensor_data = 0;
sensor_data |= Serial.read();
  for (int i = 0; i < 2; i++) sensor_data |= (shield_touch[i].isPressed() << i+4);
  for (int i = 0; i < 6; i++)
  if (sensor_data = get_two_pow(i)) return i+1;
  return 0;
}

int get_two_pow(int src)
{
int dest = 1;
for (int i = 0; i < src; i++) dest *= 2;
return dest;
}