#include "../include/proc_gen.h"
#include "../include/chunk.h"
#include "../include/chunk_map.h"

void generate_adjacent_chunks(Vector2 pos) {
  int x = pos.x;
  int y = pos.y;

  Vector2 adj_positions[4] = {
      new_vector(x - 1, y),
      new_vector(x + 1, y),
      new_vector(x, y - 1),
      new_vector(x, y + 1),
  };

  for (int i = 0; i < 4; i++) {
    Vector2 new_pos = adj_positions[i];
    if (get_chunk(new_pos) == NULL) {
      WorldChunk *new_chunk = generate_chunk(FOREST, new_pos.x, new_pos.y);
      add_chunk(new_chunk);
    }
  }
}
