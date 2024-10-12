#include "../include/graphics.h"
#include "../include/defs.h"
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;

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
