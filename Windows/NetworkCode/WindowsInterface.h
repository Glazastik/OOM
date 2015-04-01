extern "C"
{
	__declspec(dllexport) void init();
	__declspec(dllexport) void readDebugBufferLine(int lineNum, char* lineBuffer, int bufferCapacity);
	__declspec(dllexport) int getDebugBufferSize();
	__declspec(dllexport) void connectService(int serviceType);
	__declspec(dllexport) void closeService(int serviceType);
}