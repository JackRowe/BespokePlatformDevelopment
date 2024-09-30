 #pragma once

#include <vector>
#include <iostream>
#include <bitset>

#include "constants.h"
#include "piece.h"
#include "bitwise.h"

class board
{
private:
	uint64_t c_pieceBitboards[12] = { 0ULL };
	uint64_t c_pieceMovementMasks[6][64] = { {0ULL} };

	pieceColour c_move = whiteColour;
	unsigned int c_currentSquare = 0;
	unsigned int c_selectedSquare = SQUARES;
public:
	board();
	~board() {};

	void setBitboard(pieceColour p_colour, pieceType p_type, uint64_t p_bitboard) { c_pieceBitboards[(p_colour == whiteColour ? p_type : p_type + 6)] = p_bitboard; };

	pieceColour getMoveColour() { return c_move; };
	uint64_t getMovementMask(pieceType p_type, int p_position) { return c_pieceMovementMasks[p_type][p_position]; };
	uint64_t getPieceBitboard(pieceColour p_colour, pieceType p_type) { return c_pieceBitboards[(p_colour == whiteColour ? p_type : p_type + 6)]; };
	uint64_t getColourBitboard(pieceColour p_colour);
	uint64_t getBitboard();

	unsigned int getCurrent() { return c_currentSquare; };
	unsigned int getSelected() { return c_selectedSquare; };

	void setMoveColour(pieceColour p_newColour) { c_move = p_newColour; };
	void setCurrent(unsigned int p_newCurrent) { c_currentSquare = p_newCurrent; };
	void setSelected(unsigned int p_newSelected) { c_selectedSquare = p_newSelected; };
};

