// Copyright 2019 Jakob Sailer
// Author: Jakob Sailer <sailer.jakob@web.de>

#include <stdlib.h>

#include "./cave.h"
#include "./wumpus.h"

void wumpus(struct wumpus *w) {
  // reset events
  for (int i = 0; i < sizeof(w->events) / sizeof(w->events[0]); i++) {
    w->events[i] = -1;
  }

  // check if a bat is in your room
  if (w->bats[w->ply]) {
    w->events[5] = 1;
  }
  // check if the wumpus is in your room
  if (w->wum == w->ply) {
    w->events[7] = 1;
  }
  // all closeby events
  // check all connecting rooms
  int room = 0;
  for (int i = 0; i < CAVESIZE; i++) {
    if (w->matrix[w->ply][i]) {
      w->events[room] = i;
      room++;
    }
  }
  // check for closeby events
  for (int i = 0; i < room; i++) {
    // check if the wumpus is in a connecting room (depth 1)
    if (w->wum == w->events[i]) {
      w->events[6] = 1;
      // if a wumpus is in depth 1 we dont need to check for depth 2
      break;
    }
    // if not check for depth 2
    for (int j = 0; j < CAVESIZE; j++) {
      if (w->matrix[w->events[i]][j]) {
        if (j == w->wum) {
          w->events[6] = 1;
          break;  // if found break
        }
      }
    }
  }
  for (int i = 0; i < room; i++) {
    // check if a bat is closeby
    if (w->bats[w->events[i]]) {
      w->events[4] = 1;
      break;
    }
  }
}
