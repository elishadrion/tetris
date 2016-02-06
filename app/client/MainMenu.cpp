
#include "MainMenu.hpp"
#include <iostream>


MainMenu::MainMenu() {

    // menu[0] = new PlayMenu();
    // ect

}

void MainMenu::choseButton(int number) {
    menu[number]->print();
}



void MainMenu::print() {

    int choise;

    std::cout << "What would you like to do ?" << std::endl;
    std::cout << "1. Play" << std::endl;
    std::cout << "2. Collection" << std::endl;
    std::cout << "3. Friends"  << std::endl;
    std::cout << "4. Classement"  << std::endl;
    std::cout << "5. Exit"  << std::endl;

    std::cin >> choise;

    choseButton(choise);

}

