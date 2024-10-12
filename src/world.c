#include "../include/world.h"
#include "../include/camera.h"
#include "../include/chunk_map.h"
#include "../include/debug.h"
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
  // Half dimensions for centering the camera
  int half_width = camera->width / 2;
  int half_height = camera->height / 2;

  // Calculate the global world bounds for the visible area
  int world_x_min = camera->x - half_width;
  int world_x_max = camera->x + half_width;
  int world_y_min = camera->y - half_height;
  int world_y_max = camera->y + half_height;

  // Loop over the chunks and tiles within the bounds
  for (int world_x = world_x_min; world_x < world_x_max; world_x += TILE_SIZE) {
    for (int world_y = world_y_min; world_y < world_y_max;
         world_y += TILE_SIZE) {
      // Convert world coordinates to chunk and tile indices
      ChunkCoordinate chunk_coord;
      int tile_x, tile_y;
      world_to_chunk_and_tile(world_x, world_y, &chunk_coord, &tile_x, &tile_y);

      Chunk *chunk = get_chunk(chunk_coord);
      if (chunk != NULL) {
        // Calculate the screen position
        int screen_x = (world_x - world_x_min) * zoom_level;
        int screen_y = (world_y - world_y_min) * zoom_level;

        // Get the tile type and render it
        TileType tile_type = chunk->tiles[tile_x][tile_y].type;
        SDL_Rect rect = get_tile_rect(tile_type);
        enum TextureFile file = get_tile_texture_file(tile_type);
        render_tile(&rect, file, screen_x, screen_y);
      }
    }
  }
}
