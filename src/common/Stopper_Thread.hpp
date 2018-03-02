#ifndef STOPPER_HPP
#define STOPPER_HPP

class Stopper_Thread{


	private:
		bool game_end = false;

	public:

		bool game_is_finish(){return game_end;}
		void game_finish(){game_end = true;}
};

#endif