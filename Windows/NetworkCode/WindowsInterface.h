extern "C"
{
	__declspec(dllexport) void readDebugBufferLine(char* lineBuffer, int bufferCapacity);
	__declspec(dllexport) int getDebugBufferSize();
	__declspec(dllexport) void connectService(int serviceType);
	__declspec(dllexport) void closeService(int serviceType);
}