#pragma once

#include <string>
#include <map>

#include "board.h"
#include "constants.h"
#include "bitwise.h"

namespace fen {
	std::string read(board* p_board);
	void write(board* p_board, std::string input);
}