#pragma once

#include "board.h"
#include "math.h"
#include "piece.h"
#include "bitwise.h"

namespace interface {
	bool move(board* p_game, Vector2<int> p_direction);
	bool movePiece(board* p_game, int p_startPosition, int p_endPosition);
	bool isLegalMove(board* p_game, piece p_piece, int p_startPosition, int p_endPosition);
	bool inCheck(board* p_game, pieceColour p_colour);

	pieceColour getColour(board* p_game, int p_position);
	pieceType getType(board* p_game, int p_position);
	piece getPiece(board* p_game, int p_position);
}