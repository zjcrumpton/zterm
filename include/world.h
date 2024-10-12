#ifndef WORLD_H
#define WORLD_H

#include "../include/defs.h"
#include <stdbool.h>

typedef enum {
  TILE_GRASS,
  TILE_TREE,
} TileType;

typedef struct {
  TileType type;
  bool collides;
} Tile;

typedef struct {
  Tile tiles[CHUNK_SIZE][CHUNK_SIZE];
} Chunk;

void populate_chunk(Chunk *chunk);
void populate_initial_chunk(Chunk *chunk);

#endif
