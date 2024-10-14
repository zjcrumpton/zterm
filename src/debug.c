#include "../include/camera.h"
#include "../include/chunk_map.h"
#include "../include/graphics.h"

void render_camera_debug() {
  // The center world coordinates are (0, 0)
  int world_x = 0;
  int world_y = 0;

  // Convert world coordinates to screen coordinates relative to the camera's
  // center
  int screen_x = (world_x - camera->x) * zoom_level + camera->width / 2;
  int screen_y = (world_y - camera->y) * zoom_level + camera->height / 2;

  // Check if the center tile is within the camera's view
  if (screen_x + TILE_SIZE * zoom_level >= 0 && screen_x < camera->width &&
      screen_y + TILE_SIZE * zoom_level >= 0 && screen_y < camera->height) {

    // Render the orange square at the center tile's screen position
    SDL_Rect center_tile_rect = {
        screen_x - TILE_SIZE / 2, screen_y - TILE_SIZE / 2,
        TILE_SIZE * zoom_level, TILE_SIZE * zoom_level};

    SDL_SetRenderDrawColor(renderer, 255, 165, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &center_tile_rect);
  }

  // Render a purple square where the camera is
  SDL_Rect camera_rect;
  camera_rect.x = camera->width / 2 - 10;  // Center on camera
  camera_rect.y = camera->height / 2 - 10; // Center on camera
  camera_rect.w = 20;                      // Width of the square
  camera_rect.h = 20;                      // Height of the square

  // Set the color to purple and render the square
  SDL_SetRenderDrawColor(renderer, 128, 0, 128, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &camera_rect);

  // Reset render color to default (black)
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void draw_chunk_boundaries(Vector2 coord) {
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
