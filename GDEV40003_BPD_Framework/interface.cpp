#include "interface.h"

namespace interface {

	bool move(board* p_game, Vector2<int> p_direction) {
		int current = p_game->getCurrent();
		int x = current / 8;
		int y = current % 8;

		int newCurrent = clamp(current + p_direction.x + (p_direction.y * 8), 0, 63);
		if (current + p_direction.x + (p_direction.y * 8) != newCurrent) return false;
		if (p_direction.y == 0 && abs(y - (newCurrent) % 8) > 1) return false;

		p_game->setCurrent(newCurrent);
		return true;
	}

	bool isLegalMove(board* p_game, piece p_piece, int p_startPosition, int p_endPosition) {
		uint64_t movementMask = p_game->getMovementMask(p_piece.type, p_startPosition);
		piece targetPiece = getPiece(p_game, p_endPosition);
		int64_t bitboard = p_game->getBitboard();

		int x = p_startPosition / 8;
		int y = p_startPosition % 8;

		int newX = p_endPosition / 8;
		int newY = p_endPosition % 8;

		if (targetPiece.colour == p_piece.colour) return false;

		if (p_piece.type == knightType) return bit::getBit(movementMask, p_endPosition);

		if (p_piece.type == pawnType) {
			bool firstMove = p_piece.colour == whiteColour ? p_startPosition / 8 == 6 : p_startPosition / 8 == 1;
			int difference = abs(p_startPosition - p_endPosition);

			if (abs(x - newX) > 2 || abs(y - newY) > 2) return false;

			// if endPosition has an enemy piece AND is diagonal forward then it is a valid move
			// by just checking if the end position has a target piece, it means that the pawn cannot take unless it is on the diagonal
			if (targetPiece.type != noType) return (difference == 7 || difference == 9);
			
			// if it's the first move, the pawn can move either one or two square forward
			// otherwise the only other valid move is moving one square forward
			if (firstMove) return difference == 8 || (difference == 16 && !bit::getBit(bitboard, p_startPosition + ((p_endPosition - p_startPosition) / 2)));
			return difference == 8;
		}

		if (!bit::getBit(movementMask, p_endPosition)) return false;

		// ffs im just gonna be lazy
		int directionX = std::max(-1, std::min(newX - x, 1));
		int directionY = std::max(-1, std::min(newY - y, 1));

		int currentX = x;
		int currentY = y;

		bool valid = true;

		for (int distance = 1; distance < 7; distance++) {
			currentX = x + (directionX * distance);
			currentY = y + (directionY * distance);

			int newIndex = currentY + (currentX * 8);

			if (newIndex > 63 || newIndex <= 0) return false;

			if (newIndex == p_endPosition) return true;

			if (bit::getBit(bitboard, newIndex)) return false;
		}

		// alternative is working on magic bitboards

		return false;
	}

	bool movePiece(board* p_game, int p_startPosition, int p_endPosition) {
		// first set the selected position on the piece bitboard to 0
		// then set the current position on the piece bitboard to 1
		// if there is a piece already on current then set it's respective bitboard to 0

		if (p_startPosition == p_endPosition) return false;

		piece selectedPiece = getPiece(p_game, p_startPosition);

		if (!isLegalMove(p_game, selectedPiece, p_startPosition, p_endPosition)) return false;

		piece targetPiece = getPiece(p_game, p_endPosition);
		int64_t selectedPieceBitboard = p_game->getPieceBitboard(selectedPiece.colour, selectedPiece.type);

		if (targetPiece.colour != noColour && targetPiece.type != noType) {
			int64_t targetPieceBitboard = p_game->getPieceBitboard(targetPiece.colour, targetPiece.type);
			targetPieceBitboard = bit::setBit(targetPieceBitboard, p_endPosition, false);
			p_game->setBitboard(targetPiece.colour, targetPiece.type, targetPieceBitboard);
		}

		selectedPieceBitboard = bit::setBit(selectedPieceBitboard, p_startPosition, false);
		selectedPieceBitboard = bit::setBit(selectedPieceBitboard, p_endPosition, true);

		p_game->setBitboard(selectedPiece.colour, selectedPiece.type, selectedPieceBitboard);

		// horrible, stupid, shitty way to do this butttt.........
		// it also means that a chess engine is nigh impossible
		// if in check, invert back to original state

		if (inCheck(p_game, selectedPiece.colour)) {
			selectedPieceBitboard = bit::setBit(selectedPieceBitboard, p_startPosition, true);
			selectedPieceBitboard = bit::setBit(selectedPieceBitboard, p_endPosition, false);

			if (targetPiece.colour != noColour && targetPiece.type != noType) {
				int64_t targetPieceBitboard = p_game->getPieceBitboard(targetPiece.colour, targetPiece.type);
				targetPieceBitboard = bit::setBit(targetPieceBitboard, p_endPosition, true);
				p_game->setBitboard(targetPiece.colour, targetPiece.type, targetPieceBitboard);
			}

			p_game->setBitboard(selectedPiece.colour, selectedPiece.type, selectedPieceBitboard);
			return false;
		}

		p_game->setMoveColour(p_game->getMoveColour() == whiteColour ? blackColour : whiteColour);
		return true;
	}

	bool inCheck(board* p_game, pieceColour p_colour) {
		pieceColour enemyColour = p_colour == whiteColour ? blackColour : whiteColour;
		uint64_t bitboard = p_game->getBitboard();
		uint64_t colourBitboard = p_game->getColourBitboard(enemyColour);
		uint64_t kingBitboard = p_game->getPieceBitboard(p_colour, kingType);
		int squareIndex = 64;

		for (int i = 0; i < 64; i++)
		{
			if (!bit::getBit(kingBitboard, i)) continue;
			squareIndex = i;
			break;
		}

		if (squareIndex == 64) return false;
		
		for (int i = 0; i < 64; i++) {
			if (!bit::getBit(bitboard, i)) continue;
			if (!bit::getBit(colourBitboard, i)) continue;

			pieceType type = getType(p_game, i);

			if (!isLegalMove(p_game, { type, enemyColour }, i, squareIndex)) continue;

			return true;
		}

		return false;
	}

	pieceColour getColour(board* p_game, int p_position) {
		int64_t bitboard = p_game->getBitboard();
		bool isAnyPiece = bit::getBit(bitboard, p_position);

		if (!isAnyPiece) return noColour;

		for (int i = 0; i < 2; i++) {
			pieceColour colour = static_cast<pieceColour>(i);
			int64_t colourBitboard = p_game->getColourBitboard(colour);
			bool isColourPiece = bit::getBit(colourBitboard, p_position);

			if (isColourPiece) return colour;
		}

		return noColour;
	}

	pieceType getType(board* p_game, int p_position) {
		int64_t bitboard = p_game->getBitboard();
		bool isAnyPiece = bit::getBit(bitboard, p_position);

		if (!isAnyPiece) return noType;

		for (int i = 0; i < 2; i++) {
			pieceColour colour = static_cast<pieceColour>(i);
			int64_t colourBitboard = p_game->getColourBitboard(colour);
			bool isColourPiece = bit::getBit(colourBitboard, p_position);

			if (!isColourPiece) continue;

			for (int j = 0; j < 6; j++) {
				pieceType type = static_cast<pieceType>(j);
				int64_t pieceBitboard = p_game->getPieceBitboard(colour, type);
				bool isPiece = bit::getBit(pieceBitboard, p_position);

				if (isPiece) return type;
			}
		}

		return noType;
	}

	piece getPiece(board* p_game, int p_position) {
		piece returnedPiece;
		int64_t bitboard = p_game->getBitboard();
		bool isAnyPiece = bit::getBit(bitboard, p_position);

		if (!isAnyPiece) return returnedPiece;

		for (int i = 0; i < 2; i++) {
			pieceColour colour = static_cast<pieceColour>(i);
			int64_t colourBitboard = p_game->getColourBitboard(colour);
			bool isColourPiece = bit::getBit(colourBitboard, p_position);

			if (!isColourPiece) continue;
			returnedPiece.colour = colour;

			for (int j = 0; j < 6; j++) {
				pieceType type = static_cast<pieceType>(j);
				int64_t pieceBitboard = p_game->getPieceBitboard(colour, type);
				bool isPiece = bit::getBit(pieceBitboard, p_position);

				if (!isPiece) continue;
				returnedPiece.type = type;
				return returnedPiece;
			}
		}

		return returnedPiece;
	}

}