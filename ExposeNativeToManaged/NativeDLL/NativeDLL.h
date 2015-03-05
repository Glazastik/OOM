#ifdef NATIVEDLL_EXPORTS
#define NATIVEDLL_API __declspec(dllexport)
#else
#define NATIVEDLL_API __declspec(dllimport)
#endif

#include "..\NativeLib\Messenger.h"

/*Calling convention
One of the things that should be taken in consideration when exporting 
functions that takes some parameters is: Calling Conventions. Generally, 
it's the way for telling who (the Caller or the Callee) is responsible 
for cleaning the stack after the function has been finished. The default 
calling convention for a C++ program is __cdecl. Anyway, we can declare 
it explicitly (using the __cdecl keyword):*/

/*Keep the function entry point name as the original function name
Another thing that should be taken in consideration when exporting 
functions, is the functions' entry-points' names. In order to enable 
Function Overloading, the C++ compiler performs Name mangling on the 
functions' names. For preventing the C++ name mangling (and keep the 
functions entry-points as the original functions' names), we can 
declare the functions with the extern "C" keyword:*/

extern "C" NATIVEDLL_API unsigned int __cdecl CreateMessenger();
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