#include "stdafx.h"
#include "Messenger.h"

#include <iostream>

#include <string>
#include <fstream>

using namespace std;

Messenger::Messenger(int id, string file) : messengerId(id)
{
	switch (id)
	{
		case 0:
			messengerFile = "0.txt";
			break;
		case 1: 
			messengerFile = "1.txt";
			break;
		case 2:	
			messengerFile = "2.txt";
			break;
		default: 
			messengerFile = "default.txt";
	}
	//messengerFile = to_string(id) + '/' + file;
}

Messenger::Messenger()
{ 
	messengerId = 0;
	messengerFile = "default.txt";
}


Messenger::~Messenger()
{

}

void Messenger::_SendMessage(messenger msgr, message msg)
{
	ofstream textfile;
	textfile.open(messengerFile, ios::out);

	textfile << "MESSAGE:";
	textfile << '\n';	
	for (int i = 0; i < msg.data_length; i++) {
		textfile << (char)msg.data[i];
	}
	textfile << '\0';
	textfile << '\n';
	textfile << "FROM:";
	textfile << '\n';
	for (int i = 0; i < msg.cid_length; i++) {
		textfile << (char)msg.cid[i];
	}
	textfile << '\n';
	textfile.close();
}

message Messenger::_GetMessage(messenger msgr)
{
	message temp;

	temp.data_length = 3;
	temp.data = new wchar_t[3];
	temp.data[0] = 'h';
	temp.data[1] = 'e';
	temp.data[2] = 'j';

	temp.cid_length = 3;
	temp.cid = new wchar_t[3];
	temp.cid[0] = 'c';
	temp.cid[1] = 'i';
	temp.cid[2] = 'd';

	return temp;
}

vector<contact> Messenger::GetContacts(messenger msgr)
{
	vector<contact> v;
	contact c;

	c.id_length = 3;
	c.id = new wchar_t[3];
	c.id[0] = 'c';
	c.id[1] = 'c';
	c.id[2] = 'c';


	c.name_length = 3;
	c.name = new wchar_t[3];
	c.name[0] = 'a';
	c.name[1] = 'b';
	c.name[2] = 'c';

	contact d;
	d.id_length = 3;
	d.id = new wchar_t[3];
	d.id[0] = 'd';
	d.id[1] = 'd';
	d.id[2] = 'd';


	d.name_length = 3;
	d.name = new wchar_t[3];
	d.name[0] = 'd';
	d.name[1] = 'e';
	d.name[2] = 'f';

	v.push_back(c);
	v.push_back(d);

	return v;
}
bool Messenger::HasMessage(messenger msgr)
{
	return true;
}

/*unsigned int Messenger::_GetMessenger()
{
	return 0;
}

vector<wchar_t> Messenger::_GetMessage()
{
	vector<wchar_t> data;
	data.push_back('h');
	data.push_back('e');
	data.push_back('j');
	return data;
}

contact Messenger::_GetContact()
{
	contact con;
	con.id = 2;
	con.length = 2;
	con.name = new wchar_t[2];
	con.name[0] = 'a';
	con.name[1] = 'b';
	return con;
}  */

void Messenger::WriteMessage(unsigned int message)
{
	ofstream textfile;
	textfile.open(messengerFile, ios::out);
	textfile << message;
	textfile << '\n';
	textfile.close();
}

void Messenger::WriteMessage(const char *message)
{
	ofstream textfile;
	textfile.open(messengerFile, ios::out);
	for (const char *p = message; *p != '\0'; p++) {
		textfile << *p;
	}
	textfile << '\n';
	textfile.close();
}

void Messenger::WriteMessage(message_t message)
{
	ofstream textfile;
	textfile.open(messengerFile, ios::out);

	textfile << message.time;
	textfile << '\n';
	textfile << '\n';
	textfile.close();
}

void Messenger::WriteMessage(int *message, int capacity)
{
	ofstream textfile;
	textfile.open(messengerFile, ios::out);

	for (int i = 0; i < capacity; message++, i++) {
		textfile << *message;
	}
	textfile << '\n';
	textfile.close();
}

int Messenger::ReadMessageInt(void)
{
	return 1;
}

const wchar_t * Messenger::ReadMessageString(void)
{
	wchar_t *str = new wchar_t[5];
	str[0] = 'h';
	str[1] = 'e';
	str[2] = 'j';
	str[3] = '\0';
	str[4] = 't';
	return str;
}

const int * Messenger::ReadMessageIntArray(void)
{
	int *arr = new int[4];
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 2;
	arr[3] = 3;
	return arr;
}

message_t Messenger::ReadMessageStruct(void)
{
	ofstream textfile;
	textfile.open(messengerFile, ios::out);

	message_t temp;
	temp.time = 4;
	temp.test[0] = 4;
	temp.test[1] = 3;
	textfile.close();
	return temp;
}
