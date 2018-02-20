/*
Groupe 2 : 3V-CUBE

Marathon.hpp
*/

#ifndef __MARATHON__HPP__
#define __MARATHON__HPP__

#include "Mode.hpp"


class Marathon: public virtual Mode{

				
	public:
		
		Marathon();
		virtual ~Marathon();	

		void start() override;
		

};

#endif
