/*
 * HaveEnabled.cpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */

#include "HaveEnabled.hpp"

HaveEnabled::HaveEnabled(bool e):
	enabled(e)
{}

bool HaveEnabled::isEnabled() const {
	return enabled;
}

void HaveEnabled::setEnabled(bool enabled) {
	this->enabled = enabled;
}
