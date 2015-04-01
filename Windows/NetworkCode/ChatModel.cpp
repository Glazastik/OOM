#include "ChatModel.h"
#include "GoogleHangout.h"
#include "DebugBuffer.h"
#include "boost/lexical_cast.hpp"

ChatModel::ChatModel()
{
	io_service = std::make_shared<boost::asio::io_service>();
	chatServices.push_back(std::make_shared<GoogleHangout>(io_service));
}

ChatModel::~ChatModel()
{
}

void ChatModel::ConnectService(int serviceType)
{
	std::shared_ptr<ChatService> chatService = NULL;
	for (std::vector<std::shared_ptr<ChatService>>::iterator it = chatServices.begin(); it != chatServices.end(); ++it)
	{
		std::shared_ptr<ChatService> service = *it;
		if (service->GetServiceType() == serviceType)
		{
			chatService = service;
			chatService->Connect();
		}
	}
	if (chatService == NULL)
	{
		std::string errorMsg = "Error> ChatModel::ConnectService - Couldn't find service: " + boost::lexical_cast<std::string>(serviceType);
		DebugBuffer::AddLine(errorMsg);
	}
}

void ChatModel::CloseService(int serviceType)
{
	std::shared_ptr<ChatService> chatService = NULL;
	for (std::vector<std::shared_ptr<ChatService>>::iterator it = chatServices.begin(); it != chatServices.end(); ++it)
	{
		std::shared_ptr<ChatService> chatService = *it;
		if (chatService->GetServiceType() == serviceType)
		{
			chatService->CloseConnection();
		}
	}
	if (chatService == NULL)
	{
		std::string errorMsg = "Error> ChatModel::ConnectService - Couldn't find service: " + boost::lexical_cast<std::string>(serviceType);
		DebugBuffer::AddLine(errorMsg);
	}
}