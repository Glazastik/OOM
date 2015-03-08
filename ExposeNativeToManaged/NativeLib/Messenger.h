#pragma once
#include <string>

using namespace std;

struct message_t {
	int time;
	int test[5];
};

class Messenger
{
public:
	Messenger(string file);
	Messenger();
	~Messenger();

	//Writing messages
	void WriteMessage(unsigned int message);
	void WriteMessage(const char *message);
	void WriteMessage(message_t message);
	void WriteMessage(int *message, int capacity);

	//Reading messages
	int ReadMessageInt(void);
	message_t ReadMessageStruct(void);
	const wchar_t * ReadMessageString(void);
	const int * ReadMessageIntArray(void);
private:
	string messengerFile;
};


