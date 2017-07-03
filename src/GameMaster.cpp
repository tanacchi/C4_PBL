#include "../include/GameMaster.hpp"

GameMaster::GameMaster()
  : plate_(),
    body_(),
    seeler_ {0},
    turn_ {0}
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
}

Task GameMaster::task_op()
{
}

Task GameMaster::task_select()
{
}

Task GameMaster::task_insert()
{
}

Task GameMaster::task_put()
{
}

Task GameMaster::task_judge()
{
}

Task GameMaster::task_ed()
{
  return Task::Close;
}
