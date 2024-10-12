#include "../include/game_state.h"

GameState game_state = {
    .running = true,
    .fullscreen = false,
};

void exit_game() { game_state.running = false; }
