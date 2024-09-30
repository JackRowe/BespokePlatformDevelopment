#include "board.h"

void createSliderMovementMask(uint64_t& movementMask, int square, int direction, bool diagonal) {
	int rookDirections[4] = { 1, -1, 8, -8 };
	int bishopDirections[4] = { 9, 7, -9, -7 };
	
	int lastSquare = square;
	int newSquare = square;

	int x = square / 8;
	int y = square % 8;

	while (true) {
		newSquare += diagonal ? bishopDirections[direction] : rookDirections[direction];

		int newX = newSquare / 8;
		int newY = newSquare % 8;

		int lastX = lastSquare / 8;
		int lastY = lastSquare % 8;

		if (newSquare < 0 || newSquare >= 64 || abs(newY - lastY) > 1 || abs(newX - lastX) > 1) {
			break;
		}

		//if (diagonal && abs(newX - x) != abs(newY - y))  break;
		//else if (!diagonal && (newX != x && direction < 2) || (newY != y && direction >= 2)) break;

		movementMask = bit::setBit(movementMask, newSquare, true);
		lastSquare = newSquare;
	}
}

void createKnightMovementMask(uint64_t& movementMask, int square) {
	// 2 left 1 down : -2 + 8 = 6
	// 2 left 1 up : -2 + -8 = -10
	// 2 right 1 down : 2 + 8 = 10
	// 2 right 1 up : 2 + -8 = -8
	// 1 right 2 up : 1 + -16 = -15
	// 1 left 2 up : -1 + -16 = -17
	// 1 right 2 down : 1 + 16 = 17
	// 1 left 2 down : -1 + 16 = -15

	int knightDirections[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };

	int x = square / 8;
	int y = square % 8;

	for (int direction : knightDirections) {
		int newSquare = square + direction;

		// make sure it doesnt wrap around the board lol
		int newX = (newSquare + 8 * 8) % (8 * 8) / 8;
		int newY = (newSquare + 8 * 8) % (8 * 8) % 8;

		if (std::abs(newX - x) <= 2 && std::abs(newY - y) <= 2 && (std::abs(newX - x) != 2 || std::abs(newY - y) != 2)) {
			movementMask = bit::setBit(movementMask, newSquare, true);
		}
	}
}

void createKingMovementMask(uint64_t& movementMask, int square) {
	int kingDirections[8] = { 1, 9, 8, 7, -1, -9, -8, -7 };

	int x = square / 8;
	int y = square % 8;

	for (int direction : kingDirections) {
		int newSquare = square + direction;

		// make sure it doesnt wrap around the board lol
		int newX = (newSquare + 8 * 8) % (8 * 8) / 8;
		int newY = (newSquare + 8 * 8) % (8 * 8) % 8;

		if (std::abs(newX - x) <= 2 && std::abs(newY - y) <= 2 && (std::abs(newX - x) != 2 || std::abs(newY - y) != 2)) {
			movementMask = bit::setBit(movementMask, newSquare, true);
		}
	}
}

board::board() {
	// a loop to go thru each square on the board
	// to then create movement masks for each piece on that square
	for (int square = 0; square < 64; square++) {
		// loop thru the 4 unique directions
		for (int direction = 0; direction < 4; direction++) {

			// rook: continue following the direction until reaching the edge of the board
			createSliderMovementMask(c_pieceMovementMasks[rookType][square], square, direction, false);

			// bishop: continue following the direction until reaching the edge of the board
			createSliderMovementMask(c_pieceMovementMasks[bishopType][square], square, direction, true);
		}

		// queen: LITERALLY JUST THE ROOK AND BISHOP MASKS COMBINED
		c_pieceMovementMasks[queenType][square] = c_pieceMovementMasks[rookType][square] | c_pieceMovementMasks[bishopType][square];

		// knight: create movement mask by adding every variation of 2 one direction 1 in the other
		createKnightMovementMask(c_pieceMovementMasks[knightType][square], square);

		// king: movement mask which is literally just 1 tile in each direction
		createKingMovementMask(c_pieceMovementMasks[kingType][square], square);

		/*for (int i = 63; i >= 0; i--) {
			if (square == i) std::cout << "X" << " ";
			else std::cout << ((c_pieceMovementMasks[queenType][square] & (1ULL << i)) ? '1' : '0') << " ";
			if (i % 8 == 0) std::cout << std::endl;
		}*/
		//std::cout << std::endl;
	}
}

uint64_t board::getColourBitboard(pieceColour p_colour) {
	int toAdd = (p_colour == whiteColour ? 0 : 6);
	return c_pieceBitboards[0 + toAdd] | c_pieceBitboards[1 + toAdd] | c_pieceBitboards[2 + toAdd] | c_pieceBitboards[3 + toAdd] | c_pieceBitboards[4 + toAdd] | c_pieceBitboards[5 + toAdd];
}

uint64_t board::getBitboard() {
	return getColourBitboard(whiteColour) | getColourBitboard(blackColour);
}
