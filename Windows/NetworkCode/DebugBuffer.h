#pragma once
#include <iostream>
#include <vector>

class DebugBuffer
{
public:
	static std::string ReadLine();
	static int GetNumLines();
	static void AddLine(std::string line);
private:
	static std::vector<std::string> debugLines;

	DebugBuffer();
	~DebugBuffer();
};

