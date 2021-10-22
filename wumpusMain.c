// Copyright 2019 Jakob Sailer
// Author: Jakob Sailer <sailer.jakob@web.de>
// with snippets from:
// http://www.network-science.de/ascii/
// https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c
// https://stackoverflow.com/questions/4324386/how-to-cast-program-argument-char-as-int-correctly

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "./cave.h"
#include "./wumpus.h"

int main(int argc, char *argv[]) {
  printf(" __      __  __  __           __");
  printf("__    __  __  ____\n");
  printf("/\\ \\  __/\\ \\/\\ \\/\\ \\  /'");
  printf("\\_/`\\/\\  _`\\ /\\ \\/\\ \\/\\  _`\\\n");
  printf("\\ \\ \\/\\ \\ \\ \\ \\ \\ \\ \\");
  printf("/\\      \\ \\ \\L\\ \\ \\ \\ \\ \\ \\,\\L\\_\\\n");
  printf(" \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\");
  printf(" \\ \\__\\ \\ \\ ,__/\\ \\ \\ \\ \\/_\\__ \\\n");
  printf("  \\ \\ \\_/ \\_\\ \\ \\ \\_\\ \\");
  printf(" \\ \\_/\\ \\ \\ \\/  \\ \\ \\_\\ \\/\\ \\L\\ \\\n");
  printf("   \\ `\\___^___/\\ \\_____\\ \\");
  printf("_\\\\ \\_\\ \\_\\   \\ \\_____\\ `\\____\\\n");
  printf("    '\\/__//__/  \\/_____/\\/_/ ");
  printf("\\/_/\\/_/    \\/_____/\\/_____/\n");
  printf("                   created by Jakob Sailer\n\n");

  printf("\n\n                  Press ENTER to continue\n\n");
  getchar();

  // init cave & wumpus
  struct cave c;
  unsigned int seed = 0;
  struct wumpus w;
  bool dropped = 0;

  if (argc > 1) {
    sscanf(argv[1], "%u", &seed);
  }
  c.seed = seed;
  init_cave(&c);

  for (int i = 0; i < CAVESIZE; i++) {
    for (int j = 0; j < CAVESIZE; j++) {
      w.matrix[i][j] = c.matrix[i][j];
    }
    w.bats[i] = c.bats[i];
  }
  w.ply = rand() % CAVESIZE;
  while (c.bats[w.ply]) {
    w.ply = rand() % CAVESIZE;
  }
  w.wum = rand() % CAVESIZE;
  while (w.ply == w.wum || c.bats[w.wum]) {
    w.wum = rand() % CAVESIZE;
  }
  wumpus(&w);

  // while the player is alive
  while (true) {
    printf("\n---------------------------------\n");
    printf("You find yourself in room %d.\n", w.ply);

    // if the player is dead
    if (w.events[7] == 1) {
      if (dropped) {
        printf("the bat dropped you right into the wumpus' open mouth and");
      } else {
        printf("You ran right into the wumpus and");
      }
      printf(" it devoured you in a single bite!\n\n");
      break;
    }
    dropped = 0;

    // if theres a bat in your room
    if (w.events[5] == 1) {
      printf("A bat as big as a man grabs you,");
      printf(" flies off and suddendly drops you.\n");
      int temp = rand() %CAVESIZE;
      // the bat shouldnt drop you in the current room
      while (temp == w.ply) {
        temp = rand() %CAVESIZE;
      }
      w.ply = temp;
      wumpus(&w);
      dropped = 1;
    }

    // if theres a bat closeby
    if (w.events[4] == 1 && !dropped) {
      printf("You hear a strange rustling noise...\n");
    }

    // if the wumpus is closeby
    if (w.events[6] == 1 && !dropped) {
      printf("You can smell the wumpus! It must be closeby...\n");
    }

    // which rooms are connected
    if (!dropped) {
      printf("\nYou can see that the following rooms are connected: ");
      for (int i = 0; i <= 3; i++) {
        if (w.events[i] != -1) {
          printf("%d ", w.events[i]);
        }
      }

      // ask player where to go
      printf("\nWhere do You choose to go?\n");
      int input;
      char term;
      // check if input was valid
      bool valid = 0;
      while (!valid) {
        scanf("%d%c", &input, &term);
        if (term == '\n') {
          for (int i = 0; i <= 3; i++) {
            if (input == w.events[i]) {
              valid = 1;
              break;
            }
          }
          if (!valid) {
            printf("You cant go there. Try again!\n");
          }
        }
      }
      w.ply = input;
      // finally run wumpus to get new events
      wumpus(&w);
    }
  }
  return 0;
}
