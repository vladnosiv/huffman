#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <climits>

class write_uchar {
public:
	write_uchar(const unsigned char value_) : value(value_) {}
	std::ostream& operator()(std::ostream&) const;
private:
	unsigned char value;
};

std::ostream& operator<<(std::ostream&, const write_uchar&);

class read_uchar {
public:
	read_uchar(unsigned char &value_) : value(value_) {}
	std::istream& operator()(std::istream&) const;
private:
	unsigned char& value;
};

std::istream& operator>>(std::istream&, const read_uchar&);

class write_le_int32 {
public:
	write_le_int32(const int32_t value_) : value(value_) {}
	std::ostream& operator()(std::ostream&) const;
private:
	int32_t value;
};

std::ostream& operator<<(std::ostream&, const write_le_int32&);

class read_le_int32 {
public:
	read_le_int32(int32_t &value_) : value(value_) {}
	std::istream& operator()(std::istream&) const;
private:
	int32_t& value;
};

std::istream& operator>>(std::istream&, const read_le_int32&);

class bit_reader {
public:
	bool operator()(std::istream&, bool&);
private:
	unsigned char buffer = 0u, index = CHAR_BIT;
};

class bit_writer {
public:
	void operator()(std::ostream& out, bool value);
	void flush(std::ostream& out);
private:
	unsigned char buffer = 0u, index = CHAR_BIT - 1;
};
