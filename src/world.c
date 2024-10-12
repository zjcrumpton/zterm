#include "../include/world.h"
#include "../include/defs.h"
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
