#include "../include/camera.h"
#include "../include/defs.h"
#include <SDL2/SDL_video.h>

Camera *camera;
float zoom_level;

void init_camera() {
  zoom_level = 1.0f;
  camera = (Camera *)malloc(sizeof(Camera));
  if (camera != NULL) {
    // Set the camera size to the window size
    camera->width = SCREEN_WIDTH;
    camera->height = SCREEN_HEIGHT;

    // Calculate the world coordinates of the top-left corner of the center
    // chunk (0, 0)
    int top_left_chunk_world_x = 0;
    int top_left_chunk_world_y = 0;

    // Now center the camera's position over the center of this chunk
    camera->x = top_left_chunk_world_x + (CHUNK_SIZE * TILE_SIZE / 2) -
                (camera->width / 2);
    camera->y = top_left_chunk_world_y + (CHUNK_SIZE * TILE_SIZE / 2) -
                (camera->height / 2);
  }
}

void free_camera() { free(camera); }

void zoom_in() {
  int center_x = camera->x + camera->width / 2;
  int center_y = camera->y + camera->height / 2;

  zoom_level *= 1.1f;
  camera->width = SCREEN_WIDTH / zoom_level;
  camera->height = SCREEN_HEIGHT / zoom_level;

  camera->x = center_x - camera->width / 2;
  camera->y = center_y - camera->height / 2;
}

void zoom_out() {
  int center_x = camera->x + camera->width / 2;
  int center_y = camera->y + camera->height / 2;

  zoom_level /= 1.1f;
  camera->width = SCREEN_WIDTH / zoom_level;
  camera->height = SCREEN_HEIGHT / zoom_level;

  camera->x = center_x - camera->width / 2;
  camera->y = center_y - camera->height / 2;
}

void move_camera_left(int speed) { camera->x -= speed; }

void move_camera_right(int speed) { camera->x += speed; }

void move_camera_up(int speed) { camera->y -= speed; }

void move_camera_down(int speed) { camera->y += speed; }
