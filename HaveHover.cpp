/*
 * HaveHover.cpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */

#include "HaveHover.hpp"

HaveHover::HaveHover(bool h):
	hover(h)
{}

bool HaveHover::isHover() const {
	return hover;
}

void HaveHover::setHover(bool hover) {
	this->hover = hover;
}

bool HaveHover::updateHover(sf::Vector2f pointer) {
	sf::Vector2f s = getSizeReal();

	if(
		pointer.x < position.x + s.x &&
		pointer.x > position.x &&
		pointer.y < position.y + s.y &&
		pointer.y > position.y
	){
		hover = true;
	}else{
		hover = false;
	}
	return hover;
}
