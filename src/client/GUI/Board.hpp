#ifndef GUI_BOARD_HPP
#define GUI_BOARD_HPP

class Board;

#include <SFML/Graphics.hpp>
#include "../../game/Game_system/Grid.hpp"
#include "../GameManager.hpp"
#include "Constants.hpp"
#include <thread>

extern GameManager* game_manager;

class Board {
	private:
		sf::Font font;

		Grid* grid;
		sf::VertexArray vertices_first_grid;
		sf::Text score_first;
		sf::Text lines_completed_first;

		Grid* other_grid;
		sf::VertexArray vertices_second_grid;
		sf::Text score_second;
		sf::Text lines_completed_second;

		sf::RenderWindow window;
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