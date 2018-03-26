#include "../dependencies/CSVparser/CSVparser.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "SettingKeys.hpp"
#include <ncurses.h>
#include "../common/WizardLogger.hpp"

SettingKeys::SettingKeys(){
  // get all keys from csv and store as class variables
  try{
        const csv::Parser file = csv::Parser("./settings/keys_settings.csv"); // read only
        int lineNumber = file.rowCount();

        for (int i = 0; i < lineNumber; i++) {
          std::string keyValue = file[i]["key"];
          std::string keyNumber = file[i]["key_id"];

          if (keyValue == "rotateRigth"){
            C_rotateRigth = keyNumber;
          }
          else if (keyValue == "rotateLeft"){
            C_rotateLeft = keyNumber;
          }
          else if (keyValue == "accelerate"){
            C_accelerate = keyNumber;
          }
          else if (keyValue == "moveRigth"){
            C_moveRigth = keyNumber;
          }
          else if (keyValue == "moveLeft"){
            C_moveLeft = keyNumber;
          }
          else if (keyValue == "hardDrop"){
            C_hardDrop = keyNumber;
          }
          else if (keyValue == "hold"){
            C_hold = keyNumber;
          }
        }
    }
    catch (csv::Error &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void SettingKeys::dispalyCurrentKeys(){

        printw("---- Current Keys Setings ----\n");
        printw(" - rotateRigth : %c      - moveLeft : %c \n", static_cast<char>(std::stoi(C_rotateRigth)), static_cast<char>(std::stoi(C_moveLeft)));
        printw(" - rotateLeft : %c       - hardDrop : %c \n", static_cast<char>(std::stoi(C_rotateLeft)), static_cast<char>(std::stoi(C_hardDrop)));
        printw(" - accelerate : %c       - hold : %c \n", static_cast<char>(std::stoi(C_accelerate)), static_cast<char>(std::stoi(C_hold)));
        printw(" - moveRigth : %c  \n \n", static_cast<char>(std::stoi(C_moveRigth)));

}


void SettingKeys::RotateRigth(std::string keyID){
  C_rotateRigth = keyID;
}

void SettingKeys::RotateLeft(std::string keyID){
  C_rotateLeft = keyID;
}

void SettingKeys::accelerate(std::string keyID){
  C_accelerate = keyID;
}

void SettingKeys::moveRigth(std::string keyID){
  C_moveRigth = keyID;
}

void SettingKeys::moveLeft(std::string keyID){
  C_moveLeft = keyID;
}

void SettingKeys::hardDrop(std::string keyID){
  C_hardDrop = keyID;
}

void SettingKeys::hold(std::string keyID){
  C_hold = keyID;
}

void SettingKeys::saveSettings(){
  // save in csv file new settings

  WizardLogger::info("fichier de settings modifié");

  std::ofstream ofs;

  ofs.open("./settings/keys_settings.csv", std::ofstream::out | std::ofstream::trunc);
  ofs<<"key,key_id\n";
  ofs<<"rotateRigth,"<<C_rotateRigth<<"\n";
  ofs<<"rotateLeft,"<<C_rotateLeft<<"\n";
  ofs<<"accelerate,"<<C_accelerate<<"\n";
  ofs<<"moveRigth,"<<C_moveRigth<<"\n";
  ofs<<"moveLeft,"<<C_moveLeft<<"\n";
  ofs<<"hardDrop,"<<C_hardDrop<<"\n";
  ofs<<"hold,"<<C_hold<<"\n";
  ofs.close();
}
