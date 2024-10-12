#include "../include/graphics.h"
#include "../include/defs.h"
#include "../include/game_state.h"
#include <SDL2/SDL_image.h>
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

void render_frame() {
  SDL_FillRect(screenSurface, NULL,
               SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window);
}

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
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
    return -1;
  }
  textures.forest = forest_texture;

  return 0;
}
