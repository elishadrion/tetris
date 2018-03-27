/*
Groupe 2 : 3V-CUBE

Sprint.hpp
*/

#ifndef __SPRINT__HPP__
#define __SPRINT__HPP__

#include "Mode.hpp"


class Sprint: public virtual Mode{

				
	public:
		
		Sprint(long);
		virtual ~Sprint();

		virtual void start(Grid *,Grid*, Stopper_Thread*)override;		
		virtual void init_game(bool is_player)override;
		virtual bool is_winner()override;	
		
};

#endif
