/*
 * MousePointer.cpp
 *
 *  Created on: 25.03.2017
 *      Author: jakub
 */

#include "MousePointer.hpp"
#include "Conf.hpp"

MousePointer::MousePointer(sf::RenderWindow& rw):
	rw(rw),
	lastMouseMoveTime(0.f),
	mouseFocus(true)
{

}

void MousePointer::update() {
	lastPos = pos;
	rawPos = sf::Mouse::getPosition(rw);
	pos = rw.mapPixelToCoords(rawPos);
	posDiff = pos - lastPos;

	if(posDiff.x != 0.f || posDiff.y != 0.f){
		lastMouseMoveTime = Conf::rt;
		rw.setMouseCursorVisible(true);
		mouseFocus = true;
	}else{
		if(Conf::rt - lastMouseMoveTime > 3.f){
			rw.setMouseCursorVisible(false);
			mouseFocus=false;
		}
	}
	if(
		rawPos.x <= 0 ||
		rawPos.y <= 0 ||
		rawPos.x >= (int)Conf::ws.x ||
		rawPos.y >= (int)Conf::ws.y
	){
		mouseFocus = false;
	}


	if(mouseFocus){
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			pressed = true;
		}else{
			pressed = false;
		}
	}
}

sf::Vector2f MousePointer::getPosDiff() const {
	return posDiff;
}

sf::Vector2f MousePointer::getPos() const {
	return pos;
}

sf::Vector2i MousePointer::getRawPos() const {
	return rawPos;
}


bool MousePointer::isMouseFocus() const {
	return mouseFocus;
}
