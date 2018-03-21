#ifndef GUI_BOARD_HPP
#define GUI_BOARD_HPP

class Board_GUI;

#include <SFML/Graphics.hpp>
#include "../../game/Game_system/Grid.hpp"
#include "../GameManager.hpp"
#include "Constants.hpp"
#include <thread>

extern GameManager* game_manager;

class Board_GUI {
	private:
		sf::Font font;

		Grid* grid;
		sf::VertexArray vertices_first_grid;
		sf::VertexArray vertices_next_tetriminos_first;
		sf::VertexArray vertices_hold_tetriminos_first;
		sf::Text score_first;
		sf::Text lines_completed_first;
		sf::Text hold_first;
		sf::Text next_first;

		Grid* other_grid;
		sf::VertexArray vertices_second_grid;
		sf::VertexArray vertices_next_tetriminos_second;
		sf::VertexArray vertices_hold_tetriminos_second;
		sf::Text score_second;
		sf::Text lines_completed_second;
		sf::Text hold_second;
		sf::Text next_second;

		sf::RenderWindow window;
		bool vs;
	public:
		Board_GUI(bool, unsigned, unsigned, Grid*, Grid*);
		void update_display();
		void start();
		void handle_event(const sf::Event&);
		void fill_with_blocs();
		static sf::Color translate_to_color(unsigned);
		void color_bloc(sf::Vertex*, Grid*, unsigned, unsigned);

		void update_next_tetriminos_case();
		void update_hold_tetriminos_case();
		void update_score_and_lines();
		void draw_vertices();
		void draw_text();
};

#endif