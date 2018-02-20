/*
Groupe 2 : 3V-CUBE

Classic.hpp
*/

#ifndef __CLASSIC__HPP__
#define __CLASSIC__HPP__

#include "Mode.hpp"


class Classic: public virtual Mode{

				
	public:
		
		Classic();
		virtual ~Classic();	

		void start() override;
		

};

#endif
