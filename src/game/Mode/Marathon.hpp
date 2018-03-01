/*
Groupe 2 : 3V-CUBE

Marathon.hpp
*/

#ifndef __MARATHON__HPP__
#define __MARATHON__HPP__

#include "Mode.hpp"
extern bool g_is_finished;

class Marathon: public virtual Mode{

				
	public:
		
		Marathon(unsigned);
		virtual ~Marathon();	
		virtual void start(Grid *)override;
		
		virtual void init_game(bool is_player)override;
};

#endif
