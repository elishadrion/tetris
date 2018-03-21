#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {

	private:
		sf::Vector2f position;
	public:
		Button() = default;
		Button(std::string, const sf::Font&, sf::Vector2f);
}


#endif