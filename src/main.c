#include "../include/graphics.h"

int main() {
  if (init_graphics() < 0) {
    return -1;
  }

  int running = 1;
  while (running) {
    render_frame();
  }

  cleanup_graphics();
  return 0;
}
