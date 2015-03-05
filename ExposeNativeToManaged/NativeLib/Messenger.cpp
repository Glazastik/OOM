#include "stdafx.h"
#include "Messenger.h"

#include <iostream>

#include <string>
#include <fstream>

using namespace std;

Messenger::Messenger(string file) : messengerFile(file)
{

}

Messenger::Messenger()
{
	messengerFile = "temp.txt";
}


Messenger::~Messenger()
{
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
	/*for (const char *p = message.sender; *p != '\0'; p++) {
		textfile << *p;
	}
	textfile << '\n';*/
	/*for (const char *p = message.message; *p != '\0'; p++) {
		textfile << *p;
	}*/
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
