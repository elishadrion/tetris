#ifndef GUI_BOARD_HPP
#define GUI_BOARD_HPP

#include <SFML/Graphics.hpp>
#include "Game_system/Grid.hpp"
#include "Constants.hpp"
#include <thread>

class Board {
	private:
		sf::VertexArray vertices;
		sf::RenderWindow window;
		Grid* grid;
	public:
		Board(unsigned, unsigned, Grid*);
		void update_main_game_solo_GUI();
		bool within_limits(unsigned, unsigned);
		void move_bloc_up(sf::Vertex*);
		void move_bloc_down(sf::Vertex*);
		void move_bloc_right(sf::Vertex*);
		void move_bloc_left(sf::Vertex*);
		void start();
		void handle_event(const sf::Event&);
		void fill_with_blocs();
		void color_bloc(sf::Vertex*, unsigned);
};

#endif