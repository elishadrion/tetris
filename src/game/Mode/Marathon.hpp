/*
Groupe 2 : 3V-CUBE

Marathon.hpp
*/

#ifndef __MARATHON__HPP__
#define __MARATHON__HPP__

#include "Mode.hpp"


class Marathon: public virtual Mode{

				
	public:
		
		Marathon(unsigned);
		virtual ~Marathon();	
		virtual void start(Grid *,Grid*, Stopper_Thread*)override;
		
		virtual void init_game(bool is_player)override;
};

#endif
