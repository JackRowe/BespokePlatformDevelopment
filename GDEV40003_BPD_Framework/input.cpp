#include "input.h"

namespace input {
	void move(board* p_game, sprite* p_sprites[SPRITES], int x, int y) {
		int current = p_game->getCurrent();

		if (interface::move(p_game, { x, y })) {
			p_sprites[current]->subColourShift(CURSOR_COLOUR_SHIFT);

			current = p_game->getCurrent();
			p_sprites[current]->addColourShift(CURSOR_COLOUR_SHIFT);
		}
	}

	void select(board* p_game, sprite* p_sprites[SPRITES]) {
		int selected = p_game->getSelected();
		int current = p_game->getCurrent();

		if (selected > 63) {
			// nothing selected

			// if the current square doesnt contain a piece ignore
			int64_t bitboard = p_game->getBitboard();
			bool isPiece = bit::getBit(bitboard, current);
			if (!isPiece) return;

			piece selectedPiece = interface::getPiece(p_game, current);

			if (selectedPiece.colour != p_game->getMoveColour()) return;

			p_game->setSelected(current);
			p_sprites[current]->addColourShift(SELECTED_COLOUR_SHIFT);

			for (int i = 0; i < 64; i++) {
				//if (!interface::isLegalMove(p_game, selectedPiece, current, i)) continue;
				//p_sprites[i]->addColourShift(50);
			}
		}
		else {
			// something selecred

			// move the piece from selected to current

			// first set the selected position on the piece bitboard to 0
			// then set the current position on the piece bitboard to 1
			// if there is a piece already on current then set it's respective bitboard to 0
			// after doing this, update the selected square sprite to have nullptr as texture
			// then update the current square sprite to have the releveant texture to the piece we just moved

			if (interface::movePiece(p_game, selected, current)) {
				p_sprites[current]->setTexture(p_sprites[selected]->getTexture());
				p_sprites[selected]->setTexture(nullptr);
			}

			piece selectedPiece = interface::getPiece(p_game, selected);

			for (int i = 0; i < 64; i++) {
				//if (!interface::isLegalMove(p_game, selectedPiece, selected, i)) continue;
				//p_sprites[i]->subColourShift(50);
			}

			p_sprites[selected]->subColourShift(SELECTED_COLOUR_SHIFT);
			p_game->setSelected(64);
		}
	}
}