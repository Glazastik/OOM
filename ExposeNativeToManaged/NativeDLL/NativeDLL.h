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

//Testa utan extern "C" sen

struct message_s {
	unsigned char second[4];
};

extern "C" NATIVEDLL_API unsigned int __cdecl CreateMessenger();
extern "C" NATIVEDLL_API void __cdecl DeleteMessenger(unsigned int MessengerId);
extern "C" NATIVEDLL_API void __cdecl WriteMessageInt(unsigned int messengerId, unsigned int message);
extern "C" NATIVEDLL_API void __cdecl WriteMessageString(unsigned int messengerId, const char *message);
extern "C" NATIVEDLL_API void __cdecl WriteMessageStruct(unsigned int messengerId, message_t message);
extern "C" NATIVEDLL_API message_t __cdecl ReadMessage(unsigned int messengerId);
extern "C" NATIVEDLL_API message_t2 __cdecl ReadMessage2(unsigned int messengerId);
extern "C" NATIVEDLL_API message_t3 __cdecl ReadMessage3(unsigned int messengerId);

extern "C" NATIVEDLL_API message_s Test();

extern "C" __declspec(dllexport) unsigned int Dummy();
extern "C" __declspec(dllexport) void __cdecl Dummy2(wchar_t *str, int capacity);
extern "C" __declspec(dllexport) void __cdecl Dummy3(unsigned char *pnt, int capacity);
extern "C" __declspec(dllexport) unsigned char * __cdecl Dummy4();
extern "C" __declspec(dllexport) void __cdecl Dummy5(message_t *pnt, int size);


extern "C" __declspec(dllexport) bool __cdecl HasMessage(void);
typedef void(__stdcall *FUNCTION)(int arg1);
extern "C" __declspec(dllexport) bool __cdecl CallingBack(FUNCTION func);