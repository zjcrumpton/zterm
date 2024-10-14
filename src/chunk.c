#include "../include/chunk.h"
#include "../include/defs.h"
#include "../include/tile_manager.h"
#include "../include/util.h"
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
