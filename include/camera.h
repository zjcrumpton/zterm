typedef struct {
  int x, y;
  int width, height;
} Camera;

extern Camera *camera;
void init_camera();
void free_camera();
