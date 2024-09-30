#include "main.h"

int main(int argc, char* argv[]) {
	// setup SDL
	if (!initalise()) return 0;

	// load images
	if (!load()) return 0;

	// start game
	if (!start()) return 0;
	bool quit = true;

	while (quit) {
		quit = loop();
		std::this_thread::sleep_for(std::chrono::microseconds(18100));
	}

	close();
	return 0;
}

bool initalise() {
	// initalize sdl, if unsuccessful return
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
	if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_GAMECONTROLLER) < 0) {
		std::cout << "SDL failed to initalise: " << SDL_GetError();
		return false;
	}

	// create the window with WIDTH and HEIGHT
	window = SDL_CreateWindow("Bespoke Platform Development",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	// if the window is nullptr, then it failed to be created
	if (window == nullptr) {
		std::cout << "Window was not created: " << SDL_GetError();
		return false;
	}

	// create a renderer for the window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// if the renderer is nullptr, it failed to be created
	if (renderer == nullptr) {
		std::cout << "Renderer was not created: " << SDL_GetError();
		return false;
	}

	// initalise image loading
	int imageFlags = IMG_INIT_PNG;
	if (!IMG_Init(imageFlags) && imageFlags) {
		std::cout << "SDL_Image failed to initalise: " << IMG_GetError();
		return false;
	}

	SDL_JoystickOpen(1);

	return true;
}

bool load() {
	textures[0] = new texture(renderer, "Images/WhitePawn.png");
	textures[1] = new texture(renderer, "Images/WhiteRook.png");
	textures[2] = new texture(renderer, "Images/WhiteKnight.png");
	textures[3] = new texture(renderer, "Images/WhiteBishop.png");
	textures[4] = new texture(renderer, "Images/WhiteQueen.png");
	textures[5] = new texture(renderer, "Images/WhiteKing.png");

	textures[6] = new texture(renderer, "Images/BlackPawn.png");
	textures[7] = new texture(renderer, "Images/BlackRook.png");
	textures[8] = new texture(renderer, "Images/BlackKnight.png");
	textures[9] = new texture(renderer, "Images/BlackBishop.png");
	textures[10] = new texture(renderer, "Images/BlackQueen.png");
	textures[11] = new texture(renderer, "Images/BlackKing.png");

	return true;
}

bool start() {
	game = new board();
	fen::write(game, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

	uint64_t bitboard = game->getBitboard();
	uint64_t pieceBitboards[UNIQUE_PIECES] = {
		game->getPieceBitboard(whiteColour, pawnType),
		game->getPieceBitboard(whiteColour, rookType),
		game->getPieceBitboard(whiteColour, knightType),
		game->getPieceBitboard(whiteColour, bishopType),
		game->getPieceBitboard(whiteColour, queenType),
		game->getPieceBitboard(whiteColour, kingType),

		game->getPieceBitboard(blackColour, pawnType),
		game->getPieceBitboard(blackColour, rookType),
		game->getPieceBitboard(blackColour, knightType),
		game->getPieceBitboard(blackColour, bishopType),
		game->getPieceBitboard(blackColour, queenType),
		game->getPieceBitboard(blackColour, kingType),
	};

	for (int i = 0; i < SQUARES; i++) {
		int x = i / 8;
		int y = i % 8;

		texture* pieceTexture = nullptr;

		if (bit::getBit(bitboard, i)) {
			for (int j = 0; j < UNIQUE_PIECES; j++) {
				if (bit::getBit(pieceBitboards[j], i)) {
					pieceTexture = textures[j];
					break;
				}
			}
		}

		sprites[i] = new sprite(
			pieceTexture,
			{ (y) * (WINDOW_WIDTH / 8), (x) * (WINDOW_HEIGHT / 8) },
			{ WINDOW_WIDTH / 8, WINDOW_HEIGHT / 8 },
			((x + y) % 2 != 0 ? LIGHT_COLOUR : DARK_COLOUR)
		);

		if (i == 0) {
			sprites[0]->setColourShift(CURSOR_COLOUR_SHIFT);
		}
	}

	return true;
}	

bool loop() {
	draw();
	return update();
}

bool update() {
	SDL_Event e;
	SDL_PollEvent(&e);

	int current = game->getCurrent();
	int x = current / 8;
	int y = current % 8;
	Vector4<int> Colour = (x + y) % 2 != 0 ? LIGHT_COLOUR : DARK_COLOUR;

	// holy shit this entire thing needs to be cleaned up 
	// write an interface class / namespace to deal with all this in another file
	switch (e.type)
	{
		case SDL_QUIT: {
			return false;
			break;
		}
		case SDL_KEYDOWN: {
			switch (e.key.keysym.sym) {
				case SDLK_UP: {
					input::move(game, sprites, 0, -1);
					break;
				}
				case SDLK_DOWN: {
					input::move(game, sprites, 0, 1);
					break;
				}
				case SDLK_RIGHT: {
					input::move(game, sprites, 1, 0);
					break;
				}
				case SDLK_LEFT: {
					input::move(game, sprites, -1, 0);
					break;
				}
				case SDLK_SPACE: {
					input::select(game, sprites);
					break;
				}
			}

			break;
		}

		case SDL_JOYBUTTONDOWN: {
			switch(e.jbutton.button) {
				case EVERCADE_UP: {
					input::move(game, sprites, 0, -1);
					break;
				}
				case EVERCADE_RIGHT: {
					input::move(game, sprites, 1, 0);
					break;
				}
				case EVERCADE_DOWN: {
					input::move(game, sprites, 0, 1);
					break;
				}
				case EVERCADE_LEFT: {
					input::move(game, sprites, -1, 0);
					break;
				}
				case EVERCADE_SELECT: {
					input::select(game, sprites);
					break;
				}
				break;
			}
		}
	}

	return true;
}

void draw() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	for (int i = 0; i < SQUARES; i++) {
		if (sprites[i] == nullptr) continue;
		sprites[i]->draw(renderer);
	}

	SDL_RenderPresent(renderer);
}

void close() {
	for (int i = 0; i < SQUARES; i++) {
		if (sprites[i] == nullptr) continue;
		delete sprites[i];
	}

	for (int i = 0; i < TEXTURES; i++) {
		if (textures[i] == nullptr) continue;
		delete textures[i];
	}

	if (!window) return;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_Quit();
}