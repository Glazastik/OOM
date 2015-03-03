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

message_t Messenger::ReadMessage(void)
{
	ofstream textfile;
	textfile.open(messengerFile, ios::out);

	message_t temp;
	temp.time = 4;
	temp.test[0] = 4;

	textfile.close();
	return temp;
}

message_t2 Messenger::ReadMessage2(void)
{
	ofstream textfile;
	textfile.open(messengerFile, ios::out);

	message_t2 temp;
	temp.time = 4;

	textfile.close();
	return temp;
}

message_t3 Messenger::ReadMessage3(void)
{
	ofstream textfile;
	textfile.open(messengerFile, ios::out);

	message_t3 temp;
	temp.message = "hej";
	textfile.close();
	return temp;
}