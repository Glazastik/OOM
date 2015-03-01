#include "ChatModel.h"
#include "GoogleHangout.h"

ChatModel::ChatModel()
{
	chatServices.push_back(std::make_shared<GoogleHangout>());
}

ChatModel::~ChatModel()
{
}

std::string ChatModel::TestConnect(int serviceType)
{
	std::shared_ptr<GoogleHangout> googleHangout = NULL;
	for (std::vector<std::shared_ptr<ChatService>>::iterator it = chatServices.begin(); it != chatServices.end(); ++it)
	{
		std::shared_ptr<ChatService> chatService = *it;
		if (chatService->GetServiceType() == serviceType)
		{
			googleHangout = std::dynamic_pointer_cast<GoogleHangout>(chatService);
		}
		if (googleHangout == NULL)
		{
			return "Error - Couldn't find a service of given type.";
		}
	}
	return googleHangout->TestConnect();
}

std::string ChatModel::GetMessage()
{
	return "Hello World!";
}