#ifndef WORLD_H
#define WORLD_H

#include "defs.h"
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
void render_chunk(Chunk *chunk, int x_offset, int y_offset);
void generate_initial_chunks();
void draw_visible_tiles();

#endif
