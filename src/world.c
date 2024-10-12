#include "../include/world.h"
#include "../include/defs.h"
#include "../include/graphics.h"
#include <SDL2/SDL_rect.h>
#include <stdlib.h>

void populate_chunk(Chunk *chunk) {
  for (int x = 0; x < CHUNK_SIZE; x++) {
    for (int y = 0; y < CHUNK_SIZE; y++) {
      chunk->tiles[x][y].type = TILE_GRASS;
      chunk->tiles[x][y].collides = false;

      if (rand() % 10 == 0) {
        chunk->tiles[x][y].type = TILE_TREE;
        chunk->tiles[x][y].collides = true;
      }
    }
  }
}

void populate_initial_chunk(Chunk *chunk) {
  for (int x = 0; x < CHUNK_SIZE; x++) {
    for (int y = 0; y < CHUNK_SIZE; y++) {
      chunk->tiles[x][y].type = TILE_GRASS;
      chunk->tiles[x][y].collides = false;
      // don't spawn anything near the center of the starting chunk
      if (abs(x - CHUNK_SIZE / 2) < SPAWN_ZONE_RADIUS &&
          abs(y - CHUNK_SIZE / 2) < SPAWN_ZONE_RADIUS) {
        continue;
      }

      if (rand() % 10 == 0) {
        chunk->tiles[x][y].type = TILE_TREE;
        chunk->tiles[x][y].collides = true;
      }
    }
  }
}

SDL_Rect get_tile_rect(TileType tile_type) {
  SDL_Rect rect;
  rect.w = TILE_SIZE;
  rect.h = TILE_SIZE;

  switch (tile_type) {
  case TILE_GRASS:
    rect.x = 10;
    rect.y = 6;
    break;
  case TILE_TREE:
    rect.x = 1;
    rect.y = 6;
    break;
  }

  return rect;
}

enum TextureFile get_tile_texture_file(TileType tile_type) {
  switch (tile_type) {
  case TILE_GRASS:
    return TEXTURE_FLOOR;
  case TILE_TREE: // TODO: switch to proper tree Sprite
    return TEXTURE_FLOOR;
  default:
    return TEXTURE_FLOOR;
  }
}

void render_chunk(Chunk *chunk, int x_offset, int y_offset) {
  for (int x = 0; x < CHUNK_SIZE; x++) {
    for (int y = 0; y < CHUNK_SIZE; y++) {
      int screen_x = x * TILE_SIZE - x_offset;
      int screen_y = y + TILE_SIZE - y_offset;

      TileType tile_type = chunk->tiles[x][y].type;
      SDL_Rect rect = get_tile_rect(tile_type);
      enum TextureFile file = get_tile_texture_file(tile_type);

      render_tile(&rect, file, screen_x, screen_y);
    }
  }
}
