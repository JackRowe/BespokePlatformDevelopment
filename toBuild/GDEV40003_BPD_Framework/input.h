#pragma once

#include "interface.h"
#include "sprite.h"
#include "constants.h"

namespace input {
	void move(board* p_game, sprite* sprites[SPRITES], int x, int y);
	void select(board* p_game, sprite* p_sprites[SPRITES]);
}