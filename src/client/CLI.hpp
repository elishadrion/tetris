#ifndef CLI_HPP
#define CLI_HPP

#include "WizardDisplay.hpp"

class CLI: public virtual WizardDisplay{



   	public:


   		CLI();    
	    virtual ~CLI();

	    virtual void login() override;
	    virtual void register_user()override;
	    virtual void menu()override; 
	    virtual void main_menu()override;	
	    virtual void play(int)override;
	    virtual void end_game(info_game) override;
	    virtual void choice_game()override;
	    virtual void chat()override;
	    virtual void wait_player()override;
	   



};

#endif