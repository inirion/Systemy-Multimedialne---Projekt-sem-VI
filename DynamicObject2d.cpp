/*
 * DynamicObject2d.cpp
 *
 *  Created on: 28.04.2017
 *      Author: jakub
 */

#include "DynamicObject2d.hpp"
#include <cmath>

float DynamicObject2d::getAngularVelocity() const {
	return angularVelocity;
}

float DynamicObject2d::getLinearVelocity() const {
	return linearVelocity;
}

void DynamicObject2d::updateLinearVelocity() {
	sf::Vector2f diffPos = lastPosition - position;
	linearVelocity = std::sqrt(diffPos.x*diffPos.x + diffPos.y*diffPos.y);
}

void DynamicObject2d::updateAngularVelocity() {
	angularVelocity = 180 - std::abs(std::abs(angle - lastAngle) - 180);
	if(lastAngle - angle < 0)
		angularVelocity*=-1.f;
}
