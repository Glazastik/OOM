#pragma once
#include "boost/lexical_cast.hpp"
#include "DebugUtility.h"
#include <sstream>

struct ServiceType
{
public:
	enum Type
	{
		GOOGLE_HANGOUT,
		IRC
	};
	static const int NUM_TYPES = 2;

	static ServiceType::Type TypeOfIndex(int i)
	{
		if (i >= NUM_TYPES)
		{
			std::stringstream stream;
			stream << "ServiceType::TypeOfIndex - Couldn't find type with index: " << boost::lexical_cast<std::string>(i);
			DebugUtility::DebugPrint(stream.str());
		}
		return static_cast<ServiceType::Type>(i);
	}
};