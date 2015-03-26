// NativeDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "NativeDLL.h"
#include "..\NativeLib\Messenger.h"
#include <map>
#include <queue>
#include <tuple>

#include <iostream>

#include <string>
#include <fstream>

using namespace std;

map<unsigned int, Messenger*> g_theMessengers;
queue<message_body> inbox_messages;
queue<message_data> outbox_messages;

typedef uint messenger;
typedef tuple<messenger, vector<wchar_t>, contact> message;


Messenger* g_theMessenger;
message in_message;
message out_message;

map<unsigned int, message> in_messages;
map<unsigned int, message> out_messages;

extern "C" NATIVEDLL_API void __cdecl Initiliaze()
{
	g_theMessenger = new Messenger(0, "new.txt");
}

extern "C" NATIVEDLL_API void __cdecl AddMessenger(unsigned int messengerId)
{
	static unsigned int s_nextWorkerId = 0;

	unsigned int currWorkerId = s_nextWorkerId;
	g_theMessengers[messengerId] = new Messenger(messengerId, "new.txt");

	s_nextWorkerId++;
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

//
// Getting Messages
//
extern "C" __declspec(dllexport) void __cdecl _GetMessage()
{
	messenger msgr = g_theMessenger->_GetMessenger();
	vector<wchar_t> data = g_theMessenger->_GetMessage();
	contact con = g_theMessenger->_GetContact();
	in_message = make_tuple(msgr, data, con);
}

extern "C" __declspec(dllexport) uint __cdecl GetMessageSize()
{
	return get<1>(in_message).size();
}

extern "C" __declspec(dllexport) uint __cdecl GetMessageMessenger()
{
	return get<0>(in_message);
}

extern "C" __declspec(dllexport) void __cdecl GetMessageData(wchar_t *pnt)
{
	for (uint i = 0; i < get<1>(in_message).size(); i++, pnt++)
	{
		*pnt = get<1>(in_message)[i];
	}
}

extern "C" __declspec(dllexport) void __cdecl GetMessageContact(contact *pnt)
{
	pnt->id = get<2>(in_message).id;
	pnt->length = get<2>(in_message).length;
	pnt->name = pnt->name;
}

extern "C" __declspec(dllexport) void __cdecl GetMessageContactName(wchar_t *pnt)
{
	for (int i = 0; i < get<2>(in_message).length; i++, pnt++)
	{
		*pnt = get<2>(in_message).name[i];
	} 	
}

extern "C" __declspec(dllexport) uint __cdecl GetMessageContactNameSize()
{
	return get<2>(in_message).length;
}
//
// Sending Messages
//
extern "C" __declspec(dllexport) void __cdecl SendMessageMessenger(uint msgr)
{
	get<0>(out_message) = msgr;
}

extern "C" __declspec(dllexport) void __cdecl SendMessageData(const wchar_t *str, uint length)
{
	for (uint i = 0; i < length; i++, str++)
	{
		get<1>(out_message).push_back(*str);
	}
}

/*
*
* Old version of _SendMessageData
*
extern "C" __declspec(dllexport) void __cdecl SendMessageData(const wchar_t *str, uint length)
{
	ofstream textfile;
	string messengerFile = "test.txt";
	textfile.open(messengerFile, ios::out);
	for (uint i = 0; i < length; i++, str++)
	{
		get<1>(out_message).push_back(*str);
		textfile << (char)*str;
	}	
	textfile.close();
}
*/

extern "C" __declspec(dllexport) void __cdecl SendMessageContact(contact *con)
{
	get<2>(out_message).id = con->id;
	get<2>(out_message).length = con->length;
	get<2>(out_message).name = get<2>(out_message).name;
}

extern "C" __declspec(dllexport) void __cdecl SendMessageContactName(wchar_t *pnt, int length)
{
	get<2>(out_message).name = new wchar_t[length];
	for (int i = 0; i < length; i++, pnt++)
	{
		get<2>(out_message).name[i] = *pnt;
	}
}

extern "C" __declspec(dllexport) void __cdecl _SendMessage()
{
	g_theMessenger->_SendMessage(get<1>(out_message), get<2>(out_message));
}

extern "C" __declspec(dllexport) bool __cdecl Login(uint messengerId, login *log)
{
	ofstream textfile;
	string messengerFile = "test.txt";
	textfile.open(messengerFile, ios::out);
	for (uint i = 0; i < log->userNameSize; i++)
	{
		textfile << (char)log->userName[i];
	}
	textfile.close();
	return true;
}

//
// Other functions
//

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


/* -  - - - - - - - - - - -- - - - - - - ----------  -- - - - - -- - - - -- -  --  - - -- - - - - -*/
/* -  - - - - - - - - - - -- - - - - - - DONT CARE!  -- - - - - -- - - - -- -  --  - - -- - - - - -*/
/* -  - - - - - - - - - - -- - - - - - - ----------  -- - - - - -- - - - -- -  --  - - -- - - - - -*/

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

