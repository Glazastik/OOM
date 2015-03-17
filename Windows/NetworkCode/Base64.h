#pragma once
#include <iostream>

class Base64
{
public:
	static std::string Encode(const char* data, const size_t length);
private:
	Base64();
	~Base64();
};

