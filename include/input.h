#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

typedef enum {
  ACTION_QUIT,
  ACTION_TOGGLE_FULLSCREEN,
} Action;

void handle_input();
Action map_input_to_action(SDL_Event *event);

#endif
