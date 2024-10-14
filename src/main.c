#include "../include/chunk.h"
#include "../include/chunk_map.h"
#include "../include/game_state.h"
#include "../include/graphics.h"
#include "../include/input.h"
#include "../include/player.h"
#include "../include/proc_gen.h"
#include "../include/tile_manager.h"

int setup();
void cleanup();

Player *player = NULL;

int main() {
  if (setup() < 0) {
    return -1;
  }

  while (game_state.running) {
    handle_input();
    clear();
    render_visible_chunks(player->pos);
    render_frame();
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

  WorldChunk *chunk = generate_chunk(FOREST, 0, 0);
  add_chunk(chunk);

  generate_adjacent_chunks(chunk->pos);
  generate_adjacent_chunks(new_vector(0, -1));
  generate_adjacent_chunks(new_vector(0, 1));
  generate_adjacent_chunks(new_vector(1, 0));
  generate_adjacent_chunks(new_vector(-1, 0));

  player = new_player();
  if (player == NULL) {
    return -1;
  }

  // set player position to starting tile position
  player->pos.x = 15;
  player->pos.y = 15;

  return 0;
}

void cleanup() {
  cleanup_graphics();
  destroy_tile_manager();
  destroy_player(player);
}
