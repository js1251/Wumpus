// Copyright 2019 Jakob Sailer
// Author: Jakob Sailer <sailer.jakob@web.de>

#include <stdbool.h>

#include "./cave.h"

#ifndef WUMPUS_H_
#define WUMPUS_H_

struct wumpus {
  bool matrix[CAVESIZE][CAVESIZE];
  bool bats[CAVESIZE];
  int ply;
  int wum;
  int events[8];
  /*
  * really only a length of 8 is needed but 
  * I made it 9 to stop the stack smashing error
  *
  * events[0-3] => connections of current room
  * events[4] => is a bat closeby
  * events[5] => is a bat in current room
  * events[6] => is a wumpus closeby
  * events[7] => is the player dead
  */
};

// does all the checks for game events
void wumpus(struct wumpus *w);

#endif  // WUMPUS_H_
