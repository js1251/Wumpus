// Copyright 2019 Jakob Sailer
// Author: Jakob Sailer <sailer.jakob@web.de>

// #include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "./cave.h"

int main(void) {
  struct cave c;
  c.seed = 12345;
  init_cave(&c);

  // print the matrix
  // print "(0) (1) ... (CAVESIZE)"
/*
*  printf("      ");
*  for (int i = 0; i < CAVESIZE; i++) {
*    if (i < 10) {
*      printf("(0%d) ", i);
*    } else {
*      printf("(%d) ", i);
*    }
*  }
*  printf("\n");
*  int sum = 0;
*  // print the rest of the matrix
*  for (int i = 0; i < CAVESIZE; i++) {
*    // print the row number
*    if (i < 10) {
*      printf("(0%d", i);
*    } else {
*      printf("(%d", i);
*    }
*    // print bats
*    if (c.bats[i]) {
*      printf("B) ");
*    } else {
*      printf(" ) ");
*    }
*    // print the collums for this row
*    for (int j = 0; j < CAVESIZE; j++) {
*      printf("[%d]  ", c.matrix[i][j]);
*      if (c.matrix[i][j]) {
*        sum++;
*      }
*    }
*    printf("(%d)\n", sum);
*    sum = 0;
*  }
*/

  // each room should never be connected to itself
  for (int i = 0; i < CAVESIZE; i++) {
    assert(c.matrix[i][i] == 0);
  }
  // there should be CAVESIZE rooms
  // this is true if there is never a row full of 0
  // also check for max connections of 4
  int checksum;
  for (int i = 0; i < CAVESIZE; i++) {
    checksum = 0;
    for (int j = 0; j < CAVESIZE; j++) {
      if (c.matrix[i][j] == 1) {
        checksum++;
      }
    }
    assert(2 <= checksum && checksum <= 4);
  }
  /*
  * // check if all rooms can be reached
  *
  * cavetestrecurs(matrix, 0, 0);
  *
  * // an attempt was made but not successfully
  */

  // check if CAVESIZE / 5 bats are present
  checksum = 0;
  for (int i = 0; i < CAVESIZE; i++) {
    if (c.bats[i]) {
      checksum++;
    }
  }
  assert(checksum == CAVESIZE / 5);
  return 0;
}
