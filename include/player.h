#ifndef PLAYER_H
#define PLAYER_H

#include "util.h"

typedef struct {
  Vector2 pos;
} Player;

Player *new_player();
void destroy_player(Player *player);

#endif
