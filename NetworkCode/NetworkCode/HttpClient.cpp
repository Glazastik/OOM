#include <HttpClient.h>
#include <boost/network/protocol/http/client.hpp>
#include <iostream>
#include <boost/network/uri.hpp>
using namespace boost::network;

HttpClient::HttpClient(){

}
HttpClient::~HttpClient(){

}
std::string httpGet(std::string uri){

	http::client client;
	http::client::request request(uri);
	request << header("Connection", "close");
	http::client::response response = client.get(request);
	std::cout << body(response) << std::endl;
	return body(response);
	
}

std::string httpPost(std::string uri){
	http::client client;
	http::client::request req(uri);
	http::client::response res = client.post(req);
}