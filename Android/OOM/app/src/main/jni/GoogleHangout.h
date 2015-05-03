#pragma once
#include "ChatService.h"
#include "GoogleHangoutConnection.h"

class GoogleHangout : public ChatService
{
public:
	GoogleHangout(std::shared_ptr<boost::asio::io_service> io_service, std::string authid, std::string password, std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons);
	~GoogleHangout();
	ServiceType::Type GetServiceType();
	void Connect();
	void CloseConnection();
	void SendChatMessage(std::string address, std::string message);
private:
	GoogleHangoutConnection googleHangoutConnection;
};
