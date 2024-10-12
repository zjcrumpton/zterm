#include "../include/camera.h"
#include "../include/defs.h"

Camera *camera;

void init_camera() {
  camera = (Camera *)malloc(sizeof(Camera));
  if (camera != NULL) {
    camera->x = 0;
    camera->y = 0;
    camera->width = SCREEN_WIDTH;
    camera->height = SCREEN_HEIGHT;
  }
}

void free_camera() { free(camera); }
