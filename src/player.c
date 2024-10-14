#include "../include/player.h"
#include <stdio.h>

Player *new_player() {
  Player *player = (Player *)malloc(sizeof(Player));
  if (player == NULL) {
    printf("error allocating memory for player");
    return NULL;
  }

  player->pos = new_vector(0, 0);

  return player;
}

void destroy_player(Player *player) { free(player); }
