/*
 * HaveVisible.cpp
 *
 *  Created on: 25.03.2017
 *      Author: jakub
 */

#include "HaveVisible.hpp"

HaveVisible::HaveVisible(bool v):
	visible(v)
{

}

bool HaveVisible::isVisible() const {
	return visible;
}

void HaveVisible::setVisible(bool visible) {
	this->visible = visible;
}
