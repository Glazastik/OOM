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

extern "C" NATIVEDLL_API void __cdecl WriteMessageInt(unsigned int messengerId, unsigned int message)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	if (it != g_theMessengers.end())
	{
		it->second->WriteMessage(message);
	}
}

extern "C" __declspec(dllexport) unsigned int Dummy()
{
	unsigned int test = 1;
	return test;
}

extern "C" __declspec(dllexport) void __cdecl Dummy2(wchar_t *str, int capacity)
{
	str[0] = 'h';
	str[1] = 'e';
	str[2] = 'j';
	str[3] = '\0';
	str[4] = 't';
}

extern "C" __declspec(dllexport) void __cdecl Dummy3(unsigned char *pnt, int capacity)
{
	pnt[0] = (unsigned char)20;
	pnt[1] = (unsigned char)23;
	pnt[2] = (unsigned char)40;
	pnt[3] = (unsigned char)100;
}

extern "C" __declspec(dllexport) unsigned char * __cdecl Dummy4()
{
	unsigned char pnt[4];
	pnt[0] = (unsigned char)20;
	pnt[1] = (unsigned char)23;
	pnt[2] = (unsigned char)40;
	pnt[3] = (unsigned char)100;
	return pnt;
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

extern "C" NATIVEDLL_API void __cdecl WriteMessageStruct(unsigned int messengerId, message_t message)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	if (it != g_theMessengers.end())
	{
		it->second->WriteMessage(message);
	}
}

extern "C" NATIVEDLL_API message_t __cdecl ReadMessage(unsigned int messengerId)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	message_t temp;
	if (it != g_theMessengers.end())
	{
		temp = it->second->ReadMessage();
	}
	return temp;
}

extern "C" NATIVEDLL_API message_t2 __cdecl ReadMessage2(unsigned int messengerId)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	message_t2 temp;
	if (it != g_theMessengers.end())
	{
		temp = it->second->ReadMessage2();
	}
	return temp;
}

extern "C" NATIVEDLL_API message_t3 __cdecl ReadMessage3(unsigned int messengerId)
{
	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	message_t3 temp;
	if (it != g_theMessengers.end())
	{
		temp = it->second->ReadMessage3();
	}
	return temp;
}

extern "C" NATIVEDLL_API message_s Test()
{
	message_s temp;
	temp.second[0] = '1';
	temp.second[1] = '2';
	temp.second[2] = '3';
	temp.second[3] = '4';
	return temp;
}

extern "C" __declspec(dllexport) void __cdecl Dummy5(message_t *pnt, int size)
{
	pnt->time = 4;
	pnt->test[0] = 0;
	pnt->test[1] = 1;
	pnt->test[2] = 2;
	pnt->test[3] = 3;
	pnt->test[4] = 4;

	/*int *test = (int *)pnt;
	*test = 3;
	test++;
	*test = 7;
	test++;
	*test = 6;
	test++;
	*test = 2;*/
}
