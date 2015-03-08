#pragma once
#include <iostream>

class Base64
{
private:
	Base64();
	~Base64();
public:
	static std::string Encode(const char* bindata, const size_t binlen);
};

