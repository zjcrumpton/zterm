#include "../include/game_state.h"
#include "../include/graphics.h"
#include "../include/input.h"

int main() {
  if (init_graphics() < 0) {
    return -1;
  }

  while (game_state.running) {
    handle_input();
    render_frame();
  }

  cleanup_graphics();
  return 0;
}
