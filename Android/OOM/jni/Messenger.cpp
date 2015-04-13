#include "Messenger.h"

using namespace std;

Messenger::Messenger(int id) : messengerId(id)
{

}

Messenger::Messenger()
{ 
	messengerId = 0;
}

Messenger::~Messenger()
{

}

void Messenger::_SendMessage(messenger msgr, message msg)
{


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
