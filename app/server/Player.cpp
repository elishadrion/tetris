#include "include/json.hpp"
#include "Player.hpp"

using namespace std;

//player's constructor
Player::Player() {
   
   //
   signUp();
   _victory = 0;
   _defeat = 0;
   //
}

//Saves player's data in a json file
void Player::save() const {

        ifstream fichierJson("server/assets/Players.json");  //Opening the Players.json file

        if(fichierJson) //Testing if everything went allright
        {
        std::string ligne; 

            while(getline(fichierJson, ligne)) //Reading all the file and stocking it into a string variable
            {
            std::cout << ligne << std::endl; //
            //suite TBD ! 
            }
        }

        else
        {
        std::cout << "ERROR: Impossible to open the file." << std::endl;
        }  
    
}

//Sets the name and the password of the player (setter)
void Player::signUp() {
    cout << "What's your name? ";
    cin >> _username;
    
    cout << "What's your password? ";
    cin >> _pass;

}

//Getters
string Player::getUsername() const {return _username;}

int Player::getVictories() const {return _victory;}

int Player::getDefeats() const {return _defeat;}
