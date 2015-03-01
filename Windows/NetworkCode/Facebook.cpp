#include "Facebook.h"
#include "TokenHandler.h"
#include "HttpClient.h"
#include <sstream>
std::string userID;
Facebook::Facebook(){


}
Facebook::~Facebook(){


}

void GetUserID(){
	/*Returned in JSON, must parse*/
	std::string response = HttpClient::httpGet("graph.facebook.com/me?fields=id");
}

void GetFriends(){
	/*Returned in JSON, must parse into a list for example. Enable user to check the friends he wants to import
	Then if checked, save name and userID (for sending messages to this user)
	"data": [
    {
      "name": "Bullen von Carlsson", 
      "id": "1066784008"
    }, 
    {
      "name": "Mackan Fika", 
      "id": "1425567862"
    }/**/
	std::string response = HttpClient::httpGet("graph.facebook.com/"+userID+"/friends");
}
void postToWall(std::string message){
	TokenHandler tk;
	std::string post = "graph.facebook.com/me/feed?message="+message+"&access_token="+tk.getToken();
	HttpClient client;
	client.httpPost(post);
}