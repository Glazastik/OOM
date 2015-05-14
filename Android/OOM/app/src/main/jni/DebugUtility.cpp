#include "DebugUtility.h"
#include <sstream>

#ifdef __ANDROID__
#define LOG(string)	__android_log_print(ANDROID_LOG_DEBUG, "debug", "%s", string.c_str());
#include "android/log.h"
#else
#define LOG(string)	BOOST_LOG_TRIVIAL(debug) << "\n" << string;
#include "boost/log/trivial.hpp"
#endif

// Public
void DebugUtility::DebugPrint(std::string debugStr)
{
	LOG(debugStr);
}

void DebugUtility::DebugPrintRead(std::string readStr)
{
	std::stringstream stream;
	stream << "---SERVER---\n" << readStr << "\n" << "------------" << "\n";
	DebugPrint(stream.str());
}

void DebugUtility::DebugPrintWrite(std::string writeStr)
{
	std::stringstream stream;
	stream << "---CLIENT---\n" << writeStr << "------------" << "\n";
	DebugPrint(stream.str());
}

void DebugUtility::DebugPrintError(boost::system::error_code error_code)
{
	std::stringstream stream;
	stream << "ERROR CODE: " << error_code << " - \"" << error_code.message() << "\"\n";
	DebugPrint(stream.str());
}

void DebugUtility::DebugPrintException(std::exception& exception)
{
	std::stringstream stream;
	stream << "Exception: " << exception.what();
	DebugPrint(stream.str());
}

// Private
DebugUtility::DebugUtility()
{
}

DebugUtility::~DebugUtility()
{
}
