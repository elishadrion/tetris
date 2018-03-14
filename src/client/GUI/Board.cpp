#include "Board.hpp"


Board::Board(bool vs, unsigned wwidth, unsigned wheight, Grid* _grid, Grid* _other_grid): vs(vs), grid(_grid), other_grid(_other_grid) {
	vertices_first_grid.setPrimitiveType(sf::Quads);
	vertices_first_grid.resize(width*height*4);
	if (vs) {
		vertices_second_grid.setPrimitiveType(sf::Quads);
		vertices_second_grid.resize(width*height*4);
	}
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
		update_display();
	}
}

void Board::update_display() {
	for (unsigned i = 0; i < width; i++) {
		for (unsigned j = 0; j < height; j++) {
			sf::Vertex* bloc = &vertices_first_grid[(i + j*width)*4];
			color_bloc(bloc, grid, i, j);
			if (vs) {
				bloc = &vertices_second_grid[(i+j*width)*4];
				color_bloc(bloc, other_grid, i, j);
			}

		}
	}
	window.clear();
	window.draw(vertices_first_grid);
	if (vs)
		window.draw(vertices_second_grid);
	window.display();
}

void Board::fill_with_blocs() {
	unsigned x = limits_x[0];
	unsigned y = limits_y[0];
	for (unsigned i = 0; i < width; i++) {
		for (unsigned j = 0; j < height; j++) {
			//bloc courant
			sf::Vertex* bloc = &vertices_first_grid[(i + j*width)*4];
			//0 coin supérieur gauche
			bloc[0].position = sf::Vector2f(limits_x[0]+(i*BLOC_SIZE), limits_y[0]+(j*BLOC_SIZE));
			//1 coin inférieure gauche
			bloc[1].position = sf::Vector2f(limits_x[0]+((i+1)*BLOC_SIZE), limits_y[0]+(j*BLOC_SIZE));
			//2 coin inférieur droit
			bloc[2].position = sf::Vector2f(limits_x[0]+((i+1)*BLOC_SIZE), limits_y[0]+((j+1)*BLOC_SIZE));
			//3 coin supérieur droit
			bloc[3].position = sf::Vector2f(limits_x[0]+(i*BLOC_SIZE), limits_y[0]+((j+1)*BLOC_SIZE));
			if (vs) {
				bloc = &vertices_second_grid[(i + j*width)*4];
				bloc[0].position = sf::Vector2f(limits_x[1]+(i*BLOC_SIZE), limits_y[0]+(j*BLOC_SIZE));
				//1 coin inférieure gauche
				bloc[1].position = sf::Vector2f(limits_x[1]+((i+1)*BLOC_SIZE), limits_y[0]+(j*BLOC_SIZE));
				//2 coin inférieur droit
				bloc[2].position = sf::Vector2f(limits_x[1]+((i+1)*BLOC_SIZE), limits_y[0]+((j+1)*BLOC_SIZE));
				//3 coin supérieur droit
				bloc[3].position = sf::Vector2f(limits_x[1]+(i*BLOC_SIZE), limits_y[0]+((j+1)*BLOC_SIZE));
			}
		}
	}
}

void Board::color_bloc(sf::Vertex* bloc, Grid* grid, unsigned i, unsigned j) {
	unsigned color_num;
	if (grid->get_tetriminos()->has_block(j,i)) {
		//std::cout << grid->get_color_of_tetriminos() << std::endl;
		color_num = grid->get_color_of_tetriminos();
	}
	else if (grid->is_empty(j,i) == 0) {
		color_num = grid->get_color_of_block(j,i);
	}
	else {
		color_num = 8;
	}
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
					game_manager->move_drop();
					grid->set_acceleration_quick();
					break;

				case sf::Keyboard::Right:
					game_manager->move_right();
					grid->current_tetriminos_move_right();
					break;

				case sf::Keyboard::Left:
					game_manager->move_left();
					grid->current_tetriminos_move_left();
					break;

				case sf::Keyboard::Q:
					game_manager->move_turn_left();
					grid->current_tetriminos_turn_left();
					break;

				case sf::Keyboard::D:
					game_manager->move_turn_right();
					grid->current_tetriminos_turn_right();
					break;

				case sf::Keyboard::H:
					game_manager->move_hold();
					grid->set_current_tetriminos_hold();
					break;
					
				case sf::Keyboard::S:
					game_manager->move_harddrop();
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