#include "../include/chunk_map.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

ChunkEntry *chunk_table[CHUNK_HASH_SIZE];

uint32_t float_to_uint32(float value) {
  union {
    float f;
    uint32_t u;
  } converter;
  converter.f = value;
  return converter.u;
}

void init_chunk_map() {
  for (int i = 0; i < CHUNK_HASH_SIZE; i++) {
    chunk_table[i] = NULL;
  }
}

unsigned int hash_chunk(Vector2 coord) {
  uint32_t x_hash = float_to_uint32(coord.x);
  uint32_t y_hash = float_to_uint32(coord.y);

  return (x_hash ^ (y_hash * 0x9e3779b9)) % CHUNK_HASH_SIZE;
}

void add_chunk(WorldChunk *chunk) {
  unsigned int index = hash_chunk(chunk->pos);
  ChunkEntry *new_entry = (ChunkEntry *)malloc(sizeof(ChunkEntry));
  new_entry->coord = chunk->pos;
  new_entry->chunk = chunk;
  new_entry->next = NULL;

  if (index >= CHUNK_HASH_SIZE) {
    printf("Error: Index out of bounds: %u\n", index);
    return;
  }

  if (chunk_table[index] == NULL) {
    chunk_table[index] = new_entry;
  } else {
    // handle hashing collisions
    ChunkEntry *current = chunk_table[index];
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_entry;
  }
}

WorldChunk *get_chunk(Vector2 coord) {
  unsigned int index = hash_chunk(coord);

  ChunkEntry *current = chunk_table[index];
  while (current != NULL) {
    if (current->coord.x == coord.x && current->coord.y == coord.y) {
      return current->chunk;
    }

    current = current->next;
  }

  return NULL;
}

void free_chunks() {
  for (int i = 0; i < CHUNK_HASH_SIZE; i++) {
    ChunkEntry *current = chunk_table[i];
    while (current != NULL) {
      ChunkEntry *next = current->next;
      free(current->chunk);
      free(current);
      current = next;
    }
  }
}

void world_to_chunk_and_tile(int world_x, int world_y, Vector2 *coord,
                             int *tile_x, int *tile_y) {
  coord->x = floorf((float)world_x / (CHUNK_SIZE * TILE_SIZE));
  coord->y = floorf((float)world_y / (CHUNK_SIZE * TILE_SIZE));

  *tile_x = abs(world_x % (CHUNK_SIZE * TILE_SIZE)) / TILE_SIZE;
  *tile_y = abs(world_y % (CHUNK_SIZE * TILE_SIZE)) / TILE_SIZE;
}
