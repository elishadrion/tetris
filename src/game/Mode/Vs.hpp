/*
Groupe 2 : 3V-CUBE

Vs.hpp
*/

#ifndef __Vs__HPP__
#define __Vs__HPP__
class Vs;
#include "Mode.hpp"


class Vs: public virtual Mode {
			
	public:
		
		Vs(unsigned);
		virtual ~Vs();
		
		virtual void start(Grid *,Grid*, Stopper_Thread*)override;		
		virtual void init_game(bool is_player)override;

		
		
};

#endif
