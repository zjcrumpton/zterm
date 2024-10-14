#include "../include/util.h"
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

  sprite.srcRect.x = slice_x;
  sprite.srcRect.y = slice_y;
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
