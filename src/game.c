#include "./game.h"

#include <SDL.h>

Player player;

void gameFrame(SDL_Event e, float deltaTime) {
  if (e.type != SDL_KEYDOWN) {
    return;
  }
  if (e.key.keysym.sym == SDLK_w) {
    player.z += 1 * deltaTime;
  }
  if (e.key.keysym.sym == SDLK_s) {
    player.z += 1 * deltaTime;
  }
}