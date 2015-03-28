#include "ChatModel.h"
#include "GoogleHangout.h"
#include "DebugBuffer.h"

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
		DebugBuffer::AddLine("Error - Couldn't find service: " + serviceType);
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
		DebugBuffer::AddLine("Error - Couldn't find service: " + serviceType);
	}
}