#include "FriendsManager.hpp"


extern FriendsManager *friends_manager;


void FriendsManager::showOption(){
  printw("******* Friends manager *******\n");
  printw("0 : back to menu\n");
  printw("1 : Display all my friends\n");
	printw("2 : Add new friend\n");
	printw("3 : Delete friend\n");
  printw("4 : Friends requests\n");

}


void FriendsManager::displayFriendsMenu(){
	std::string ch;
	initscr();
	while (1) {
		showOption();
		refresh();

		while (1) {
			ch = getch();
			if(ch == "0"){
				break;
			}
			else if(ch == "1"){
				clear();
				displayAllFriends();
				break;
			}
			else if(ch == "2"){
				clear();
				displayAddFriend();
				break;
			}
			else if(ch == "3"){
				clear();
				displayDeleteFriend();
				break;
			}
      else if(ch == "4"){
				clear();
				displayFirendsRequests();
				break;
			}
			else{
				clear();
				break;
			}
		}
		if(ch == "0"){
			clear();
			break;
		}
	}
}


void FriendsManager::displayAllFriends(){
		int ch;


		while (1) {
			printw("******* All my friends (ESC to got back)*******\n");
      const char * myChar = "0";
      PacketManager::send_friend_request(4, myChar);

			refresh();

			while (1) {
				ch = getch();
				if(ch == 27){
					break;
				}
				else{
					clear();
					break;
				}
			}
			if(ch == 27){
				clear();
				break;
			}
		}

    clear();


}


void FriendsManager::printAllUsers(char *allUsers){

  printw(allUsers);
  refresh();


}


void FriendsManager::displayAddFriend(){

    std::string input;
    const char * myChar = "0";
      PacketManager::send_friend_request(0, myChar);


    printw("******* Enter Name of user you want to accept request (ENTER to validate or go back) *******\n");

    refresh();


    nocbreak();
    echo();


    int ch = getch();

    //get user name
    while ( ch != '\n' && ch != 27)
    {
        input.push_back( ch );
        ch = getch();
    }


    if(ch == '\n'){
      PacketManager::send_friend_request(1, input.c_str());



    }

    clear();

    cbreak();
}


void FriendsManager::displayDeleteFriend(){
    std::string input;

    const char * myChar = "0";
      PacketManager::send_friend_request(4, myChar);


    printw("******* Enter name of the friend that you want to remove (ENTER to validate or go back) *******\n");


    refresh();


    nocbreak();
    echo();


    int ch = getch();

    while ( ch != '\n' && ch != 27)
    {
        input.push_back( ch );
        ch = getch();
    }


    if(ch == '\n'){
      PacketManager::send_friend_request(2, input.c_str());

    }

    clear();

    cbreak();

}


void FriendsManager::displayFirendsRequests(){
    std::string input;

    const char * myChar = "0";
      PacketManager::send_friend_request(3, myChar);


    printw("******* Enter name of the user that you want to accept request (ENTER to validate or go back) *******\n");


    refresh();


    nocbreak();
    echo();


    int ch = getch();

    while ( ch != '\n' && ch != 27)
    {
        input.push_back( ch );
        ch = getch();
    }


    if(ch == '\n'){
      PacketManager::send_friend_request(5, input.c_str());

    }

    clear();

    cbreak();

}
