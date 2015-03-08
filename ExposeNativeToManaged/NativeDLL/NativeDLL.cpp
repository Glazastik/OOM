// NativeDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "NativeDLL.h"
#include "..\NativeLib\Messenger.h"
#include <map>

using namespace std;

map<unsigned int, Messenger*> g_theMessengers;


extern "C" NATIVEDLL_API unsigned int __cdecl CreateMessenger()
{
	static unsigned int s_nextWorkerId = 0;

	unsigned int currWorkerId = s_nextWorkerId;
	g_theMessengers[currWorkerId] = new Messenger();

	s_nextWorkerId++;

	return currWorkerId;
}

extern "C" NATIVEDLL_API void __cdecl DeleteMessenger(unsigned int messengerId)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	if (it != g_theMessengers.end())
	{
		delete it->second;
		g_theMessengers.erase(it);
	}
}

extern "C" NATIVEDLL_API void __cdecl WriteMessageInt(unsigned int messengerId, int message)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	if (it != g_theMessengers.end())
	{
		it->second->WriteMessage(message);
	}
}

extern "C" NATIVEDLL_API void __cdecl WriteMessageString(unsigned int messengerId, const char *message)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	if (it != g_theMessengers.end())
	{
		it->second->WriteMessage(message);
	}
}

extern "C" NATIVEDLL_API void __cdecl WriteMessageIntArray(unsigned int messengerId, int *message, int capacity)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	if (it != g_theMessengers.end())
	{
		it->second->WriteMessage(message, capacity);
	}
}

extern "C" NATIVEDLL_API void __cdecl WriteMessageStruct(unsigned int messengerId, message_t message)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	if (it != g_theMessengers.end())
	{
		it->second->WriteMessage(message);
	}
}

extern "C" __declspec(dllexport) int __cdecl ReadMessageInt(unsigned int messengerId)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	if (it != g_theMessengers.end())
	{
		return it->second->ReadMessageInt();
	}
	return 0;
}

extern "C" __declspec(dllexport) void __cdecl ReadMessageString(unsigned int messengerId, wchar_t *str, int capacity)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	const wchar_t *_str;
	if (it != g_theMessengers.end())
	{
		_str = it->second->ReadMessageString();
		str[0] = _str[0];
		str[1] = _str[1];
		str[2] = _str[2];
		str[3] = _str[3];
		str[4] = _str[4];
	}
}

extern "C" __declspec(dllexport) void __cdecl ReadMessageCharArray(unsigned int messengerId, wchar_t *pnt, int capacity)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	const wchar_t *_pnt;
	if (it != g_theMessengers.end())
	{
		_pnt = it->second->ReadMessageString();
		pnt[0] = _pnt[0];
		pnt[1] = _pnt[1];
		pnt[2] = _pnt[2];
		pnt[3] = _pnt[3];
		pnt[4] = _pnt[4];
	}
}

extern "C" __declspec(dllexport) void __cdecl ReadMessageIntArray(unsigned int messengerId, int *pnt, int capacity)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	const int *_pnt;
	if (it != g_theMessengers.end())
	{
		_pnt = it->second->ReadMessageIntArray();
		pnt[0] = _pnt[0];
		pnt[1] = _pnt[1];
		pnt[2] = _pnt[2];
		pnt[3] = _pnt[3];
	}
}

extern "C" __declspec(dllexport) void __cdecl ReadMessageStruct(unsigned int messengerId, message_t *pnt, int size)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	message_t _pnt;
	if (it != g_theMessengers.end())
	{
		_pnt = it->second->ReadMessageStruct();
		pnt->time = _pnt.time;
		pnt->test[0] = _pnt.test[0];
		pnt->test[1] = _pnt.test[1];
		pnt->test[2] = _pnt.test[2];
		pnt->test[3] = _pnt.test[3];
		pnt->test[4] = _pnt.test[4];
	}
}

extern "C" __declspec(dllexport) bool __cdecl HasMessage(void)
{
	return true;
}

extern "C" __declspec(dllexport) bool __cdecl CallingBack(FUNCTION func)
{
	int i = 0;
	func(i);
	return true;
}
