#pragma once

#include <cstdint>

namespace bit {
	bool getBit(uint64_t p_bitboard, int p_bit);
	uint64_t setBit(uint64_t p_bitboard, int p_bit, bool p_value);
}