#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "boost/thread/mutex.hpp"

class DebugBuffer
{
public:
	static std::string ReadLine(int lineNum);
	static int GetNumLines();
	static void AddLine(const std::string& line);
private:
	static std::vector<std::string> debugLines;

	DebugBuffer();
	~DebugBuffer();
};

