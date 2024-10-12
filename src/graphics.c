#include "../include/graphics.h"
#include "../include/defs.h"
#include "../include/game_state.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <unistd.h>

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Renderer *renderer = NULL;

Textures textures = {};

int init_graphics() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  window =
      SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
    return -1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Renderer could not be created! SDL_ERROR: %s\n", SDL_GetError());
    return -1;
  }

  if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN < 0)) {
    printf("SDL could not go fullscreen! SDL_Error: %s\n", SDL_GetError());
  }

  screenSurface = SDL_GetWindowSurface(window);
  return 0;
}

void clear() { SDL_RenderClear(renderer); }
void render_frame() { SDL_RenderPresent(renderer); }

void cleanup_graphics() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void toggle_fullscreen() {
  game_state.fullscreen = !game_state.fullscreen;
  int flags = game_state.fullscreen ? 0 : SDL_WINDOW_FULLSCREEN;
  SDL_SetWindowFullscreen(window, flags);
}

int load_textures() {
  SDL_Texture *forest_texture = NULL;

  forest_texture = IMG_LoadTexture(renderer, "./assets/forest_pack/FLOORS.png");
  if (forest_texture == NULL) {
    printf("SDL could not load forest texture! SDL_Error: %s\n",
           SDL_GetError());
    return -1;
  }
  textures.forest = forest_texture;

  SDL_Texture *decorations_texture = NULL;
  decorations_texture =
      IMG_LoadTexture(renderer, "./assets/forest_pack/Decorations.png");
  if (decorations_texture == NULL) {
    printf("SDL could not load forest texture! SDL_Error: %s\n",
           SDL_GetError());

    return -1;
  }

  return 0;
}

void render_tile(SDL_Rect *rect, enum TextureFile file, int x, int y) {
  SDL_Texture *texture;
  switch (file) {
  case TEXTURE_FLOOR:
    texture = textures.forest;
    break;
  case TEXTURE_DECORATIONS:
    texture = textures.decorations;
    break;
  }

  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = TILE_SIZE;
  dest.h = TILE_SIZE;

  SDL_RenderCopy(renderer, texture, rect, &dest);
}
