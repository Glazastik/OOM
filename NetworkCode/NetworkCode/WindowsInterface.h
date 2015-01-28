extern "C"
{
	__declspec(dllexport) void testConnect(int serviceType, char* buffer, int bufferCapacity);
	__declspec(dllexport) void getMessage(char* messageBuffer, int bufferCapacity);
}