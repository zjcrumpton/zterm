#include "../include/input.h"
#include "../include/game_state.h"
#include "../include/graphics.h"
#include <SDL2/SDL_events.h>

Action map_input_to_action(SDL_Event *event) {
  switch (event->type) {
  case SDL_QUIT:
    return ACTION_QUIT;
  case SDL_KEYDOWN:
    switch (event->key.keysym.sym) {
    case SDLK_q:
      return ACTION_QUIT;
    case SDLK_F11:
      return ACTION_TOGGLE_FULLSCREEN;
    case SDLK_j:
      return ACTION_MOVE_CAMERA_DOWN;
    case SDLK_k:
      return ACTION_MOVE_CAMERA_UP;
    case SDLK_h:
      return ACTION_MOVE_CAMERA_LEFT;
    case SDLK_l:
      return ACTION_MOVE_CAMERA_RIGHT;
    }
  case SDL_MOUSEWHEEL:
    if (event->wheel.y > 0) {
      return ACTION_ZOOM_IN;
    } else if (event->wheel.y < 0) {
      return ACTION_ZOOM_OUT;
    }
    break;
  }

  return -1;
}

void handle_input() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    Action action = map_input_to_action(&event);
    if (action < 0) {
      continue;
    }

    switch (action) {
    case ACTION_QUIT:
      exit_game();
      break;
    case ACTION_TOGGLE_FULLSCREEN:
      toggle_fullscreen();
      break;
    case ACTION_ZOOM_IN:
      break;
    case ACTION_ZOOM_OUT:
      break;
    case ACTION_MOVE_CAMERA_RIGHT:
      break;
    case ACTION_MOVE_CAMERA_LEFT:
      break;
    case ACTION_MOVE_CAMERA_UP:
      break;
    case ACTION_MOVE_CAMERA_DOWN:
      break;
    }
  }
}
