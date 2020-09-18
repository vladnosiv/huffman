#include <iostream>
#include <fstream>
#include <cassert>
#include <climits>

#include "bin_manip.hpp"

std::ostream& write_uchar::operator()(std::ostream& s) const {
	return s << (unsigned char)value;
}

std::ostream& operator<<(std::ostream& s, const write_uchar &wuc) {
	return wuc(s);
}

std::istream& read_uchar::operator()(std::istream& s) const {
	value = s.get();
	return s;
}

std::istream& operator>>(std::istream& s, const read_uchar &ruc) {
	return ruc(s);
}

std::ostream& write_le_int32::operator()(std::ostream& s) const {
	s << (unsigned char)(value) << (unsigned char)(value >> 8);
	return s << (unsigned char)(value >> 16) << (unsigned char)(value >> 24);
}

std::ostream& operator<<(std::ostream& s, const write_le_int32 &wi) {
	return wi(s);
}

std::istream& read_le_int32::operator()(std::istream& s) const {
	unsigned char current_byte;
	value = 0;
	for (int i = 0; i < 4; ++i) {
		current_byte = s.get();
		value |= ((int32_t)current_byte) << (8 * i);
	}
	return s;
}

std::istream& operator>>(std::istream& s, const read_le_int32 &ri) {
	return ri(s);
}

bool bit_reader::operator()(std::istream& in, bool& result) {
	if (index == CHAR_BIT) {
		buffer = in.get();
		index = CHAR_BIT - 1;
	}
	result = (buffer >> index) & 1u;
	if (index == 0) {
		buffer = in.get();
		if (buffer == std::ios::traits_type::eof()) {
			return false;
		}
		index = CHAR_BIT;
	}
	index--;
	return true;
}

void bit_writer::operator()(std::ostream& out, bool value) {
	buffer |= (value ? (1u << index) : 0u);
	if (index == 0) {
		out << buffer;
		buffer = 0;
		index = CHAR_BIT;
	}
	index--;
}

void bit_writer::flush(std::ostream& out) {
	if (index != CHAR_BIT - 1) {
		out << buffer;
		buffer = 0;
		index = CHAR_BIT - 1;
	}
}
