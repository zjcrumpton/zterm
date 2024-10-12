#ifndef CHUNK_MAP_H
#define CHUNK_MAP_H

#define CHUNK_HASH_SIZE 1024

#include "./world.h"

typedef struct ChunkCoordinate {
  int x, y;
} ChunkCoordinate;

typedef struct ChunkEntry {
  ChunkCoordinate coord;
  Chunk *chunk;
  struct ChunkEntry *next;
} ChunkEntry;

extern ChunkEntry *chunk_table[CHUNK_HASH_SIZE];

void init_chunk_map();
unsigned int hash_chunk(ChunkCoordinate coord);
void add_chunk(ChunkCoordinate coord, Chunk *chunk);
Chunk *get_chunk(ChunkCoordinate coord);
void free_chunks();
void world_to_chunk_and_tile(int world_x, int world_y, ChunkCoordinate *coord,
                             int *tile_x, int *tile_y);

#endif
