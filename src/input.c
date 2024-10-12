#include "../include/input.h"
#include "../include/camera.h"
#include "../include/chunk_map.h"
#include "../include/game_state.h"
#include "../include/graphics.h"
#include <SDL2/SDL_events.h>
#include <stdio.h>

Action map_input_to_action(SDL_Event *event) {
  switch (event->type) {
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
      zoom_in();
      break;
    case ACTION_ZOOM_OUT:
      zoom_out();
      break;
    case ACTION_MOVE_CAMERA_RIGHT:
      move_camera_right(32);
      break;
    case ACTION_MOVE_CAMERA_LEFT:
      move_camera_left(32);
      break;
    case ACTION_MOVE_CAMERA_UP:
      move_camera_up(32);
      break;
    case ACTION_MOVE_CAMERA_DOWN:
      move_camera_down(32);
      break;
    }
    printf("camera position (%i, %i)\n", camera->x, camera->y);
    ChunkCoordinate coord;
    int tile_x, tile_y;
    world_to_chunk_and_tile(camera->x, camera->y, &coord, &tile_x, &tile_y);

    printf("mapped chunk and tile position Chunk: (%i, %i) Tile: (%i, %i)\n",
           coord.x, coord.y, tile_x, tile_y);
  }
}
