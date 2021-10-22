// Copyright 2019 Jakob Sailer
// Author: Jakob Sailer <sailer.jakob@web.de>

#include <assert.h>
#include <stdio.h>

#include "./wumpus.h"
#include "./cave.h"

int main(void) {
  struct cave c;
  struct wumpus w;

  c.seed = 123;
  init_cave(&c);

  for (int i = 0; i < CAVESIZE; i++) {
    for (int j = 0; j < CAVESIZE; j++) {
      w.matrix[i][j] = c.matrix[i][j];
    }
    w.bats[i] = c.bats[i];
  }
  // assert first move of game with seed 123
  w.ply = 15;
  w.wum = 12;
  wumpus(&w);
  assert(w.events[0] == 2);
  assert(w.events[1] == 10);
  assert(w.events[2] == 11);
  assert(w.events[3] == -1);
  assert(w.events[4] == 1);
  assert(w.events[5] == -1);
  assert(w.events[6] == -1);
  assert(w.events[7] == -1);

  // now lets assert some random stuff
  w.bats[w.events[0]] = 1;  // bat near player
  w.bats[w.ply] = 1;  // bat in player room
  w.wum = w.events[0];  // wumpus near player (depth 1)
  wumpus(&w);
  assert(w.events[5] = 1);
  assert(w.events[6] = 1);
  assert(w.events[4] = 1);
  return 0;
}

