#include "bitwise.h"

namespace bit {

	// maybe make overloads to set by ref

	bool getBit(uint64_t p_bitboard, int p_bit) {
		// and the board and a mask (which left shifts by 'bit' positions) and check if it's not 0
		// to get the bool value at 'bit'  which is then returned
		return (p_bitboard & (1ULL << p_bit)) != 0;
	}

	uint64_t setBit(uint64_t p_bitboard, int p_bit, bool p_state) {
		// if state is true, or the board and a mask (shifted left by 'bit' positions)
		// if state is false, do the same thing, but the mask is inverted.
		return p_state ? p_bitboard | (1ULL << p_bit) : p_bitboard & ~(1ULL << p_bit);
	}

}