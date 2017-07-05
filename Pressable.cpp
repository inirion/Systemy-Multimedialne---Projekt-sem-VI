/*
 * Pressable.cpp
 *
 *  Created on: 21.04.2017
 *      Author: jakub
 */

#include "Pressable.hpp"


template <typename T>
Pressable<T>::Pressable():
	hotKey(sf::Keyboard::Unknown),
	hotPress(false)
{}

template <typename T>
void Pressable<T>::setPressed(bool pressed) {
	if((hover || hotPress) && this->pressed && !pressed){
		hotPress = false;
		setFocus(true);
		this->doAction();
	}
	this->pressed = pressed;
}

template <typename T>
sf::Keyboard::Key Pressable<T>::getHotKey() const {
	return hotKey;
}

template <typename T>
void Pressable<T>::setHotKey(sf::Keyboard::Key hotKey) {
	this->hotKey = hotKey;
}

template <typename T>
void Pressable<T>::update(sf::Vector2f pointerPos, bool pressed) {
	bool hp = false;

	if(hotKey != sf::Keyboard::Unknown){
		hp = sf::Keyboard::isKeyPressed(hotKey);
		if(hp){
			hotPress = true;
			hover = true;
			setPressed(true);
		}
	}

	if(!hp){
		if(visible && updateHover(pointerPos) && pressed){
			setPressed(true);
		}else{
			setPressed(false);
		}
	}
}


#include "MenuButton.hpp"
template class Pressable<void>;
template class Pressable<const MenuButton&>;
