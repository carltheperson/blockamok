#include <SDL.h>

#include "./game.h"

#define WIDTH 800
#define HEIGHT 800

void draw(SDL_Renderer *renderer);

void drawCubes(SDL_Renderer *renderer, Cube cubes[], int cubesLength);

void drawCube(SDL_Renderer *renderer, Cube cube);

void drawSpeedText(SDL_Renderer *renderer);

void drawGameOverText(SDL_Renderer *renderer);