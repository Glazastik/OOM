extern "C"
{
	__declspec(dllexport) void init();
	__declspec(dllexport) int readMessage(size_t messageNum, char* messageBuffer, int bufferCapacity);
	__declspec(dllexport) int getNumMessages();
	__declspec(dllexport) void connectService(int serviceType);
	__declspec(dllexport) void closeService(int serviceType);
}