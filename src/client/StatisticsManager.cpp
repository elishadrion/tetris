#include "StatisticsManager.hpp"



void StatisticsManager::showOption(){
  printw("******* Statistics manager *******\n");
  printw("0 : back to menu\n");
  printw("1 : Display my statistics\n");
	printw("2 : Display satistics by game mode\n");
  printw("3 : Display all users satistics\n");
}


void StatisticsManager::displayStatisticsMenu(){
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
				displayMyStatistics();
				break;
			}
			else if(ch == "2"){
				clear();
				displayAllStatistics();
				break;
			}
      else if(ch == "3"){
				clear();
				displayAllUsersStatistics();
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


void StatisticsManager::displayMyStatistics(){
		int ch;

		while (1) {
			printw("******* My Statistics (ESC to got back)*******\n");

      PacketManager::send_stat_request(0);

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


void StatisticsManager::printAllStats(char *allStats){

  printw(allStats);
  refresh();


}


void StatisticsManager::displayAllStatistics(){
  int ch;

  while (1) {
    printw("******* Global Statistics (ESC to got back)*******\n");

    PacketManager::send_stat_request(1);

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



void StatisticsManager::displayAllUsersStatistics(){
  int ch;

  while (1) {
    printw("******* All users Statistics (ESC to got back)*******\n");

    PacketManager::send_stat_request(2);

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
