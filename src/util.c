#include "../include/util.h"
#include "../include/graphics.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>

Vector2 new_vector(float x, float y) {
  Vector2 vec;
  vec.x = x;
  vec.y = y;
  return vec;
}

Sprite new_sprite(int slice_x, int slice_y, int width, int height,
                  Texture *texture) {
  Sprite sprite;

  sprite.srcRect.x = slice_x * width;
  sprite.srcRect.y = slice_y * height;
  sprite.srcRect.w = width;
  sprite.srcRect.h = height;
  sprite.texture = texture;
  sprite.rotation = 0.0f;
  sprite.flip = SDL_FLIP_NONE;

  return sprite;
}

TileMap new_tilemap(int width, int height) {
  TileMap tilemap = (TileMap)malloc(height * sizeof(Tile *));
  if (tilemap == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  for (int i = 0; i < height; i++) {
    tilemap[i] = (Tile *)malloc(width * sizeof(Tile));
  }

  return tilemap;
}

void destroy_tilemap(TileMap tilemap, int height) {
  for (int i = 0; i < height; i++) {
    free(tilemap[i]);
  }

  free(tilemap);
}

void render_tile(Tile *tile, int screen_x, int screen_y, int zoom_level) {
  Texture *texture = tile->sprite.texture;
  Rect *srcRect = &tile->sprite.srcRect;

  Rect dest;
  dest.x = screen_x;
  dest.y = screen_y;
  dest.w = srcRect->w * zoom_level;
  dest.h = srcRect->h * zoom_level;

  SDL_RenderCopy(renderer, texture, srcRect, &dest);

  SDL_RenderDrawRect(renderer, &dest);
}
