#include "../include/tile_manager.h"
#include "../include/graphics.h"
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

TileManager *tile_manager = NULL;

int init_tile_manager() {
  tile_manager = (TileManager *)malloc(sizeof(TileManager));

  if (tile_manager == NULL) {
    fprintf(stderr, "failed to allocate tile manager");
    return -1;
  }

  Sprite dirt_sprite = new_sprite(1, 6, TILE_SIZE, TILE_SIZE, textures.forest);
  Tile dirt;
  dirt.type = TILE_DIRT;
  dirt.sprite = dirt_sprite;
  dirt.walkable =
      false; // TODO: make this true, and later make tree tiles non walkable

  Sprite grass_sprite =
      new_sprite(10, 6, TILE_SIZE, TILE_SIZE, textures.forest);
  Tile grass;
  grass.type = TILE_GRASS;
  grass.sprite = grass_sprite;
  grass.walkable = true;

  tile_manager->dirt = dirt;
  tile_manager->grass = grass;
  return 0;
};

void destroy_tile_manager() { free(tile_manager); }
