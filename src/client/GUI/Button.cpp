#include "Button.hpp"

Button::Button(std::string _str, const sf::Font& _font, sf::Vector2f _position): {
	position = _position;
	text.setFont(_font);
	text.setString(str);
	text.setPosition(_position);
	shape.setPosition(_position);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(text);
	target.draw(shape);
}