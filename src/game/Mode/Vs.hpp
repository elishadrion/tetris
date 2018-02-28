/*
Groupe 2 : 3V-CUBE

Vs.hpp
*/

#ifndef __Vs__HPP__
#define __Vs__HPP__

#include "Mode.hpp"
extern bool g_is_finished;

class Vs: public virtual Mode {
	bool _is_player;			
	public:
		
		Vs(unsigned);
		virtual ~Vs();
		virtual void start(Grid *)override;
		
		virtual void init_game(bool is_player)override;

		
		
};

#endif
