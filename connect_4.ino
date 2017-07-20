#include <Arduino.h>
#include <Wire.h>
#include <EVShield.h>
#include <Evs_EV3Touch.h>

#include "include/VirtualPlate.hpp"
#include "include/HandSeeker.hpp"

EVShield evshield(0x34, 0x36);
EVs_EV3Touch shield_sensor[2];

const int TaskInit   = 0;
const int TaskOp     = 1;
const int TaskSelect = 2;
const int TaskPut    = 3;
const int TaskJudge  = 4;
const int TaskEd     = 5;
const int TaskClose  = 6;

int task = TaskInit;

VirtualPlate plate;
HandSeeker* seeker;

int turn = 0;
unsigned int select_x = -1;

byte buff;

void setup()
{
  Serial.begin(9600);
  delay(2000);
  evshield.init( SH_HardwareI2C );
  evshield.bank_a.motorReset();
  evshield.bank_b.motorReset();

  shield_sensor[0].init(&evshield, SH_BBS1);
  shield_sensor[1].init(&evshield, SH_BBS2);
}

void loop()
{
  if (task != TaskClose) task = run(task);
  else exit(1);
}

int run(int task)
{
  switch (task) {
    case TaskInit:
      return task_init();
    case TaskOp:
      return task_op();
    case TaskSelect:
      return task_select();
    case TaskPut:
      return task_put();
    case TaskJudge:
      return task_judge();
    case TaskEd:
      return task_ed();
    default:
      return TaskClose;
  }
}

int task_init()
{
  return TaskOp;
}

int task_op()
{
  turn++;
  return TaskSelect;
}

int task_select()
{
  if (turn % 2) {
    byte new_data, prev_data = 0x00;
    new_data = get_sensor();
    if (new_data == prev_data) { prev_data = new_data; return TaskSelect; }
    prev_data = new_data;
    select_x = new_data - 1;
  }
  else {
    seeker = new HandSeeker(2);
    select_x = (*seeker)(plate);
    delete seeker;
  }
  delay(1000);
  return (plate.is_valid_hand(select_x)) ? TaskPut : TaskSelect;
}

int task_put()
{
  plate.insert(select_x);
  evshield.bank_a.motorRunDegrees(
    SH_Motor_1,
    (!(turn % 2) ? SH_Direction_Forward : SH_Direction_Reverse),
    30,
    100,
    SH_Completion_Wait_For,
    SH_Next_Action_Brake);
  delay(100);

  switch (select_x) {
    case 0:
      evshield.bank_a.motorRunRotations(
        SH_Motor_2,
        SH_Direction_Forward,
        30,
        1,
        SH_Completion_Wait_For,
        SH_Next_Action_Brake);
      delay(100);

      break;
    case 1:
      evshield.bank_a.motorRunRotations(
        SH_Motor_2,
        SH_Direction_Reverse,
        30,
        1,
        SH_Completion_Wait_For,
        SH_Next_Action_Brake);
      delay(100);

      break;
    case 2:
      evshield.bank_b.motorRunRotations(
        SH_Motor_1,
        SH_Direction_Forward,
        30,
        1,
        SH_Completion_Wait_For,
        SH_Next_Action_Brake);
      delay(100);

      break;
    case 3:
      evshield.bank_b.motorRunRotations(
        SH_Motor_1,
        SH_Direction_Reverse,
        30,
        1,
        SH_Completion_Wait_For,
        SH_Next_Action_Brake);
      delay(100);

      break;
    case 4:
      evshield.bank_b.motorRunRotations(
        SH_Motor_2,
        SH_Direction_Forward,
        30,
        1,
        SH_Completion_Wait_For,
        SH_Next_Action_Brake);
      delay(100);

      break;
    case 5:
      evshield.bank_b.motorRunRotations(
        SH_Motor_2,
        SH_Direction_Reverse,
        30,
        1,
        SH_Completion_Wait_For,
        SH_Next_Action_Brake);
      delay(100);

      break;
  }
  return TaskJudge;
}

int task_judge()
{
  if (plate.is_game_finish()) return TaskEd;
  else if (!plate.can_continue()) return TaskEd;
  plate.switch_active_stone();
  return (get_sensor() == 0) ? TaskOp : TaskJudge;
}

int task_ed()
{
  return TaskClose;
}

int get_sensor()
{
  if (Serial.available() > 0) {
    byte receive_data = Serial.read();
    for (int i = 0; i < 2; i++) receive_data |= (shield_sensor[i].isPressed() << i + 4);
    for (int i = 0; i < 8; i++)
      if (receive_data == get_two_pow(i)) return i + 1;
  }
  return 0;
}

int get_two_pow(int src)
{
  int dest = 1;
  for (int i = 0; i < src; i++) dest *= 2;
  return dest;
}


