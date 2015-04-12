#pragma once
#include "ChatService.h"
#include "GoogleHangoutConnection.h"

class GoogleHangout : public ChatService
{
public:
	GoogleHangout(std::shared_ptr<boost::asio::io_service> io_service, std::string authid, std::string password);
	~GoogleHangout();
	ServiceType::Type GetServiceType();
	void Connect();
	void CloseConnection();
	void SendChatMessage(std::string address, std::string message);
private:
	GoogleHangoutConnection googleHangoutConnection;
};
