#pragma once

enum pieceType {
	pawnType,
	rookType,
	knightType,
	bishopType,
	queenType,
	kingType,
	noType
};

enum pieceColour {
	whiteColour,
	blackColour,
	noColour
};

struct piece {
	pieceType type = noType;
	pieceColour colour = noColour;

	piece() : type(noType), colour(noColour) {}
	piece(pieceType newType, pieceColour newColour) : type(newType), colour(newColour) {}
};