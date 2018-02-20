/*
Groupe 2 : 3V-CUBE

Sprint.hpp
*/

#ifndef __SPRINT__HPP__
#define __SPRINT__HPP__

#include "Mode.hpp"


class Sprint: public virtual Mode{

				
	public:
		
		Sprint();
		virtual ~Sprint();

		void start() override;
		
};

#endif
