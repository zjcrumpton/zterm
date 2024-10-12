#include "../include/input.h"
#include "../include/game_state.h"
#include "../include/graphics.h"

Action map_input_to_action(SDL_Event *event) {
  switch (event->type) {
  case SDL_KEYDOWN:
    switch (event->key.keysym.sym) {
    case SDLK_q:
      return ACTION_QUIT;
    case SDLK_F11:
      return ACTION_TOGGLE_FULLSCREEN;
    }
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
    }
  }
}
