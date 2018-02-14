#include <ncurses.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include "SettingKeys.hpp"
#include "SettingsMenu.hpp"


void SettingMenu::showOption(){
  printw("What you want to do ?\n");
  printw("0 : Quit\n");
  printw("1 : Setings keys\n");
}


int SettingMenu::setNewKey(){
  clear();
  printw("Enter new key value:\n");
  int res;
  res = getch();
  return res;
}


void SettingMenu::KeysOption(){
  // key editor settings menu
  std::string keyToSet;

  SettingKeys* settingKeys = new SettingKeys();

  while (1) {
    printw("Which key you want to set ? (Enter 0 to finish and save)\n");
    printw("1 : rotate Rigth\n");
    printw("2 : rotate Left\n");
    printw("3 : accelerate\n");
    printw("4 : move Rigth\n");
    printw("5 : move Left\n");
    printw("6 : hard Drop\n");
    printw("7 : hold\n");

    refresh();

    while (1) {
      keyToSet = getch();
      int res;

      if(keyToSet == "0"){
        break;
      }
      else if(keyToSet == "1"){
        res = setNewKey();
        settingKeys->RotateRigth(std::to_string(res));
        clear();
        break;
      }
      else if(keyToSet == "2"){
        res = setNewKey();
        settingKeys->RotateLeft(std::to_string(res));
        clear();
        break;
      }
      else if(keyToSet == "3"){
        res = setNewKey();
        settingKeys->accelerate(std::to_string(res));
        clear();
        break;
      }
      else if(keyToSet == "4"){
        res = setNewKey();
        settingKeys->moveRigth(std::to_string(res));
        clear();
        break;
      }
      else if(keyToSet == "5"){
        res = setNewKey();
        settingKeys->moveLeft(std::to_string(res));
        clear();
        break;
      }
      else if(keyToSet == "6"){
        res = setNewKey();
        settingKeys->hardDrop(std::to_string(res));
        clear();
        break;
      }
      else if(keyToSet == "7"){
        res = setNewKey();
        settingKeys->hold(std::to_string(res));
        clear();
        break;
      }
      else{
        clear();
        break;
      }
    }


    if(keyToSet == "0"){
      settingKeys->saveSettings();
      clear();
      break;
    }
  }
}



SettingMenu::SettingMenu() {
    // main menu windows
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
          KeysOption();
          break;
        }
        else{
          clear();
          break;
        }
      }
      if(ch == "0"){
        break;
      }
    }
    endwin();
}
