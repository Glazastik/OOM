#include "Base64.h"
#include <string>
#include <limits>
#include <stdexcept>
#include <cctype>

const char b64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char reverse_table[128] = {
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
	64, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
	64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
};

Base64::Base64()
{
}

Base64::~Base64()
{
}

std::string Base64::Encode(const char* bindata, const size_t binlen)
{
	if (binlen > (std::numeric_limits<std::string::size_type>::max() / 4u) * 3u) 
	{
		throw std::length_error("Converting too large a string to base64.");
	}

	// Use '=' signs so the end is properly padded
	std::string retval((((binlen + 2) / 3) * 4), '=');
	std::size_t outpos = 0;
	int bits_collected = 0;
	unsigned int accumulator = 0;

	for (size_t i = 0; i < binlen; i++)
	{
		accumulator = (accumulator << 8) | (bindata[i] & 0xffu);
		bits_collected += 8;
		while (bits_collected >= 6) 
		{
			bits_collected -= 6;
			retval[outpos++] = b64_table[(accumulator >> bits_collected) & 0x3fu];
		}
	}
	if (bits_collected > 0) // Any trailing bits that are missing
	{
		accumulator <<= 6 - bits_collected;
		retval[outpos++] = b64_table[accumulator & 0x3fu];
	}
	return retval;
}