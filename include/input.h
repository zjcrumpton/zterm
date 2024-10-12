#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

typedef enum {
  ACTION_QUIT,
  ACTION_TOGGLE_FULLSCREEN,
  ACTION_ZOOM_OUT,
  ACTION_ZOOM_IN,
  ACTION_MOVE_CAMERA_LEFT,
  ACTION_MOVE_CAMERA_RIGHT,
  ACTION_MOVE_CAMERA_DOWN,
  ACTION_MOVE_CAMERA_UP,
} Action;

void handle_input();
Action map_input_to_action(SDL_Event *event);

#endif
