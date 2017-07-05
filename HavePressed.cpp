/*
 * HavePressed.cpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */

#include "HavePressed.hpp"

HavePressed::HavePressed(bool p):
	pressed(p)
{

}

bool HavePressed::isPressed() const {
	return pressed;
}

void HavePressed::setPressed(bool pressed) {
	this->pressed = pressed;
}
