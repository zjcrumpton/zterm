#ifndef CHUNK_MAP_H
#define CHUNK_MAP_H

#include "chunk.h"
#include "util.h"
#define CHUNK_HASH_SIZE 1024

typedef struct ChunkEntry {
  Vector2 coord;
  WorldChunk *chunk;
  struct ChunkEntry *next;
} ChunkEntry;

extern ChunkEntry *chunk_table[CHUNK_HASH_SIZE];

void init_chunk_map();
unsigned int hash_chunk(Vector2 coord);
void add_chunk(WorldChunk *chunk);
WorldChunk *get_chunk(Vector2 coord);
void free_chunks();
void world_to_chunk_and_tile(int world_x, int world_y, Vector2 *coord,
                             int *tile_x, int *tile_y);
Tile *get_tile_from_world_pos(Vector2 pos);

#endif
