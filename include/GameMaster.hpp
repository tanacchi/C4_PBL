#ifndef GAME_MASTER_H_
#define GAME_MASTER_H_

#include "VirtualPlate.hpp"
#include "BodyController.hpp"
#include "HandSeeker.hpp"

enum class Task {
  Init, Op, Select, Put, Judge, Ed, Close
};

class GameMaster {
public:
  GameMaster();
  ~GameMaster() = default;
  Task run(Task task);
  Task task_init();
  Task task_op();
  Task task_select();
  Task task_put();
  Task task_judge();
  Task task_ed();
private:
  GameMaster(const GameMaster& src);
  const GameMaster& operator=(const GameMaster& src);
  VirtualPlate plate_;
  BodyController body_;
  HandSeeler* seeker_;
  int turn_;
  int select_x_;
};

#endif // GAME_MASTER_H_
