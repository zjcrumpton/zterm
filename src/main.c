#include "../include/game_state.h"
#include "../include/graphics.h"
#include "../include/input.h"
#include "../include/world.h"

int main() {
  if (init_graphics() < 0) {
    return -1;
  }

  if (load_textures() < 0) {
    return -1;
  }

  Chunk chunk = {};
  populate_initial_chunk(&chunk);
  render_chunk(&chunk, 0, 0);

  while (game_state.running) {
    handle_input();
    clear();
    render_chunk(&chunk, 0, 0);
    render_frame();
  }

  cleanup_graphics();
  return 0;
}
