#include "../include/GameMaster.hpp"

GameMaster::GameMaster()
  : plate_(),
    body_(),
    seeler_ {0},
    turn_ {1}
{
}

Task GameMaster::run(Task task)
{
  switch (task) {
  case Task::Init:   return task_init();
  case Task::Op:     return task_op();
  case Task::Select: return task_select();
  case Task::Put:    return task_put();
  case Task::Judge:  return task_judge();
  case Task::Ed:     return task_ed();
  default:           return Task::Close;
  }
}

Task GameMaster::task_init()
{
  return Task::Op;
}

Task GameMaster::task_op()
{
  return Task::Select;
}

Task GameMaster::task_select()
{
  if (!(turn % 2)) {
    int pushed_sensor = 0;
    while (!(pushed_sensor = body_.get_sensor())) ;
    select_x_ = pushed_sensor - 1;
  }
  else {
    seeker = new HandSeeker();
    select_x_ = (*seeker)(plate_);
    delete seeker;
  }
  return (plate_.is_valid_hand(select_x_)) ? Task::Put : Task::Select;
}

Task GameMaster::task_put()
{
  plate_.insert(select_x_);
  //  body_.drop_stone(select_x_);
  switch (select_x_) {
    // use motor series
  case 0: break;
  case 1: break;
  case 2: break;
  case 3: break;
  case 4: break;
  case 5: break;
  }
  return Task::Judge;
}

Task GameMaster::task_judge()
{
  if (plate_.is_game_finish()) return Ed; // 引き分けかどうかで分岐させたい
  else if (plate_.can_continue())   return Ed;
  plate_.switch_active_stone();
  turn++;
  return Task::Select;
}

Task GameMaster::task_ed()
{
  return Task::Close;
}
