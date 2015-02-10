#include <string>
class TokenHandler{

private:
	std::string token;
	std::string tokenExpiry;

public:
	TokenHandler();
	~TokenHandler();
	void parseUrl(char []);
};