#pragma once
#include "ChatService.h"
#include "GoogleHangoutConnection.h"

class GoogleHangout : public ChatService
{
public:
	GoogleHangout(std::shared_ptr<boost::asio::io_service> io_service);
	~GoogleHangout();
	ServiceType::Type GetServiceType();
	void Connect();
	void CloseConnection();
private:
	GoogleHangoutConnection googleHangoutConnection;
};
