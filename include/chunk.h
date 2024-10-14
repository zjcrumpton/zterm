#ifndef CHUNK_H
#define CHUNK_H

#include "./util.h"

typedef struct {
  Vector2 pos;
  TileMap tilemap;
} WorldChunk;

enum ChunkType {
  SPAWN,
  FOREST,
};

WorldChunk *generate_chunk(enum ChunkType type, int x, int y);
void render_visible_chunks(Vector2 player_pos);

#endif
