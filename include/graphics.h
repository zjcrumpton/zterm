#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

typedef struct {
  SDL_Texture *forest;
  SDL_Texture *decorations;
} Textures;

enum TextureFile {
  TEXTURE_FLOOR,
  TEXTURE_DECORATIONS,
};

int init_graphics();
int load_textures();
void render_frame();
void cleanup_graphics();
void toggle_fullscreen();

#endif
