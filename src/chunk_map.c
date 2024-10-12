#include "../include/chunk_map.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

ChunkEntry *chunk_table[CHUNK_HASH_SIZE];

void init_chunk_map() {
  for (int i = 0; i < CHUNK_HASH_SIZE; i++) {
    chunk_table[i] = NULL;
  }
}

unsigned int hash_chunk(ChunkCoordinate coord) {
  long long hash = ((long long)coord.x * 31 + coord.y) % CHUNK_HASH_SIZE;
  return (unsigned int)(hash < 0 ? -hash : hash);
}

void add_chunk(ChunkCoordinate coord, Chunk *chunk) {
  unsigned int index = hash_chunk(coord);

  ChunkEntry *new_entry = (ChunkEntry *)malloc(sizeof(ChunkEntry));
  new_entry->coord = coord;
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

Chunk *get_chunk(ChunkCoordinate coord) {
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

void world_to_chunk_and_tile(int world_x, int world_y, ChunkCoordinate *coord,
                             int *tile_x, int *tile_y) {
  coord->x = floorf((float)world_x / (CHUNK_SIZE * TILE_SIZE));
  coord->y = floorf((float)world_y / (CHUNK_SIZE * TILE_SIZE));

  *tile_x = abs(world_x % (CHUNK_SIZE * TILE_SIZE)) / TILE_SIZE;
  *tile_y = abs(world_y % (CHUNK_SIZE * TILE_SIZE)) / TILE_SIZE;
}
