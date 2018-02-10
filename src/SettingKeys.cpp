#include "dependencies/CSVparser/CSVparser.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "SettingKeys.hpp"

SettingKeys::SettingKeys(){
  // get all keys from csv and store as class variables
  try{
        const csv::Parser file = csv::Parser("settings/keys_settings.csv"); // read only
        int lineNumber = file.rowCount();

        for (int i = 0; i < lineNumber; i++) {
          std::string keyValue = file[i]["key_id"];

          if (keyValue == "rotateRigth"){
            C_rotateRigth = keyValue;
          }
          else if (keyValue == "rotateLeft"){
            C_rotateLeft = keyValue;
          }
          else if (keyValue == "accelerate"){
            C_accelerate = keyValue;
          }
          else if (keyValue == "moveRigth"){
            C_moveRigth = keyValue;
          }
          else if (keyValue == "moveLeft"){
            C_moveLeft = keyValue;
          }
          else if (keyValue == "hardDrop"){
            C_hardDrop = keyValue;
          }
          else if (keyValue == "hold"){
            C_hold = keyValue;
          }
        }
    }
    catch (csv::Error &e)
    {
        std::cerr << e.what() << std::endl;
    }
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
  std::ofstream ofs;

  ofs.open("settings/keys_settings.csv", std::ofstream::out | std::ofstream::trunc);
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
