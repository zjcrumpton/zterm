#include "../include/camera.h"
#include "../include/chunk_map.h"
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

  init_chunk_map();
  generate_initial_chunks();
  init_camera();

  int tile_x, tile_y;
  ChunkCoordinate coord;
  world_to_chunk_and_tile(0, 0, &coord, &tile_x, &tile_y);
  printf("coords: %n,%n\n", &tile_x, &tile_y);

  while (game_state.running) {
    handle_input();
    clear();
    draw_visible_tiles();
    render_frame();
  }

  cleanup_graphics();
  free_camera();
  free_chunks();
  return 0;
}
