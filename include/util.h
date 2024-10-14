#ifndef UTIL_H
#define UTIL_H

#include "./defs.h"
#include "stdbool.h"
#include <SDL2/SDL.h>

typedef struct {
  float x;
  float y;
} Vector2;

Vector2 new_vector(float x, float y);

typedef SDL_Rect Rect;
typedef SDL_Texture Texture;
typedef SDL_RendererFlip Flip;

typedef struct {
  Rect srcRect;
  Texture *texture;
  float rotation;
  Flip flip;
} Sprite;

Sprite new_sprite(int slice_x, int slice_y, int width, int height,
                  Texture *texture);

typedef struct {
  int type;
  Sprite sprite;
  bool walkable;
} Tile;

void render_tile(Tile *tile, int screen_x, int screen_y, int zoom_level);

typedef Tile **TileMap;

TileMap new_tilemap(int width, int height);
void destroy_tilemap(TileMap tilemap, int height);

typedef struct {
  Vector2 pos;
  int vp_width;
  int vp_height;
} Camera;

#endif
