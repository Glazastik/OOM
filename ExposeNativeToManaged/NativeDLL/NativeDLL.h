#ifdef NATIVEDLL_EXPORTS
#define NATIVEDLL_API __declspec(dllexport)
#else
#define NATIVEDLL_API __declspec(dllimport)
#endif

#include "..\NativeLib\Messenger.h"

#define IRC 0
#define GOOGLE 1

extern "C" NATIVEDLL_API void __cdecl AddMessenger(unsigned int messengerId);
extern "C" NATIVEDLL_API void __cdecl DeleteMessenger(unsigned int MessengerId);

extern "C" NATIVEDLL_API void __cdecl WriteMessageInt(unsigned int messengerId, int message);
extern "C" NATIVEDLL_API void __cdecl WriteMessageString(unsigned int messengerId, const char *message);
extern "C" NATIVEDLL_API void __cdecl WriteMessageIntArray(unsigned int messengerId, int *message, int capacity);
extern "C" NATIVEDLL_API void __cdecl WriteMessageStruct(unsigned int messengerId, message_t message);

extern "C" __declspec(dllexport) int __cdecl ReadMessageInt(unsigned int messengerId);
extern "C" __declspec(dllexport) void __cdecl ReadMessageString(unsigned int messengerId, wchar_t *str, int capacity);
extern "C" __declspec(dllexport) void __cdecl ReadMessageCharArray(unsigned int messengerId, wchar_t *pnt, int capacity);
extern "C" __declspec(dllexport) void __cdecl ReadMessageIntArray(unsigned int messengerId, int *pnt, int capacity);
extern "C" __declspec(dllexport) void __cdecl ReadMessageStruct(unsigned int messengerId, message_t *pnt, int size);


extern "C" __declspec(dllexport) bool __cdecl HasMessage(void);

typedef void(__stdcall *FUNCTION)(int arg1);
extern "C" __declspec(dllexport) bool __cdecl CallingBack(FUNCTION func);


extern "C" __declspec(dllexport) void __cdecl SendMessageHeader(unsigned int messengerId, message_header header);
extern "C" __declspec(dllexport) void __cdecl SendMessageData(unsigned int messengerId, message_body body);
extern "C" __declspec(dllexport) void __cdecl SendMessageContact(unsigned int messengerId, contact con);
extern "C" __declspec(dllexport) void __cdecl _SendMessage(unsigned int messengerId);

extern "C" __declspec(dllexport) void __cdecl GetMessageHeader(unsigned int messengerId, message_header *pnt);
extern "C" __declspec(dllexport) void __cdecl GetMessageData(unsigned int messengerId, message_data *pnt);
extern "C" __declspec(dllexport) void __cdecl GetMessageContact(unsigned int messengerId, contact *pnt);
extern "C" __declspec(dllexport) bool __cdecl HasMessageData(unsigned int messengerId);
extern "C" __declspec(dllexport) void __cdecl _GetMessage(unsigned int messengerId);
