
#include <string>
#include "Database.hpp"
#include <stdio.h>
#include <cstring>




Database::Database(){
  char *ERRORmsg = NULL;
	int result = 0;
  result = sqlite3_open_v2("./database/TetrisPlayerDatabase.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

  if(result) {
      printf("Error cannot open database : %s\n", sqlite3_errmsg(db));
   } else {
      printf("Database opened\n");
   }
}

bool Database::checkNameExist(std::string name){
  int codeRetour = 0;
    sqlite3_stmt *request;
    //check if name in database

    char *sqlSelection = "SELECT name FROM users WHERE name = ? ";
    int id = 0;
    unsigned char *nameDB = NULL;

  codeRetour = sqlite3_prepare_v2(db, sqlSelection, strlen(sqlSelection), &request, NULL);

  if (!codeRetour){

    sqlite3_bind_text(request, 1, name.c_str() , name.size(), 0);

    while (codeRetour == SQLITE_OK || codeRetour == SQLITE_ROW){

      codeRetour = sqlite3_step(request);

      if (codeRetour == SQLITE_OK || codeRetour == SQLITE_ROW ){

        id = sqlite3_column_int(request, 0);
        nameDB = (unsigned char *)sqlite3_column_text(request, 0);

        if(std::string(reinterpret_cast<char*>(nameDB)) == name){
          printf("User exist  %s\n", nameDB);
          return true;
        }
      }
    }
    sqlite3_finalize(request);
  }

  printf("User not exist %s\n", nameDB);
  return false;
}


void Database::initialiseDatabase(){
  char *ERRORmsg = NULL;
	int result = 0;

  sqlite3_close(db);

  // delete current database
  if(remove("./database/TetrisPlayerDatabase.db") != 0 ){
      printf("Error deleting TetrisPlayerDatabase.db\n");
  }
  else{
    printf("TetrisPlayerDatabase.db successfully deleted\n");
  }

  // create new db
  result = sqlite3_open_v2("./database/TetrisPlayerDatabase.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

  if(result) {
      printf("Error creating database : %s\n", sqlite3_errmsg(db));
   }
   else {
      printf("Database created\n");
   }

  // create new main users table
  //SQLite AUTOINCREMENT instead of AUTO_INCREMENT
  result = sqlite3_exec(db, "CREATE TABLE users( id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(20), password VARCHAR(64), score INTEGER DEFAULT 0, time INTEGER DEFAULT 0)", NULL, 0, &ERRORmsg);
  if(result && ERRORmsg != NULL) {
    printf("Error creating main users Table : %s\n", sqlite3_errmsg(db));
  }
  else {
    printf("Main users table created\n");
  }

  // create new global Statistic table
  result = sqlite3_exec(db, "CREATE TABLE globalStatistic( id_mode INTEGER PRIMARY KEY AUTOINCREMENT, victory INTEGER DEFAULT 0, defeat INTEGER DEFAULT 0, score INTEGER DEFAULT 0, time INTEGER DEFAULT 0, complete_line INTEGER DEFAULT 0)", NULL, 0, &ERRORmsg);
  if(result && ERRORmsg != NULL) {
    printf("Error creating Table : %s\n", sqlite3_errmsg(db));
  }
  else {
    printf("Table created\n");
  }

  // Insert 4 game modes
  result = sqlite3_exec(db, "INSERT INTO globalStatistic(victory, defeat) VALUES (0,0),(0,0),(0,0),(0,0)", NULL, 0, &ERRORmsg);
  if(result && ERRORmsg != NULL) {
    printf("Error creating Table : %s\n", sqlite3_errmsg(db));
  }
  else {
    printf("Table created\n");
  }
}


bool Database::checkNamePassword(std::string name, std::string password){
	int codeRetour = 0;
	sqlite3_stmt *requete;
	//Requête SQL qui sera utilisée plus tard dans le programme qui permet de récupérer toutes les informations contenues dans la table contact
	char *sqlSelection = "SELECT * FROM users";
	int id = 0;
	unsigned char *nameDB = NULL;
	unsigned char *passDB = NULL;

  codeRetour = sqlite3_prepare_v2(db, sqlSelection, strlen(sqlSelection), &requete, NULL);

  if (!codeRetour){

    while (codeRetour == SQLITE_OK || codeRetour == SQLITE_ROW){

      codeRetour = sqlite3_step(requete);

      if (codeRetour == SQLITE_OK || codeRetour == SQLITE_ROW ){

        id = sqlite3_column_int(requete, 0);
        nameDB = (unsigned char *)sqlite3_column_text(requete, 1);

        passDB = (unsigned char *)sqlite3_column_text(requete, 2);

        if(std::string(reinterpret_cast<char*>(nameDB)) == name && std::string(reinterpret_cast<char*>(passDB)) == password){
          printf("Login and password correct for  %s\n", nameDB);
          return true;
        }
      }
    }
    sqlite3_finalize(requete);
  }

  printf("Login and password NOT correct for  %s\n", nameDB);
  return false;
}




std::string Database::getUserNameFriends(std::string name){
  int resVal = 0;
  sqlite3_stmt *request;
  int id2 = 0;
  unsigned char *friendName = NULL;

  std::string req = "SELECT * FROM "+name;
  std::string res = "";

  resVal = sqlite3_prepare_v2(db, req.c_str(), req.size(), &request, NULL);

  if (!resVal){

    while (resVal == SQLITE_OK || resVal == SQLITE_ROW){

            resVal = sqlite3_step(request);

      if (resVal == SQLITE_OK || resVal == SQLITE_ROW ){

                id2 = sqlite3_column_int(request, 0);

                friendName = (unsigned char *)sqlite3_column_text(request, 1);
        printf("Recuperation de l'ami numéro %d : \n ami : %s \n", id2, friendName);
        res = res+"\t"+std::string(reinterpret_cast<char*>(friendName));

      }
    }
    sqlite3_finalize(request);
  }

  return res;
}


std::string Database::getAllUser(){
  int resVal = 0;
  sqlite3_stmt *request;
  int id2 = 0;
  unsigned char *name = NULL;

  std::string req = "SELECT * FROM users";
  std::string res = "";

  resVal = sqlite3_prepare_v2(db, req.c_str(), req.size(), &request, NULL);

  if (!resVal){

    while (resVal == SQLITE_OK || resVal == SQLITE_ROW){

            resVal = sqlite3_step(request);

      if (resVal == SQLITE_OK || resVal == SQLITE_ROW ){

                id2 = sqlite3_column_int(request, 0);

                name = (unsigned char *)sqlite3_column_text(request, 1);
        printf("Recuperation de l'ami numéro %d : \n ami : %s \n", id2, name);
        res = res+"\t"+std::string(reinterpret_cast<char*>(name));

      }
    }
    sqlite3_finalize(request);
  }

  return res;
}



std::string Database::getGlobalStatistics(){
  int resVal = 0;
  sqlite3_stmt *request;
  int id2 = 0;
  unsigned char *victory = NULL;
  unsigned char *defeat = NULL;
  unsigned char *score = NULL;
  unsigned char *time = NULL;
  unsigned char *complete_line = NULL;

  std::string req = "SELECT * FROM globalStatistic";
  std::string res = "";

  resVal = sqlite3_prepare_v2(db, req.c_str(), req.size(), &request, NULL);

  if (!resVal){

    while (resVal == SQLITE_OK || resVal == SQLITE_ROW){

            resVal = sqlite3_step(request);

      if (resVal == SQLITE_OK || resVal == SQLITE_ROW ){

                id2 = sqlite3_column_int(request, 0);

                victory = (unsigned char *)sqlite3_column_text(request, 1);
                defeat = (unsigned char *)sqlite3_column_text(request, 2);

        printf("Recuperation de l'ami numéro %d : \t ami : %s ami : %s\n", id2, victory, defeat);
        res = res+std::string(reinterpret_cast<char*>(victory))+"\t"+std::string(reinterpret_cast<char*>(defeat))+"\n";

      }
    }
    sqlite3_finalize(request);
  }

  return res;
}


std::string Database::getUserNameStatistics(std::string name){
  int resVal = 0;
  sqlite3_stmt *request;
  int id2 = 0;
  unsigned char *victory = NULL;
  unsigned char *defeat = NULL;

  std::string req = "SELECT score, time FROM users WHERE name = ?";
  std::string res = "";

  resVal = sqlite3_prepare_v2(db, req.c_str(), req.size(), &request, NULL);

  if (!resVal){

    sqlite3_bind_text(request, 1, name.c_str() , name.size(), 0);

    while (resVal == SQLITE_OK || resVal == SQLITE_ROW){

            resVal = sqlite3_step(request);

      if (resVal == SQLITE_OK || resVal == SQLITE_ROW ){

                id2 = sqlite3_column_int(request, 0);

                victory = (unsigned char *)sqlite3_column_text(request, 0);
                defeat = (unsigned char *)sqlite3_column_text(request, 1);

        printf("Recuperation de l'ami numéro %d : \t ami : %s ami : %s\n", id2, victory, defeat);
        res = res+std::string(reinterpret_cast<char*>(victory))+"\t"+std::string(reinterpret_cast<char*>(defeat))+"\n";

      }
    }
    sqlite3_finalize(request);
  }

  return res;
}


void Database::registerUser(std::string name, std::string password){
  char *ERRORmsg = NULL;
	int result = 0;
  sqlite3_stmt *stmt;

  char *reg = "INSERT INTO users(name, password) VALUES (?, ?)";

  result = sqlite3_prepare_v2(db, reg, strlen(reg), &stmt, NULL);

	if (!result){
    // bind name and password
    sqlite3_bind_text(stmt, 1, name.c_str() , name.size(), 0);
    sqlite3_bind_text(stmt, 2, password.c_str() , password.size(), 0);

    // execute
    result = sqlite3_step(stmt);
    if(result) {
      printf("User added : %s  \n", name.c_str());
    }
    else {
      printf("User not added : %s  \n", name.c_str());
    }
    sqlite3_finalize(stmt);
	}

  // create table for user friends
  std::string req = "CREATE TABLE "+name+"(id INTEGER PRIMARY KEY AUTOINCREMENT, friends VARCHAR(100), status INTEGER DEFAULT 0)";
  result = sqlite3_exec(db, req.c_str(), NULL, 0, &ERRORmsg);
  if(result && ERRORmsg != NULL) {
    printf("Error creating friend Table : %s\n", sqlite3_errmsg(db));
  }
  else {
    printf("Friend table created \n");
  }

}




void Database::updateUserNameScore(std::string name, int victoryAdd, int lostAdd){
  char *ERRORmsg = NULL;
	int result = 0;
  sqlite3_stmt *stmt;

  char *reg = "UPDATE users SET score = score + ?, time = time + ? WHERE name = ?";

  result = sqlite3_prepare_v2(db, reg, strlen(reg), &stmt, NULL);

	if (!result){
    // bind victoryAdd and lostAdd
    sqlite3_bind_int(stmt, 1, victoryAdd );
    sqlite3_bind_int(stmt, 2, lostAdd );
    sqlite3_bind_text(stmt, 3, name.c_str() , name.size(), 0);


    // execute
    result = sqlite3_step(stmt);
    if(result) {
      printf("User update stats : %s  \n", name.c_str());
    }
    else {
      printf("User update stats : %s  \n", name.c_str());
    }
    sqlite3_finalize(stmt);
	}
}


void Database::updateGlobalStatistic(int gameMode, int victoryAdd, int lostAdd, int score, int time, int completeLine){
  char *ERRORmsg = NULL;
	int result = 0;
  sqlite3_stmt *stmt;
  std::string req;

  if(gameMode==0){
    req = "UPDATE globalStatistic SET victory = victory + ?, defeat = defeat + ?, defeat = score + ?, defeat = time + ?, defeat = complete_line + ? WHERE id_mode = 1";
  }
  else if(gameMode==1){
    req = "UPDATE globalStatistic SET victory = victory + ?, defeat = defeat + ?, defeat = score + ?, defeat = time + ?, defeat = complete_line + ? WHERE id_mode = 2";
  }
  else if(gameMode==2){
    req = "UPDATE globalStatistic SET victory = victory + ?, defeat = defeat + ?, defeat = score + ?, defeat = time + ?, defeat = complete_line + ? WHERE id_mode = 3";
  }
  else if(gameMode==3){
    req = "UPDATE globalStatistic SET victory = victory + ?, defeat = defeat + ?, defeat = score + ?, defeat = time + ?, defeat = complete_line + ?WHERE id_mode = 4";
  }
  else{
    printf("Game mode Error\n");
  }


  result = sqlite3_prepare_v2(db, req.c_str(), req.size(), &stmt, NULL);

	if (!result){
    // bind victoryAdd and lostAdd
    sqlite3_bind_int(stmt, 1, victoryAdd );
    sqlite3_bind_int(stmt, 2, lostAdd );
    sqlite3_bind_int(stmt, 3, score );
    sqlite3_bind_int(stmt, 4, time );
    sqlite3_bind_int(stmt, 5, completeLine );



    // execute
    result = sqlite3_step(stmt);
    if(result) {
      printf("global update stats : %i  \n", gameMode);
    }
    else {
      printf("global update stats : %i  \n", gameMode);
    }
    sqlite3_finalize(stmt);
	}

}


void Database::sendFriendRequest(std::string name, std::string FriendName){
  char *ERRORmsg = NULL;
	int result = 0;
  sqlite3_stmt *stmt;
  std::string req = "INSERT INTO "+name+"(friends, status) VALUES(?, ?)";
  result = sqlite3_prepare_v2(db, req.c_str(), req.size(), &stmt, NULL);
	if (!result){
    // bind friend name
    sqlite3_bind_text(stmt, 1, FriendName.c_str() , FriendName.size(), 0);
    sqlite3_bind_int(stmt, 2, 0);


    // execute
    result = sqlite3_step(stmt);

    if(result) {
      printf("Friend added : %s  %i\n", FriendName.c_str(), result);
    }
    else {
      printf("Friend not added : %s  %i\n", FriendName.c_str(), result);
    }
    sqlite3_finalize(stmt);
	}
}



void Database::confirmFriendRequest(std::string name, std::string FriendName){
  char *ERRORmsg = NULL;
	int result = 0;
  sqlite3_stmt *stmt;
  std::string req = "UPDATE "+name+"SET status = 1 WHERE friends = ? ";
  result = sqlite3_prepare_v2(db, req.c_str(), req.size(), &stmt, NULL);
	if (!result){
    // bind friend name
    sqlite3_bind_text(stmt, 1, FriendName.c_str() , FriendName.size(), 0);

    // execute
    result = sqlite3_step(stmt);

    if(result) {
      printf("Friend added : %s  %i\n", FriendName.c_str(), result);
    }
    else {
      printf("Friend not added : %s  %i\n", FriendName.c_str(), result);
    }
    sqlite3_finalize(stmt);
	}
}


  void Database::deleteFriendFromUserName(std::string name, std::string FriendName){
    char *ERRORmsg = NULL;
  	int result = 0;
    sqlite3_stmt *stmt;
    std::string req = "DELETE FROM "+name+" WHERE friends = ?";

    result = sqlite3_prepare_v2(db, req.c_str(), req.size(), &stmt, NULL);
  	if (!result){
      // bind friend name
      sqlite3_bind_text(stmt, 1, FriendName.c_str() , FriendName.size(), 0);


      // execute
      result = sqlite3_step(stmt);

      if(result) {
        printf("Friend deleted : %s  %i\n", FriendName.c_str(), result);
      }
      else {
        printf("Friend not deleted : %s  %i\n", FriendName.c_str(), result);
      }
      sqlite3_finalize(stmt);
  	}
  }



void Database::prettyPrint(){
	int codeRetour = 0;
	sqlite3_stmt *requete;
	//Requête SQL qui sera utilisée plus tard dans le programme qui permet de récupérer toutes les informations contenues dans la table contact
	char *sqlSelection = "SELECT * FROM users";
	int id = 0;
	unsigned char *noms = NULL;
	unsigned char *prenoms = NULL;
  std::string res;
  codeRetour = sqlite3_prepare_v2(db, sqlSelection, strlen(sqlSelection), &requete, NULL);

  if (!codeRetour){



    while (codeRetour == SQLITE_OK || codeRetour == SQLITE_ROW){

            codeRetour = sqlite3_step(requete);

      if (codeRetour == SQLITE_OK || codeRetour == SQLITE_ROW ){

                id = sqlite3_column_int(requete, 0);
                noms = (unsigned char *)sqlite3_column_text(requete, 1);
        res = std::string(reinterpret_cast<char*>(noms));

        //on récupère la deuxième colonne (ici le texte prénoms)
        prenoms = (unsigned char *)sqlite3_column_text(requete, 2);



        printf("Recuperation du contact numero %d : \n Noms : %s \n Prenoms : %s \n", id, noms, prenoms);
        noms = (unsigned char *)sqlite3_column_text(requete, 3);
        //on récupère la deuxième colonne (ici le texte prénoms)
        prenoms = (unsigned char *)sqlite3_column_text(requete, 4);

        printf("Recuperation du contact numero %d : \n Noms : %s \n Prenoms : %s \n", id, noms, prenoms);

      }
          }
    sqlite3_finalize(requete);
  }



                int resVal = 0;
                sqlite3_stmt *request;
                int id2 = 0;

                std::string req = "SELECT * FROM "+res;

                resVal = sqlite3_prepare_v2(db, req.c_str(), req.size(), &request, NULL);

                if (!resVal){



                  while (resVal == SQLITE_OK || resVal == SQLITE_ROW){

                                        resVal = sqlite3_step(request);

                    if (resVal == SQLITE_OK || resVal == SQLITE_ROW ){

                                            id2 = sqlite3_column_int(request, 0);

                                            noms = (unsigned char *)sqlite3_column_text(request, 1);
                      printf("Recuperation de l'ami numéro %d : \n ami : %s \n", id2, noms);

                    }
                                      }
                  sqlite3_finalize(request);
                }


}


