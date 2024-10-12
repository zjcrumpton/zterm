typedef struct {
  int x, y;
  int width, height;
} Camera;

extern Camera *camera;
extern float zoom_level;

void init_camera();
void free_camera();
void zoom_in();
void zoom_out();
void move_camera_left(int speed);
void move_camera_right(int speed);
void move_camera_up(int speed);
void move_camera_down(int speed);
