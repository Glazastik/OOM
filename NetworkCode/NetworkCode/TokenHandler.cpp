#include "Tokenhandler.h"
#include <string.h>
#include <iostream>
#include <boost/network/uri.hpp> //cpp-netlib
#include <boost/regex.hpp>
using namespace boost::network; //cpp-netlib
std::string Token;
std::string TokenExpiry;

/*As of implementation 2015-02-10 , this may only apply to Facebook OAuth url. Time will tell*/ 
/*Setup:
VC++ Include Directories: ../Github/OOM/CPP-NETLIB/include
VC++ Lib Dir ../Github/OOM/CPP-NETLIB/lib
C++ Preprocessor: _SCL_SECURE_NO_WARNINGS
Linker General: ../Github/OOM/CPP-NETLIB/lib
Linker Input : 
cppnetlib-client-connections.lib
cppnetlib-server-parsers.lib
cppnetlib-uri.lib

*/
TokenHandler::TokenHandler(){

}
TokenHandler::~TokenHandler(){

}
std::string findTokenInfo(std::string input, std::string start, std::string ending){
	std::string data(input), begin(start), end(ending);
	boost::regex r(begin + "(.*)" + end);
	boost::smatch result;

	if (boost::regex_search(data, result, r)){
		std::cout << result[1];
		return result[1];
	}

	else{
		return "NotFound";
	}
}
/*Parse the URL down to the token fragment*/
void TokenHandler::parseUrl(char str[]){
	std::string stray;
	uri::uri instance(str);
	assert(instance.is_valid());
	std::cout << "Fragment " << instance.fragment() << std::endl;
	stray = instance.fragment();

	/*Use Booost::Regex to find the substrings we want*/
	token = findTokenInfo(stray, "=", "&");
	tokenExpiry = findTokenInfo(findTokenInfo(stray, "&", ""), "=", "");

	if (token == "NotFound"){
		//Do some error message
	}
}

std::string getToken(){
	return token;
}

