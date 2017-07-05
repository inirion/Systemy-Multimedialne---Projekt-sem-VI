/*
 * Gate.cpp
 *
 *  Created on: 06.05.2017
 *      Author: jakub
 */

#include "Gate.hpp"

Gate::Gate() {
	size = sf::Vector2f(Conf::gateWidth, Conf::gateHeight);
}

void Gate::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::RectangleShape rs;
	rs.setFillColor(sf::Color::Black);
	rs.setSize(size*Conf::gas);
	rs.setOutlineColor(sf::Color::Red);
	rs.setOutlineThickness(0.05f*Conf::gas);

	float x = (position.x * Conf::gas);
	float y = (position.y * Conf::gas);
	rs.setPosition(x,y);

	target.draw(rs,states);
}
