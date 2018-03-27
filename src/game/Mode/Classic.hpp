/*
Groupe 2 : 3V-CUBE

Classic.hpp
*/

#ifndef __CLASSIC__HPP__
#define __CLASSIC__HPP__

#include "Mode.hpp"


class Classic: public virtual Mode{

				
	public:
		
		Classic(long);
		virtual ~Classic();	
		virtual void start(Grid *,Grid*, Stopper_Thread*)override;		
		virtual void init_game(bool is_player)override;
		virtual bool is_winner()override;	


};

#endif
