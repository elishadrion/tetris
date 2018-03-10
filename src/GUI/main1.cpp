#include <SFML/Graphics.hpp>
#include "Constants.hpp"

bool within_limits(unsigned x, unsigned y) {
	bool is_within = true;
	if (x < limits_x[0] or x > limits_x[1])
		is_within = false;
	if (y < limits_y[0] or y > limits_y[1])
		is_within = false;
	return is_within;
}

void move_bloc_up(sf::Vertex* bloc) {
	bool is_within = within_limits(bloc[0].position.x, bloc[0].position.y-20);
	if (is_within) {
		for (unsigned i = 0; i < 4; i++) {
			bloc[i].position.y -= 20;
		}
	}
}

void move_bloc_down(sf::Vertex* bloc) {
	bool is_within = within_limits(bloc[0].position.x, bloc[0].position.y+20);
	if (is_within) {
		for (unsigned i = 0; i < 4; i++) {
			bloc[i].position.y += 20;
		}
	}
}

void move_bloc_right(sf::Vertex* bloc) {
	bool is_within = within_limits(bloc[0].position.x+20, bloc[0].position.y);
	if (is_within) {
		for (unsigned i = 0; i < 4; i++) {
			bloc[i].position.x += 20;
		}
	}
}

void move_bloc_left(sf::Vertex* bloc) {
	bool is_within = within_limits(bloc[0].position.x-20, bloc[0].position.y);
	if (is_within) {
		for (unsigned i = 0; i < 4; i++) {
			bloc[i].position.x -= 20;
		}
	}
}

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Fenêtre");
	window.setFramerateLimit(30);
	sf::VertexArray vertices(sf::Quads, width*height*4);
	sf::Vertex* quad = &vertices[0];
	//0 coin supérieur gauche
	quad[0].position = sf::Vector2f(220, 440);
	//1 coin inférieure gauche
	quad[1].position = sf::Vector2f(220, 460);
	//2 coin inférieur droit
	quad[2].position = sf::Vector2f(240, 460);
	//3 coin supérieur droit
	quad[3].position = sf::Vector2f(240, 440);


	quad[0].color = sf::Color::Red;
	quad[1].color = sf::Color::Red;
	quad[2].color = sf::Color::Red;
	quad[3].color = sf::Color::Red;



	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			switch(event.type) {

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:

				switch(event.key.code) {
					case sf::Keyboard::Up:
						move_bloc_up(quad);
						break;
					case sf::Keyboard::Down:
						move_bloc_down(quad);
						break;
					case sf::Keyboard::Right:
						move_bloc_right(quad);
						break;
					case sf::Keyboard::Left:
						move_bloc_left(quad);
						break;
				}
				break;
			}
		}

		window.clear();
		window.draw(vertices);
		window.display();
	}
	return 0;
}