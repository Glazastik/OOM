#pragma once
#include <iostream>
#include "boost/system/error_code.hpp"

class DebugUtility
{
private:
	DebugUtility();
	~DebugUtility();
public:
	static void DebugPrint(std::string debugStr);
	static void DebugPrintRead(std::string readStr);
	static void DebugPrintWrite(std::string writeStr);
	static void DebugPrintError(boost::system::error_code error_code);
	static void DebugPrintException(std::exception& exception);
};

