#include "DebugBuffer.h"

std::vector<std::string> DebugBuffer::debugLines;

// Public
std::string DebugBuffer::ReadLine(int lineNum)
{
	std::string printLine = "";
	if (!debugLines.empty() && lineNum < debugLines.size())
	{
		printLine = debugLines.at(lineNum);
	}
	return printLine;
}

int DebugBuffer::GetNumLines()
{
	return debugLines.size();
}

void DebugBuffer::AddLine(const std::string& line)
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
