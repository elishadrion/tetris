#include "Board_GUI.hpp"


Board_GUI::Board_GUI(bool vs, unsigned wwidth, unsigned wheight, Grid* _grid, Grid* _other_grid): vs(vs), grid(_grid), other_grid(_other_grid) {
	font.loadFromFile("arial.ttf");
	score_first.setFont(font);
	lines_completed_first.setFont(font);
	hold_first.setFont(font);
	next_first.setFont(font);

	score_first.setString("Score : 0");
	score_first.setPosition(sf::Vector2f(infos_x[0], 10));
	lines_completed_first.setString("Lines : 0");
	lines_completed_first.setPosition(sf::Vector2f(infos_x[0], 50));
	next_first.setString("Next :");
	next_first.setPosition(sf::Vector2f(infos_x[0], y_position_next_text));
	hold_first.setString("Hold :");
	hold_first.setPosition(sf::Vector2f(infos_x[0], y_position_hold_text));

	vertices_first_grid.setPrimitiveType(sf::Quads);
	vertices_first_grid.resize(width*height*4);
	vertices_next_tetriminos_first.setPrimitiveType(sf::Quads);
	vertices_next_tetriminos_first.resize(64);
	vertices_hold_tetriminos_first.setPrimitiveType(sf::Quads);
	vertices_hold_tetriminos_first.resize(64);

	if (vs) {
		score_second.setFont(font);
		lines_completed_second.setFont(font);
		hold_second.setFont(font);
		next_second.setFont(font);

		score_second.setString("Score : 0");
		score_second.setPosition(sf::Vector2f(infos_x[1], 10));
		lines_completed_second.setString("Lines : 0");
		lines_completed_second.setPosition(sf::Vector2f(infos_x[1], 50));
		next_second.setString("Next :");
		next_second.setPosition(sf::Vector2f(infos_x[1], y_position_next_text));
		hold_second.setString("Hold :");
		hold_second.setPosition(sf::Vector2f(infos_x[0], y_position_hold_text));

		vertices_second_grid.setPrimitiveType(sf::Quads);
		vertices_second_grid.resize(width*height*4);
		vertices_next_tetriminos_second.setPrimitiveType(sf::Quads);
		vertices_next_tetriminos_second.resize(64);
		vertices_hold_tetriminos_second.setPrimitiveType(sf::Quads);
		vertices_hold_tetriminos_second.resize(64);
	}
	fill_with_blocs();
	window.create(sf::VideoMode(wwidth, wheight), "Fenêtre");
	window.setFramerateLimit(60);
}

void Board_GUI::start() {
	usleep(100);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			handle_event(event);
		}
		update_display();
	}
}

void Board_GUI::update_display() {
	for (unsigned i = 0; i < width; i++) {
		for (unsigned j = 0; j < height; j++) {
			sf::Vertex* bloc = &vertices_first_grid[(i + j*width)*4];
			color_bloc(bloc, grid, i, j);
			update_next_tetriminos_case();
			update_hold_tetriminos_case();
	
			if (vs) {
				bloc = &vertices_second_grid[(i+j*width)*4];
				color_bloc(bloc, other_grid, i, j);
			}

		}
	}
	window.clear();
	update_score_and_lines();
	draw_text();
	draw_vertices();
	window.display();
}

void Board_GUI::draw_text() {
	window.draw(score_first);
	window.draw(lines_completed_first);
	window.draw(next_first);
	window.draw(hold_first);
	if (vs) {
		window.draw(score_second);
		window.draw(lines_completed_second);
		window.draw(next_second);
		window.draw(hold_second);
	}
}

void Board_GUI::draw_vertices() {
	window.draw(vertices_first_grid);
	window.draw(vertices_next_tetriminos_first);
	window.draw(vertices_hold_tetriminos_first);
	if (vs) {
		window.draw(vertices_second_grid);
		window.draw(vertices_next_tetriminos_second);
		window.draw(vertices_hold_tetriminos_second);
	}
}

void Board_GUI::update_score_and_lines() {
	score_first.setString("Score : "+ std::to_string(grid->get_score()));
	lines_completed_first.setString("Lines : "+ std::to_string(grid->get_line_complete()));
	if (vs) {
		score_second.setString("Score : "+ std::to_string(other_grid->get_score()));
		lines_completed_second.setString("Lines : "+ std::to_string(other_grid->get_line_complete()));
	}
}

void Board_GUI::update_next_tetriminos_case() {
	//On colorie tout en noir
	for (unsigned i = 0; i < 4; i++) {
		for (unsigned j = 0; j < 4; j++) {
			sf::Vertex* bloc = &vertices_next_tetriminos_first[(i + j*4)*4];
			for (unsigned k=0; k < 4; k++)
				bloc[k].color = sf::Color::Black;
			if (vs) {
				bloc = &vertices_next_tetriminos_second[(i + j*4)*4];
				for (unsigned k=0; k < 4; k++)
					bloc[k].color = sf::Color::Black;
			}

		}
	}
	unsigned x,y;
	for (unsigned i = 0; i < 4; i++) {
		y = (grid->get_next_tetriminos()->get_coord_Y_of_block(i)+3);
		x = (grid->get_next_tetriminos()->get_coord_X_of_block(i)-3);
		sf::Vertex* bloc = &vertices_next_tetriminos_first[(x+ y*4)*4];
		sf::Color color = translate_to_color(grid->get_next_tetriminos()->get_color_of_block(0));
		for (unsigned k=0; k < 4; k++)
			bloc[k].color = color;

		if (vs) {
			y = (other_grid->get_next_tetriminos()->get_coord_Y_of_block(i)+3);
			x = (other_grid->get_next_tetriminos()->get_coord_X_of_block(i)-3);
			sf::Vertex* bloc = &vertices_next_tetriminos_second[(x+ y*4)*4];
			sf::Color color = translate_to_color(other_grid->get_next_tetriminos()->get_color_of_block(0));
			for (unsigned k=0; k < 4; k++)
				bloc[k].color = color;
		}
	}
}

void Board_GUI::update_hold_tetriminos_case() {
	//On colorie tout en noir
	for (unsigned i = 0; i < 4; i++) {
		for (unsigned j = 0; j < 4; j++) {
			sf::Vertex* bloc = &vertices_hold_tetriminos_first[(i + j*4)*4];
			for (unsigned k=0; k < 4; k++)
				bloc[k].color = sf::Color::Black;
			if (vs) {
				bloc = &vertices_hold_tetriminos_second[(i + j*4)*4];
				for (unsigned k=0; k < 4; k++)
					bloc[k].color = sf::Color::Black;
			}

		}
	}
	unsigned x,y;
	if (grid->get_hold_tetriminos() != nullptr) {
		for (unsigned i = 0; i < 4; i++) {
			y = (grid->get_hold_tetriminos()->get_coord_Y_of_block(i)+3);
			x = (grid->get_hold_tetriminos()->get_coord_X_of_block(i)-3);
			sf::Vertex* bloc = &vertices_hold_tetriminos_first[(x+ y*4)*4];
			sf::Color color = translate_to_color(grid->get_hold_tetriminos()->get_color_of_block(0));
			for (unsigned k=0; k < 4; k++)
				bloc[k].color = color;
		}
	}

	if (vs and other_grid->get_hold_tetriminos() != nullptr) {
		for (unsigned i = 0; i < 4; i++) {
			y = (other_grid->get_hold_tetriminos()->get_coord_Y_of_block(i)+3);
			x = (other_grid->get_next_tetriminos()->get_coord_X_of_block(i)-3);
			sf::Vertex* bloc = &vertices_hold_tetriminos_second[(x+ y*4)*4];
			sf::Color color = translate_to_color(other_grid->get_hold_tetriminos()->get_color_of_block(0));
			for (unsigned k=0; k < 4; k++)
				bloc[k].color = color;
		}
	}
}

void Board_GUI::fill_with_blocs() {
	//Pour les cases du next tetriminos
	for (unsigned i = 0; i < 4; i++) {
		for (unsigned j = 0; j < 4; j++) {
			sf::Vertex* bloc = &vertices_next_tetriminos_first[(i + j*4)*4];
			bloc[0].position = sf::Vector2f(infos_x[0]+(i*BLOC_SIZE), y_position_next+(j*BLOC_SIZE));
			//1 coin inférieure gauche
			bloc[1].position = sf::Vector2f(infos_x[0]+((i+1)*BLOC_SIZE), y_position_next+(j*BLOC_SIZE));
			//2 coin inférieur droit
			bloc[2].position = sf::Vector2f(infos_x[0]+((i+1)*BLOC_SIZE), y_position_next+((j+1)*BLOC_SIZE));
			//3 coin supérieur droit
			bloc[3].position = sf::Vector2f(infos_x[0]+(i*BLOC_SIZE), y_position_next+((j+1)*BLOC_SIZE));

			if (vs) {
				sf::Vertex* bloc = &vertices_next_tetriminos_second[(i + j*4)*4];
				bloc[0].position = sf::Vector2f(infos_x[1]+(i*BLOC_SIZE), y_position_next+(j*BLOC_SIZE));
				bloc[1].position = sf::Vector2f(infos_x[1]+((i+1)*BLOC_SIZE), y_position_next+(j*BLOC_SIZE));
				bloc[2].position = sf::Vector2f(infos_x[1]+((i+1)*BLOC_SIZE), y_position_next+((j+1)*BLOC_SIZE));
				bloc[3].position = sf::Vector2f(infos_x[1]+(i*BLOC_SIZE), y_position_next+((j+1)*BLOC_SIZE));
			}
		}
	}
	//Pour les cases du hold tetriminos
	for (unsigned i = 0; i < 4; i++) {
		for (unsigned j = 0; j < 4; j++) {
			sf::Vertex* bloc = &vertices_hold_tetriminos_first[(i + j*4)*4];
			bloc[0].position = sf::Vector2f(infos_x[0]+(i*BLOC_SIZE), y_position_hold+(j*BLOC_SIZE));
			//1 coin inférieure gauche
			bloc[1].position = sf::Vector2f(infos_x[0]+((i+1)*BLOC_SIZE), y_position_hold+(j*BLOC_SIZE));
			//2 coin inférieur droit
			bloc[2].position = sf::Vector2f(infos_x[0]+((i+1)*BLOC_SIZE), y_position_hold+((j+1)*BLOC_SIZE));
			//3 coin supérieur droit
			bloc[3].position = sf::Vector2f(infos_x[0]+(i*BLOC_SIZE), y_position_hold+((j+1)*BLOC_SIZE));

			if (vs) {
				sf::Vertex* bloc = &vertices_hold_tetriminos_second[(i + j*4)*4];
				bloc[0].position = sf::Vector2f(infos_x[1]+(i*BLOC_SIZE), y_position_hold+(j*BLOC_SIZE));
				bloc[1].position = sf::Vector2f(infos_x[1]+((i+1)*BLOC_SIZE), y_position_hold+(j*BLOC_SIZE));
				bloc[2].position = sf::Vector2f(infos_x[1]+((i+1)*BLOC_SIZE), y_position_hold+((j+1)*BLOC_SIZE));
				bloc[3].position = sf::Vector2f(infos_x[1]+(i*BLOC_SIZE), y_position_hold+((j+1)*BLOC_SIZE));
			}
		}
	}
	//Pour les grilles de jeu
	for (unsigned i = 0; i < width; i++) {
		for (unsigned j = 0; j < height; j++) {
			sf::Vertex* bloc = &vertices_first_grid[(i + j*width)*4];
			bloc[0].position = sf::Vector2f(limits_x[0]+(i*BLOC_SIZE), limits_y[0]+(j*BLOC_SIZE));
			bloc[1].position = sf::Vector2f(limits_x[0]+((i+1)*BLOC_SIZE), limits_y[0]+(j*BLOC_SIZE));
			bloc[2].position = sf::Vector2f(limits_x[0]+((i+1)*BLOC_SIZE), limits_y[0]+((j+1)*BLOC_SIZE));
			bloc[3].position = sf::Vector2f(limits_x[0]+(i*BLOC_SIZE), limits_y[0]+((j+1)*BLOC_SIZE));
			if (vs) {
				bloc = &vertices_second_grid[(i + j*width)*4];
				bloc[0].position = sf::Vector2f(limits_x[1]+(i*BLOC_SIZE), limits_y[0]+(j*BLOC_SIZE));
				bloc[1].position = sf::Vector2f(limits_x[1]+((i+1)*BLOC_SIZE), limits_y[0]+(j*BLOC_SIZE));
				bloc[2].position = sf::Vector2f(limits_x[1]+((i+1)*BLOC_SIZE), limits_y[0]+((j+1)*BLOC_SIZE));
				bloc[3].position = sf::Vector2f(limits_x[1]+(i*BLOC_SIZE), limits_y[0]+((j+1)*BLOC_SIZE));
			}
		}
	}
}

void Board_GUI::color_bloc(sf::Vertex* bloc, Grid* grid, unsigned i, unsigned j) {
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


void Board_GUI::handle_event(const sf::Event& event) {

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

sf::Color Board_GUI::translate_to_color(unsigned color_num) {
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
			color = sf::Color(128,128,128);
			break;
	}
	return color;
}