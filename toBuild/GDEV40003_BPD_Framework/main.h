#pragma once

#include <chrono>
#include <thread>

#include "SDL.h"
#include "SDL_image.h"
#include "constants.h"
#include "sprite.h"
#include "texture.h"
#include "board.h"
#include "fen.h"
#include "math.h"
#include "interface.h"
#include "input.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

sprite* sprites[SQUARES] = {};
texture* textures[TEXTURES] = {};

board* game = nullptr;

int main(int argc, char* argv[]);
bool initalise();
bool load();
bool start();
bool loop();
bool update();
void draw();
void close();