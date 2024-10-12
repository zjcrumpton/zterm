#include "../include/world.h"
#include "../include/camera.h"
#include "../include/chunk_map.h"
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
    rect.x = 10 * TILE_SIZE;
    rect.y = 6 * TILE_SIZE;
    break;
  case TILE_TREE:
    rect.x = 1 * TILE_SIZE;
    rect.y = 6 * TILE_SIZE;
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
      int screen_y = y * TILE_SIZE - y_offset;

      TileType tile_type = chunk->tiles[x][y].type;
      SDL_Rect rect = get_tile_rect(tile_type);
      enum TextureFile file = get_tile_texture_file(tile_type);

      render_tile(&rect, file, screen_x, screen_y);
    }
  }
}

void generate_initial_chunks() {
  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      ChunkCoordinate coord = {dx, dy};
      Chunk *chunk = malloc(sizeof(Chunk));

      // handle the spawn chunk
      if (dx == 0 && dy == 0) {
        populate_initial_chunk(chunk);
      } else {
        populate_chunk(chunk);
      }

      add_chunk(coord, chunk);
    }
  }
}

void render_chunk_with_camera(Chunk *chunk) {
  for (int x = 0; x < CHUNK_SIZE; x++) {
    for (int y = 0; y < CHUNK_SIZE; y++) {
      int screen_x = x * TILE_SIZE - camera->x;
      int screen_y = y * TILE_SIZE - camera->y;

      if (screen_x >= 0 && screen_x < camera->width && screen_y >= 0 &&
          screen_y < camera->height) {
        TileType tile_type = chunk->tiles[x][y].type;
        SDL_Rect rect = get_tile_rect(tile_type);
        enum TextureFile file = get_tile_texture_file(tile_type);

        render_tile(&rect, file, screen_x, screen_y);
      }
    }
  }
}

void draw_visible_tiles() {
  int chunk_x_start = floor(camera->x / (CHUNK_SIZE * TILE_SIZE));
  int chunk_y_start = floor(camera->y / (CHUNK_SIZE * TILE_SIZE));
  int chunk_x_end =
      ceil((camera->x + camera->width) / (CHUNK_SIZE * TILE_SIZE));
  int chunk_y_end =
      ceil((camera->y + camera->height) / (CHUNK_SIZE * TILE_SIZE));

  for (int chunk_x = chunk_x_start; chunk_x <= chunk_x_end; chunk_x++) {
    for (int chunk_y = chunk_y_start; chunk_y <= chunk_y_end; chunk_y++) {
      ChunkCoordinate coord = {chunk_x, chunk_y};
      Chunk *chunk = get_chunk(coord);
      if (chunk != NULL) {
        for (int tile_x = 0; tile_x < CHUNK_SIZE; tile_x++) {
          for (int tile_y = 0; tile_y < CHUNK_SIZE; tile_y++) {
            // Calculate the world position of the tile
            int world_x = chunk_x * CHUNK_SIZE * TILE_SIZE + tile_x * TILE_SIZE;
            int world_y = chunk_y * CHUNK_SIZE * TILE_SIZE + tile_y * TILE_SIZE;

            // Convert to screen coordinates
            int screen_x = world_x - camera->x;
            int screen_y = world_y - camera->y;

            // Render the tile if it's within the camera's view
            if (screen_x >= 0 && screen_x < camera->width && screen_y >= 0 &&
                screen_y < camera->height) {
              TileType tile_type = chunk->tiles[tile_x][tile_y].type;
              SDL_Rect rect = get_tile_rect(tile_type);
              enum TextureFile file = get_tile_texture_file(tile_type);
              render_tile(&rect, file, screen_x, screen_y);
            }
          }
        }
      }
    }
  }
}
