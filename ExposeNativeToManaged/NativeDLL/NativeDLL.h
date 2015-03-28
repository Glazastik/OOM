#ifdef NATIVEDLL_EXPORTS
#define NATIVEDLL_API __declspec(dllexport)
#else
#define NATIVEDLL_API __declspec(dllimport)
#endif

#include "..\NativeLib\Messenger.h"

#define IRC 0
#define GOOGLE 1

typedef unsigned int uint;

extern "C" NATIVEDLL_API void __cdecl Initiliaze(void);

extern "C" NATIVEDLL_API void __cdecl AddMessenger(uint messengerId);
extern "C" NATIVEDLL_API void __cdecl DeleteMessenger(uint MessengerId);

extern "C" NATIVEDLL_API void __cdecl WriteMessageInt(uint messengerId, int message);
extern "C" NATIVEDLL_API void __cdecl WriteMessageString(uint messengerId, const char *message);
extern "C" NATIVEDLL_API void __cdecl WriteMessageIntArray(uint messengerId, int *message, int capacity);
extern "C" NATIVEDLL_API void __cdecl WriteMessageStruct(uint messengerId, message_t message);

extern "C" __declspec(dllexport) int __cdecl ReadMessageInt(uint messengerId);
extern "C" __declspec(dllexport) void __cdecl ReadMessageString(uint messengerId, wchar_t *str, int capacity);
extern "C" __declspec(dllexport) void __cdecl ReadMessageCharArray(uint messengerId, wchar_t *pnt, int capacity);
extern "C" __declspec(dllexport) void __cdecl ReadMessageIntArray(uint messengerId, int *pnt, int capacity);
extern "C" __declspec(dllexport) void __cdecl ReadMessageStruct(uint messengerId, message_t *pnt, int size);


extern "C" __declspec(dllexport) bool __cdecl HasMessage(void);

typedef void(__stdcall *FUNCTION)(int arg1);
extern "C" __declspec(dllexport) bool __cdecl CallingBack(FUNCTION func);


extern "C" __declspec(dllexport) void __cdecl SendMessageMessenger(uint messengerId);
extern "C" __declspec(dllexport) void __cdecl SendMessageData(const wchar_t *str, uint length);
extern "C" __declspec(dllexport) void __cdecl SendMessageContact(contact *con);
extern "C" __declspec(dllexport) void __cdecl SendMessageContactName(wchar_t *pnt, int length);
extern "C" __declspec(dllexport) void __cdecl _SendMessage();


extern "C" __declspec(dllexport) uint __cdecl GetMessageSize();
extern "C" __declspec(dllexport) uint __cdecl GetMessageMessenger();
extern "C" __declspec(dllexport) void __cdecl GetMessageData(wchar_t *pnt);
extern "C" __declspec(dllexport) void __cdecl GetMessageContact(contact *pnt);
extern "C" __declspec(dllexport) uint __cdecl GetMessageContactNameSize();
extern "C" __declspec(dllexport) void __cdecl GetMessageContactName(wchar_t *pnt);
extern "C" __declspec(dllexport) void __cdecl _GetMessage();

extern "C" __declspec(dllexport) bool __cdecl Login(uint messengerId, login *log);
