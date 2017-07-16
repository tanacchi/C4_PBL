#include "include/GameMaster.hpp"

GameMaster master();
Task task = Task::Init;

void setup()
{ // 最初の設定とか
}

void loop()
{
  if (task != Task::Close) task = master.run(task); 
  else exit(0);
}