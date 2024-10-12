#include "../include/camera.h"
#include "../include/defs.h"

Camera *camera;
float zoom_level;

void init_camera() {
  zoom_level = 1.0f;
  camera = (Camera *)malloc(sizeof(Camera));
  if (camera != NULL) {
    camera->x = 0;
    camera->y = 0;
    camera->width = SCREEN_WIDTH;
    camera->height = SCREEN_HEIGHT;
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
