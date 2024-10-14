#include "../include/camera.h"
#include "../include/chunk.h"
#include "../include/chunk_map.h"
#include "../include/game_state.h"
#include "../include/graphics.h"
#include "../include/input.h"
#include "../include/proc_gen.h"
#include "../include/tile_manager.h"
#include "../include/util.h"

int setup();
void cleanup();

int main() {
  if (setup() < 0) {
    return -1;
  }

  while (game_state.running) {
    handle_input();
    clear();
  }

  cleanup();
  return 0;
}

int setup() {
  if (init_graphics() < 0) {
    return -1;
  }

  if (load_textures() < 0) {
    return -1;
  }

  if (init_tile_manager()) {
    return -1;
  }

  init_chunk_map();

  WorldChunk *chunk = generate_chunk(SPAWN, 0, 0);
  add_chunk(chunk);

  generate_adjacent_chunks(chunk->pos);

  return 0;
}

void cleanup() {
  cleanup_graphics();
  destroy_tile_manager();
}
