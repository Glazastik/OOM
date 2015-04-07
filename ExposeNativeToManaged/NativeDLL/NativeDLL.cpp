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

// OBSOLETE
map<unsigned int, Messenger*> g_theMessengers;
queue<message_body> inbox_messages;
queue<message_data> outbox_messages;

/*map<unsigned int, message> in_messages;
map<unsigned int, message> out_messages;*/

// ACTIVE


//typedef tuple<messenger, vector<wchar_t>, contact> message;	  //Ska ändras till struct

Messenger* g_theMessenger;
message in_message;
message out_message;

map<messenger, vector<contact>> list_of_contacts;     // Fixa implementation
contact buffer_contact;
vector<contact> buffer_contacts;		  //for multi threading
//
// CONSTRUCT AND DESTRUCT
//
extern "C" NATIVEDLL_API void __cdecl Initiliaze()
{
	g_theMessenger = new Messenger();
}

extern "C" NATIVEDLL_API void __cdecl DeleteMessenger()
{
	delete g_theMessenger;
}

//
// OBSOLETE
//
/*extern "C" NATIVEDLL_API void __cdecl AddMessenger(unsigned int messengerId)
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
}	 */

 // CHANGE GET MESSAGE TO TAKE INTEGER AS PARAMETER FOR WHICH MESSENGER TO GET FROM

//
// Getting Messages
//
extern "C" __declspec(dllexport) bool __cdecl HasMessage(void)
{
	return true;
}

extern "C" __declspec(dllexport) void __cdecl _GetMessage()
{
	//messenger msgr = g_theMessenger->_GetMessenger();
	//vector<wchar_t> data = g_theMessenger->_GetMessage();
	//contact con = g_theMessenger->_GetContact();
	//in_message = make_tuple(msgr, data, con);
	in_message = g_theMessenger->_GetMessage();
}

extern "C" __declspec(dllexport) uint __cdecl GetMessageMessenger()
{
	//return get<0>(in_message);
	return in_message.msgr;
}

extern "C" __declspec(dllexport) uint __cdecl GetMessageDataSize()
{
	//return get<1>(in_message).size();
	return in_message.data_length;
}

extern "C" __declspec(dllexport) void __cdecl GetMessageData(wchar_t *pnt)
{
	/*for (uint i = 0; i < get<1>(in_message).size(); i++, pnt++)
	{
		*pnt = get<1>(in_message)[i];
	}*/
	for (int i = 0; i < in_message.data_length; i++, pnt++)
	{
		*pnt = in_message.data[i];
	}
}

extern "C" __declspec(dllexport) uint __cdecl GetMessageCidSize()
{
	//return get<1>(in_message).size();
	return in_message.cid_length;
}

extern "C" __declspec(dllexport) void __cdecl GetMessageCid(wchar_t *pnt)
{
	for (int i = 0; i < in_message.cid_length; i++, pnt++)
	{
		*pnt = in_message.cid[i];
	}
}

//
// Sending Messages
//
extern "C" __declspec(dllexport) void __cdecl SendMessageMessenger(messenger msgr)
{
	out_message.msgr = msgr;
}

extern "C" __declspec(dllexport) void __cdecl SendMessageData(const wchar_t *data, int length)
{
	out_message.data_length = length;
	out_message.data = new wchar_t[length];
	for (int i = 0; i < length; i++, data++)
	{
		out_message.data[i] = *data;
	}
}

extern "C" __declspec(dllexport) void __cdecl SendMessageCid(const wchar_t *cid, int length)
{
	out_message.cid_length = length;
	out_message.cid = new wchar_t[length];
	for (int i = 0; i < length; i++, cid++)
	{
		out_message.cid[i] = *cid;
	}
}

extern "C" __declspec(dllexport) void __cdecl _SendMessage()
{
	g_theMessenger->_SendMessage(out_message);
}

//
//	Contact functions
//
extern "C" __declspec(dllexport) void __cdecl GetContacts(messenger msgr)
{
	list_of_contacts[msgr] = g_theMessenger->GetContacts(msgr);
}

extern "C" __declspec(dllexport) bool __cdecl HasContact(messenger msgr)
{
	map<messenger, vector<contact>>::iterator it;
	it = list_of_contacts.find(msgr);
	if (it != list_of_contacts.end())
	{
		if (it->second.size() > 0) {
			return true;
		}
		else {
			list_of_contacts.erase(it);
		}
	}
	return false;
}

extern "C" __declspec(dllexport) void __cdecl GetContact(messenger msgr)
{
	map<messenger, vector<contact>>::iterator it;
	it = list_of_contacts.find(msgr);
	buffer_contact = it->second.back();
	it->second.pop_back();
}

extern "C" __declspec(dllexport) uint __cdecl GetContactIdSize()
{
	return buffer_contact.id_length;
}

extern "C" __declspec(dllexport) void __cdecl GetContactId(wchar_t *pnt)
{
	for (int i = 0; i < buffer_contact.id_length; i++, pnt++)
	{
		*pnt = buffer_contact.id[i];
	}
}

extern "C" __declspec(dllexport) uint __cdecl GetContactNameSize()
{
	return buffer_contact.name_length;
}

extern "C" __declspec(dllexport) void __cdecl GetContactName(wchar_t *pnt)
{
	for (int i = 0; i < buffer_contact.name_length; i++, pnt++)
	{
		*pnt = buffer_contact.name[i];
	}
}

//
// Login functions
//
extern "C" __declspec(dllexport) bool __cdecl Login(uint messengerId, login *log)
{
	ofstream textfile;
	string messengerFile = "test.txt";
	textfile.open(messengerFile, ios::out);
	for (int i = 0; i < log->userNameSize; i++)
	{
		textfile << (char)log->userName[i];
	}
	textfile.close();
	return true;
}

//
// Other functions
//


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
	pnt[0] = (wchar_t)'h';
	pnt[1] = (wchar_t)'h';
	pnt[2] = 'h';
	pnt[3] = 'h';
	pnt[4] = 'h';
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

