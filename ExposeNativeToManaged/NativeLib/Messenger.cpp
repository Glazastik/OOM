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

void Messenger::_SendMessage(vector<wchar_t> data, contact con)
{
	ofstream textfile;
	textfile.open(messengerFile, ios::out);

	textfile << "MESSAGE:";
	textfile << '\n';	
	for (unsigned int i = 0; i < data.size(); i++) {
		textfile << (char) data[i];
	}
	textfile << '\0';
	textfile << '\n';
	textfile << "FROM:";
	textfile << '\n';
	textfile << (char)con.name[0];
	textfile << (char)con.name[1];
	textfile << '\n';
	textfile.close();
}
unsigned int Messenger::_GetMessenger()
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
}

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
	wchar_t str[5];
	str[0] = 'h';
	str[1] = 'e';
	str[2] = 'j';
	str[3] = '\0';
	str[4] = 't';
	return str;
}

const int * Messenger::ReadMessageIntArray(void)
{
	int arr[4];
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
