// Copyright 2019 Jakob Sailer
// Author: Jakob Sailer <sailer.jakob@web.de>

#include <stdbool.h>

#ifndef CAVE_H_
#define CAVE_H_

#define CAVESIZE 20
struct cave {
  bool matrix[CAVESIZE][CAVESIZE];
  bool bats[CAVESIZE];
  unsigned int seed;
};

// initiates the cavesystem and places bats in it
void init_cave(struct cave *c);

#endif  // CAVE_H_
