#include "Board.hpp"


Board::Board(unsigned wwidth, unsigned wheight, Grid* _grid): grid(_grid) {
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(width*height*4);
	fill_with_blocs();
	window.create(sf::VideoMode(wwidth, wheight), "Fenêtre");
	window.setFramerateLimit(60);
}

void Board::start() {
	usleep(100);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			handle_event(event);
		}
		update_main_game_solo_GUI();
	}
}

void Board::update_main_game_solo_GUI() {
	for (unsigned i = 0; i < width; i++) {
		for (unsigned j = 0; j < height; j++) {
			sf::Vertex* bloc = &vertices[(i + j*width)*4];
			if (grid->get_tetriminos()->has_block(j,i)) {
				//std::cout << grid->get_color_of_tetriminos() << std::endl;
				color_bloc(bloc, grid->get_color_of_tetriminos());
			}
			else if (grid->is_empty(j,i) == 0) {
				color_bloc(bloc, grid->get_color_of_block(j,i));
			}
			else {
				color_bloc(bloc, 8);
			}
		}
	}
		window.clear();
		window.draw(vertices);
		window.display();
}

bool Board::within_limits(unsigned x, unsigned y) {
	bool is_within = true;
	if (x < limits_x[0] or x > limits_x[1])
		is_within = false;
	if (y < limits_y[0] or y > limits_y[1])
		is_within = false;
	return is_within;
}

void Board::move_bloc_up(sf::Vertex* bloc) {
	bool is_within = within_limits(bloc[0].position.x, bloc[0].position.y-20);
	if (is_within) {
		for (unsigned i = 0; i < 4; i++) {
			bloc[i].position.y -= 20;
		}
	}
}

void Board::move_bloc_down(sf::Vertex* bloc) {
	bool is_within = within_limits(bloc[0].position.x, bloc[0].position.y+20);
	if (is_within) {
		for (unsigned i = 0; i < 4; i++) {
			bloc[i].position.y += 20;
		}
	}
}

void Board::move_bloc_right(sf::Vertex* bloc) {
	bool is_within = within_limits(bloc[0].position.x+20, bloc[0].position.y);
	if (is_within) {
		for (unsigned i = 0; i < 4; i++) {
			bloc[i].position.x += 20;
		}
	}
}

void Board::move_bloc_left(sf::Vertex* bloc) {
	bool is_within = within_limits(bloc[0].position.x-20, bloc[0].position.y);
	if (is_within) {
		for (unsigned i = 0; i < 4; i++) {
			bloc[i].position.x -= 20;
		}
	}
}

void Board::fill_with_blocs() {
	unsigned x = limits_x[0];
	unsigned y = limits_y[0];
	for (unsigned i = 0; i < width; i++) {
		for (unsigned j = 0; j < height; j++) {
			//bloc courant
			sf::Vertex* bloc = &vertices[(i + j*width)*4];
			bloc[0].position = sf::Vector2f(x+(i*BLOC_SIZE), y+(j*BLOC_SIZE));
			//1 coin inférieure gauche
			bloc[1].position = sf::Vector2f(x+((i+1)*BLOC_SIZE), y+(j*BLOC_SIZE));
			//2 coin inférieur droit
			bloc[2].position = sf::Vector2f(x+((i+1)*BLOC_SIZE), y+((j+1)*BLOC_SIZE));
			//3 coin supérieur droit
			bloc[3].position = sf::Vector2f(x+(i*BLOC_SIZE), y+((j+1)*BLOC_SIZE));
		}
	}
}

void Board::color_bloc(sf::Vertex* bloc, unsigned color_num) {
	sf::Color color = translate_to_color(color_num);
	for (unsigned i = 0; i < 4; i++)
		bloc[i].color = color;
}


void Board::handle_event(const sf::Event& event) {

	switch(event.type) {

		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:

			switch(event.key.code) {
				case sf::Keyboard::Down:
					grid->set_acceleration_quick();
					break;
				case sf::Keyboard::Right:
					grid->current_tetriminos_move_right();
					break;
				case sf::Keyboard::Left:
					grid->current_tetriminos_move_left();
					break;
				case sf::Keyboard::Q:
					grid->current_tetriminos_turn_left();
					break;
				case sf::Keyboard::D:
					grid->current_tetriminos_turn_right();
					break;
				case sf::Keyboard::H:
					grid->set_current_tetriminos_hold();
					break;
				case sf::Keyboard::S:
					grid->current_tetriminos_hard_drop();
					break;
			}
			break;
	}
}

sf::Color Board::translate_to_color(unsigned color_num) {
	sf::Color color;
	switch (color_num) {
		case 1:
			color = sf::Color::White;
			break;
		case 2:
			color = sf::Color::Red;
			break;
		case 3:
			color = sf::Color::Green;
			break;
		case 4:
			color = sf::Color::Blue;
			break;
		case 5:
			color = sf::Color::Yellow;
			break;
		case 6:
			color = sf::Color::Magenta;
			break;
		case 7:
			color = sf::Color::Cyan;
			break;
		case 8:
			color = sf::Color::Black;
			break;
	}
	return color;
}