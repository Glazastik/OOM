
#include "Parsing.h"
#include <iostream>
#include <string>



using namespace std;
// Takes a string to be parsed, a reference to a variable where you want the nickname and one reference to a variable where you want the status of the message.
// example message to parse ":NICK!+"rubish" JOIN hello my name is jabba hut hut".
std::string Parsing(string message, string &nickref , string &statusref){

	//Fins the nickname of the user sending the message.
	int nicklength = message.find_first_of("!");
	nicklength--;//-1 to remove '!'
	string nickname = message.substr( 1, nicklength);
	//cout << "nicklength: ";			// needs to be on separete 
	//cout << nicklength << endl;		//rows scince we are mixing 
	cout << "nickname: ";				//string and int
	cout << nickname << endl;			//??????????????
	nickref = nickname;
	//Finds the first occurence of blankspace.
	int firstblankspace = message.find_first_of(" ");
	//cout << "first position of blankspace:";
	//cout << firstblankspace <<endl;
	
	//Finds the length of the message.
	int msglength = message.length();
	//cout << "msglength (message): ";
	//cout << msglength << endl;

	//calculates the length for substring1 i.e ("msglength" - "garbage" = "Status" + "Message").
	int substrlength1 = msglength - firstblankspace + 1;

	//removes all the "garbage" from the message.
	string relevantinfo = message.substr(firstblankspace+1, substrlength1); //+1 to get rid of the blankspace.
	//cout << "relevant info: " + relevantinfo << endl;

	// finds the second blankspace i.e the first in 'relevantinfo' string.
	int secondblankspace = relevantinfo.find_first_of(" ");
	//cout << "second position of blankspace:";
	//cout << secondblankspace << endl;

	//Finds the length of 'relevantinfo'.
	int msglength2 = relevantinfo.length();
	//cout << "msglength2 (relevantinfo): ";
	//cout << msglength2 << endl;

	//Takes out the 'status'
	string status = relevantinfo.substr( 0, secondblankspace);
	cout << "STATUS: " + status << endl;
	statusref = status;

	//calculates the length for substring1 i.e ("msglength2" - "STATUS" = "message").
	int substrlength2 = msglength2 - secondblankspace + 1;

	//
	string msg = relevantinfo.substr(secondblankspace + 1, substrlength2); //+1 to get rid of the blankspace.
	cout << "msg: " + msg << endl;

	//returns only the relevant message.
	return msg;
}






