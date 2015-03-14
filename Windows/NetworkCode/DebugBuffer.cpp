#include "DebugBuffer.h"

std::vector<std::string> DebugBuffer::debugLines;

// Public
std::string DebugBuffer::ReadLine()
{
	std::string printLine = "";
	if (!debugLines.empty())
	{
		printLine = debugLines.front();
		debugLines.pop_back();
	}
	return printLine;
}

int DebugBuffer::GetNumLines()
{
	return debugLines.size();
}

void DebugBuffer::AddLine(std::string line)
{
	debugLines.push_back(line);
}

// Private
DebugBuffer::DebugBuffer()
{
}

DebugBuffer::~DebugBuffer()
{
}
