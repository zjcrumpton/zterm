#include "../include/chunk.h"
#include "../include/chunk_map.h"
#include "../include/defs.h"
#include "../include/graphics.h"
#include "../include/tile_manager.h"
#include "../include/util.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void generate_spawn_tile(int x, int y, WorldChunk *chunk);
void generate_forest_tile(int x, int y, WorldChunk *chunk);

WorldChunk *generate_chunk(enum ChunkType type, int x, int y) {
  WorldChunk *chunk = (WorldChunk *)malloc(sizeof(WorldChunk));
  if (chunk == NULL) {
    fprintf(stderr, "failed to allocate space for new WorldChunk");
  }

  TileMap tilemap = new_tilemap(CHUNK_SIZE, CHUNK_SIZE);
  chunk->tilemap = tilemap;
  chunk->pos.x = x;
  chunk->pos.y = y;

  for (int x = 0; x < CHUNK_SIZE; x++) {
    for (int y = 0; y < CHUNK_SIZE; y++) {
      switch (type) {
      case SPAWN:
        generate_spawn_tile(x, y, chunk);
        break;

      case FOREST:
        generate_forest_tile(x, y, chunk);
        break;
      }
    }
  }

  return chunk;
}
void generate_spawn_tile(int x, int y, WorldChunk *chunk) {
  chunk->tilemap[x][y] = tile_manager->grass;
}

void generate_forest_tile(int x, int y, WorldChunk *chunk) {
  bool is_dirt = rand() % 10 == 0;
  chunk->tilemap[x][y] = is_dirt ? tile_manager->grass : tile_manager->dirt;
}

void destroy_chunk(WorldChunk *chunk) {
  destroy_tilemap(chunk->tilemap, CHUNK_SIZE);
  free(chunk);
}

#define ZOOM_LEVEL 2

void render_visible_chunks(Vector2 player_pos) {
  // Tile *tile = get_tile_from_world_pos(new_vector(0, 0));

  int zoom_tile_size = TILE_SIZE * ZOOM_LEVEL;
  float horizontal_tiles = (float)SCREEN_WIDTH / zoom_tile_size;
  float vertical_tiles = (float)SCREEN_HEIGHT / zoom_tile_size;

  Vector2 start = new_vector(player_pos.x - (horizontal_tiles / 2),
                             player_pos.y - (vertical_tiles / 2));

  for (int y = 0; y < vertical_tiles; y++) {
    for (int x = 0; x < horizontal_tiles; x++) {
      int world_x = start.x + x;
      int world_y = start.y + y;

      int screen_x = x * zoom_tile_size;
      int screen_y = y * zoom_tile_size;
      Tile *tile = get_tile_from_world_pos(new_vector(world_x, world_y));
      render_tile(tile, screen_x, screen_y, ZOOM_LEVEL);
    }
  }
}
