#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>

typedef struct {
  bool running;
  bool fullscreen;
} GameState;

void exit_game();

extern GameState game_state;

#endif
