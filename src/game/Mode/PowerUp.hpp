/*
Groupe 2 : 3V-CUBE

Vs.hpp
*/

#ifndef __POWERUP__HPP__
#define __POWERUP__HPP__
class PowerUp;
#include "Mode.hpp"


class PowerUp: public virtual Mode {
			
	public:
		
		PowerUp(unsigned);
		virtual ~PowerUp();
		virtual void start(Grid *,Grid*, Stopper_Thread*)override;		
		virtual void init_game(bool is_player)override;
		virtual bool is_winner()override;		
		
};

#endif
