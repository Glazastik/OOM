#pragma once
#include <string>

using namespace std;

struct message_t {
	int time;
	int test [5];
};

struct message_t2 {
	int time;
};

struct message_t3 {
	const char *message;
};

class Messenger
{
public:
	Messenger(string file);
	Messenger();
	~Messenger();

	void WriteMessage(unsigned int message);
	void WriteMessage(const char *message);
	void WriteMessage(message_t message);
	message_t ReadMessage(void);
	message_t2 ReadMessage2(void);
	message_t3 ReadMessage3(void);
private:
	string messengerFile;
};


