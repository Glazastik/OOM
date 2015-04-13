#pragma once

#include <vector>

using namespace std;

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

	Messenger(int id);
	Messenger();
	~Messenger();

	// Sending and getting messages
	void _SendMessage(messenger msgr, message msg);
	bool HasMessage(messenger msgr);
	message _GetMessage(messenger msgr);

	// Getting contacts
	vector<contact> GetContacts(messenger);

private:

	int messengerId;
	
};


