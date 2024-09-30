	#include "fen.h"

std::map<char, pieceType> charToType = {
	{'p', pawnType},
	{'r', rookType},
	{'n', knightType},
	{'b', bishopType},
	{'q', queenType},
	{'k', kingType},
};

namespace fen {

	std::string read(board* p_board) {
		return "";
	}

	void write(board* p_board, std::string input) {
		int square = 0;

		for (int i = 0; i < input.size(); i++) {
			char character = input[i];

			// ignore since we don't actually care about the verticality of the board
			if (character == '/') continue;

			// if it's a number, skip forward that many squares
			if (isdigit(character))
			{
				square += static_cast<int>(character) - ASCII_ZERO;
				continue;
			}

			pieceColour colour = islower(character) ? blackColour : whiteColour;
			pieceType type = charToType[tolower(character)];

			// get the releveant bitboard, set the releveant bit on it and then set the bitboard to the updated version
			uint64_t bitboard = p_board->getPieceBitboard(colour, type);
			bitboard = bit::setBit(bitboard, square, true);
			p_board->setBitboard(colour, type, bitboard);

			square++;
		}
	}

}