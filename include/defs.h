#ifndef DEFS_H
#define DEFS_H

#include <SDL2/SDL.h>

// Game Metadata
extern const char *TITLE;

// Screen Dimensions
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

// World Generation
#define CHUNK_SIZE 32
#define SPAWN_ZONE_RADIUS CHUNK_SIZE / 4
extern const int TILE_SIZE;
extern const int TILES_ACROSS;
extern const int TILES_DOWN;

#define TILEMAP_WIDTH 32
#define TILEMAP_HEIGHT 32

#endif
