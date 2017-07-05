/*
 * HaveFocus.cpp
 *
 *  Created on: 21.04.2017
 *      Author: jakub
 */

#include "HaveFocus.hpp"
#include <iostream>

HaveFocus* HaveFocus::lastFocus = nullptr;

HaveFocus::HaveFocus(bool f):
	focus(f)
{}

bool HaveFocus::isFocus() const {
	return focus;
}

void HaveFocus::setFocus(bool focus) {
	if(lastFocus != nullptr){
		lastFocus->focus = false;
		if(focus)
			lastFocus = this;
		else
			lastFocus = nullptr;
	}else{
		if(focus)
			lastFocus = this;
	}
	this->focus = focus;
}

void HaveFocus::unFocus() {
	if(lastFocus != nullptr){
		lastFocus->focus = false;
		lastFocus = nullptr;
	}
}
