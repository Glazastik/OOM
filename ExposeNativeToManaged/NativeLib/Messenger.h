#pragma once
#include <string>
#include <vector>

using namespace std;

struct message_t {
	int time;
	int test[5];
};

struct message_header {
	int size;
	int leftOvers;
	int type;
};

struct message_body {
	int id;
	int index;
	wchar_t message[256];
};

struct message_data {
	wchar_t message[256];
};

// MESSENGERS
#define IRC 0
#define GOOGLE 1
#define FACEBOOK 2

typedef unsigned int uint;
typedef uint messenger;
struct message {
	int data_length;
	wchar_t *data;
	int cid_length;
	wchar_t *cid;
};

struct contact {
	int id_length;
	wchar_t *id;
	int name_length;
	wchar_t *name;
};

struct login {
	int userNameSize;
	wchar_t *userName;
	int passwordSize;
	wchar_t *password;
};

class Messenger
{
public:

	Messenger(int id, string file);
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

	// Sending and getting messages
	void _SendMessage(messenger msgr, message msg);
	bool HasMessage(messenger msgr);
	message _GetMessage(messenger msgr);

	// Getting contacts
	vector<contact> GetContacts(messenger);

private:

	int messengerId;
	string messengerFile;

};


