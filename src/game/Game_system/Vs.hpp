/*
Groupe 2 : 3V-CUBE

Vs.hpp
*/

#ifndef __Vs__HPP__
#define __Vs__HPP__

#include "Mode.hpp"


class Vs: public virtual Mode{

	private:

		Grid * other_grid;

				
	public:
		
		Vs();
		virtual ~Vs();

		void start() override;
		
};

#endif
