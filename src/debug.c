#include "../include/camera.h"
#include "../include/chunk_map.h"
#include "../include/graphics.h"

void render_camera_debug() {
  SDL_Rect camera_rect;

  // Set the size and position for the debug square
  camera_rect.x = (camera->width / 2) - 10;  // Center on camera
  camera_rect.y = (camera->height / 2) - 10; // Center on camera
  camera_rect.w = 20;                        // Width of the square
  camera_rect.h = 20;                        // Height of the square

  // Set the color to purple (R, G, B, A)
  SDL_SetRenderDrawColor(renderer, 128, 0, 128, SDL_ALPHA_OPAQUE);

  // Render the purple square
  SDL_RenderFillRect(renderer, &camera_rect);

  // Reset render color to default (black)
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void draw_chunk_boundaries(ChunkCoordinate coord) {
  int chunk_world_x = coord.x * CHUNK_SIZE * TILE_SIZE;
  int chunk_world_y = coord.y * CHUNK_SIZE * TILE_SIZE;

  int screen_x = (chunk_world_x - camera->x) * zoom_level;
  int screen_y = (chunk_world_y - camera->y) * zoom_level;

  SDL_Rect chunk_rect = {screen_x, screen_y, CHUNK_SIZE * TILE_SIZE,
                         CHUNK_SIZE * TILE_SIZE};

  // Set color for boundary (e.g., red)
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

  // Draw the boundary rectangle
  SDL_RenderDrawRect(renderer, &chunk_rect);

  // Reset render color to default
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  render_camera_debug();
}
