/*
 * Object2d.cpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */

#include "Object2d.hpp"

Object2d::Object2d(sf::Vector2f p, sf::Vector2f s):
	position(p),
	size(s),
	angle(0.f)
{

}
sf::Vector2f Object2d::getPosition() const {
	return position;
}

void Object2d::setPosition(sf::Vector2f position) {
	this->position = position;
}

sf::Vector2f Object2d::getSize() const {
	return size;
}

void Object2d::setSize(sf::Vector2f size) {
	this->size = size;
}

sf::Vector2f Object2d::getSizeReal() const {
	return size;
}

float Object2d::getAngle() const {
	return angle;
}

void Object2d::setAngle(float angle) {
	if(angle > 360.f)
		throw std::logic_error("Object2d::setAngle angle > 360.f");
	else if(angle < 0.f)
		throw std::logic_error("Object2d::setAngle angle < 0.f");

	this->angle = angle;
}

float toRad(float deg) {
	return deg * 0.017453293;
}

