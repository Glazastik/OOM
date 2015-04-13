#pragma once
#include "boost/log/trivial.hpp"
#include "boost/lexical_cast.hpp"

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
			BOOST_LOG_TRIVIAL(error) << "ServiceType::TypeOfIndex - Couldn't find type with index: " << boost::lexical_cast<std::string>(i);
		}
		return static_cast<ServiceType::Type>(i);
	}
};