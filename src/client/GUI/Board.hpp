#ifndef GUI_BOARD_HPP
#define GUI_BOARD_HPP

class Board;

#include <SFML/Graphics.hpp>
#include "../../game/Game_system/Grid.hpp"
//#include "../GameManager.hpp"
#include "Constants.hpp"
#include <thread>

class Board {
	private:
		sf::VertexArray vertices_first_grid;
		sf::VertexArray vertices_second_grid;
		sf::RenderWindow window;
		Grid* grid;
		Grid* other_grid;
		bool vs;
	public:
		Board(bool, unsigned, unsigned, Grid*, Grid*);
		void update_display();
		void start();
		void handle_event(const sf::Event&);
		void fill_with_blocs();
		static sf::Color translate_to_color(unsigned);
		void color_bloc(sf::Vertex*, Grid*, unsigned, unsigned);
};

#endif