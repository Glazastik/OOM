extern "C"
{
	__declspec(dllexport) void init();
	__declspec(dllexport) void stop();
	__declspec(dllexport) void connectService(int serviceType);
	__declspec(dllexport) int readMessage(size_t messageNum, char* messageBuffer, int bufferCapacity);
	__declspec(dllexport) int getNumMessages();
	__declspec(dllexport) void addPerson(int id, const char* name);
	__declspec(dllexport) void addAccountToPerson(int personId, int accountId, int serviceType, const char* address);
	__declspec(dllexport) void sendChatMessage(int accountId, const char* message);
}