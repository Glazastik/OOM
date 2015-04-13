#include <iostream>
class HttpClient
{

public:
	HttpClient();
	~HttpClient();
	static std::string httpGet(std::string);
	void httpPost(std::string);


};