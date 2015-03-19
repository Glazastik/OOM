// NativeDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "NativeDLL.h"
#include "..\NativeLib\Messenger.h"
#include <map>
#include <queue>
#include <tuple>

using namespace std;

map<unsigned int, Messenger*> g_theMessengers;
queue<message_body> inbox_messages;
queue<message_data> outbox_messages;

typedef tuple<contact, message_header, queue<message_data>> message;
map<unsigned int, message> in_messages;
map<unsigned int, message> out_messages;

//
// Sending Messages
//
extern "C" __declspec(dllexport) void __cdecl SendMessageHeader(unsigned int messengerId, message_header header)
{

}

extern "C" __declspec(dllexport) void __cdecl SendMessageBody(unsigned int messengerId, message_body body)
{
	inbox_messages.push(body);
}

extern "C" __declspec(dllexport) void __cdecl SendMessageContact(unsigned int messengerId, contact con)
{
	
}

extern "C" __declspec(dllexport) void __cdecl _SendMessage(unsigned int messengerId)
{
	vector<wchar_t> data;
	while (!inbox_messages.empty())
	{
		message_body temp;
		temp = inbox_messages.front();
		inbox_messages.pop();
		for (int i = 0; i < 256; i++)
		{
			data.push_back(temp.message[i]);
		}
	}
	data.push_back('\0');

	contact con;

	std::map<unsigned int, Messenger*>::iterator it;
	it = g_theMessengers.find(messengerId);
	if (it != g_theMessengers.end())
	{
		//it->second->_SendMessage(data, con);
	}
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

//
// Getting Messages
//
extern "C" __declspec(dllexport) void __cdecl GetMessageData(unsigned int messengerId, message_data *pnt)
{
	std::map<unsigned int, message>::iterator it;
	it = in_messages.find(messengerId);
	message_data _pnt;
	if (it != in_messages.end())
	{
		message_data _pnt = get<2>(it->second).front();
		get<2>(it->second).pop();
		for (int i = 0; i < 256; i++)
		{
			pnt->message[i] = _pnt.message[i];
		}
	}
}

extern "C" __declspec(dllexport) void __cdecl GetMessageHeader(unsigned int messengerId, message_header *pnt)
{

}

extern "C" __declspec(dllexport) void __cdecl GetMessageContact(unsigned int messengerId, contact *pnt)
{

}

extern "C" __declspec(dllexport) bool __cdecl HasMessageData(unsigned int messengerId)
{
	std::map<unsigned int, message>::iterator it;
	it = in_messages.find(messengerId);
	if (it != in_messages.end())
	{
		return !get<2>(it->second).empty();
	}
}

extern "C" __declspec(dllexport) void __cdecl _GetMessage(unsigned int messengerId)
{
	message_data pnt;	

	pnt.message[0] = 'T';

	pnt.message[2] = 'i';
	pnt.message[3] = 's';
	
	pnt.message[4] = ' ';
	pnt.message[5] = 'i';
	pnt.message[6] = 's';
	pnt.message[7] = ' ';

	pnt.message[8] = 't';
	pnt.message[9] = 'e';
	pnt.message[10] = 's';
	pnt.message[11] = 't';

	pnt.message[12] = ' ';
	pnt.message[13] = 'm';
	pnt.message[14] = 'e';
	pnt.message[15] = 's';
	pnt.message[16] = 's';
	pnt.message[17] = 'a';
	pnt.message[18] = 'g';
	pnt.message[19] = 'e'; 

	message_header header;
	header.size = 0;
	header.leftOvers = 20;
	header.type = 0;

	contact con;
	con.id = 0;
	con.length = 4;
	con.name[0] = 't';
	con.name[1] = 'e';
	con.name[2] = 's';
	con.name[3] = 't';

	outbox_messages.push(pnt);
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
