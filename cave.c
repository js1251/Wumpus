// Copyright 2019 Jakob Sailer
// Author: Jakob Sailer <sailer.jakob@web.de>
// with snippets from:
// https://www.tutorialspoint.com/c_standard_library/c_function_srand.htm
// https://stackoverflow.com/questions/30807947/what-does-comparing-constant-with-boolean-expression-is-always-true-warning-me
// http://www.c-howto.de/tutorial/schleifen/continue/

// #include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./cave.h"

void init_cave(struct cave *c) {
  // make whole matrix false
  for (int i = 0; i < CAVESIZE; i++) {
    for (int j = 0; j < CAVESIZE; j++) {
      c->matrix[i][j] = 0;
    }
  }

  // using the choosen seed as rand init
  srand(c->seed);

  int rooms = 0;
  int start = rand() % CAVESIZE;
  int current = start;
  int connect;
  // until CAVESIZE rooms have been added
  // create a "line" through the cave
  // -1 as last room doesnt need a seperate conection
  while (rooms < CAVESIZE - 1) {
    connect = rand() % CAVESIZE;
    // calculate how many conections the next room already has
    int checksum = 0;
    for (int i = 0; i < CAVESIZE; i++) {
      checksum += c->matrix[connect][i];
    }
    // room cannot be itself, an already connected
    // room or a already have an connection
    if (current == connect ||
    c->matrix[connect][current] == true ||
    checksum >= 1) {
      continue;
    }
    // lets only make it one way for now
    c->matrix[current][connect] = true;
    rooms++;
    if (rooms == CAVESIZE - 1) {
      // connect end to start of line as to not create dead ends
      c->matrix[connect][start] = true;
    }
    current = connect;
  }

  // Now that the line is done go through each room and add
  // additional connections between 1 and 3 (to get 2 to 4 total)
  for (int i = 0; i < CAVESIZE; i++) {
    // i is current room
    int a = rand() % 1;
    int b = rand() % 2;
    // 50% for 0 or 1
    // 33% for 0, 1, or 2
    int limit = a + b;
    // -> 0:11%, 1:22%, 2:33%, 3:33%
    if (limit == 0) {
      limit = 1;  // to even the chances and eliminate dead ends
    }
    for (int j = 0; j < limit; j++) {
      int connect = rand() % CAVESIZE;
      int checksum = 3;
      while (connect == i ||
      c->matrix[i][connect] == true ||
      checksum >= 3) {
        checksum = 0;
        connect = rand() % CAVESIZE;
        for (int k = 0; k < CAVESIZE; k++) {
          checksum += c->matrix[connect][k];
        }
      }
      // to guarantee at least one symetrical connection for each room
      c->matrix[i][connect] = true;
      c->matrix[connect][i] = true;
    }
  }
/*
  // init
  int current = rand() % CAVESIZE;
  int connect;
  int checksum = 0;
  int rooms = 0;

  // until CAVESIZE rooms have been added
  while (rooms < CAVESIZE) {
    checksum = 0;
    connect = rand() % CAVESIZE;
    // calculate how many conections the room already has
    for (int i = 0; i < CAVESIZE; i++) {
      checksum += c->matrix[connect][i];
    }

    // choose a random room to connect to,
    // thats not itself, an already connected room
    // or already has four(three + current) connections

    if (connect == current ||
    c->matrix[connect][current] == true ||
    checksum >= 3) {
      continue;
    }
    // connect the found room to the current and the other way around
    c->matrix[current][connect] = true;
    c->matrix[connect][current] = true;
    // we might have only created a junction with an already existing room
    if (checksum < 2) {
      // nope its actually a new room
      rooms++;
    }
    // set the next room to be the found room
    // so we dont end up with 'floating' rooms
    current = connect;
  }

  // once all connections have been build check
  // if all rooms have at least 2 connections
  for (int i = 0; i < CAVESIZE; i++) {
    checksum = 0;
    for (int j = 0; j < CAVESIZE; j++) {
      current = c->matrix[i][j];
      if (current) {
        // count connecting rooms
        checksum++;
      }
    }
    // if its below 2
    if (checksum == 1) {
      printf("DEBUG: only one connection in room %d\n", i);
      // add another random connection with the same requirements as above
      checksum = 3;  // to start the while loop
      while (connect == i ||
      c->matrix[i][connect] == true ||
      checksum > 3) {
        checksum = 0;
        connect = rand() % CAVESIZE;
        for (int j = 0; j < CAVESIZE; j++) {
          checksum += c->matrix[connect][j];
        }
        printf("DEBUG: try %d\n", connect);
        printf("DEBUG: checksum %d\n", checksum);
        printf("DEBUG: i %d\n", i);
      }
      printf("DEBUG: added connection %d<->%d\n", i, connect);
      c->matrix[i][connect] = true;
      c->matrix[connect][i] = true;
    }
  }
*/

  // add bats to some rooms (ratio 1 in 5)
  for (int i = 0; i < CAVESIZE; i++) {
    c->bats[i] = 0;
  }
  for (int i = 0; i < CAVESIZE / 5; i++) {
    // choose a random room
    int batroom = rand() % CAVESIZE;
    // if it doesnt already have a bat
    if (c->bats[batroom] != true) {
      // add one
      c->bats[batroom] = true;
    } else {
      // we have to try again so dont iterate i
      i--;
    }
  }
}
