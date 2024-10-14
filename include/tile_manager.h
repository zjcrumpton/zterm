#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include "./util.h"

enum TileType {
  TILE_DIRT,
  TILE_GRASS,
};

typedef struct {
  Tile grass;
  Tile dirt;
} TileManager;

extern TileManager *tile_manager;
int init_tile_manager();
void destroy_tile_manager();

#endif
