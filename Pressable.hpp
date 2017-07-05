/*
 * Pressable.hpp
 *
 *  Created on: 21.04.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja bazowej klasy Pressable dziedziczącej po HaveAction, HaveHover, HavePressed, HaveVisible i HaveFocus
 *
 * \class Pressable
 * \brief
 * Bazowa klasa obiektu wciskalnego
 *
 * Bazowa klasa reprezentująca obiekt który można nacisnąć.
 */
#ifndef PRESSABLE_HPP_
#define PRESSABLE_HPP_

#include <functional>
#include <SFML/Graphics.hpp>
#include "HaveHover.hpp"
#include "HavePressed.hpp"
#include "HaveVisible.hpp"
#include "HaveFocus.hpp"
#include "HaveAction.hpp"

template <typename T>
class Pressable : public HaveAction<T>, public HaveHover, public HavePressed, public HaveVisible, public HaveFocus{
public:
	Pressable();
	virtual void setPressed(bool pressed);
	sf::Keyboard::Key getHotKey() const;
	void setHotKey(sf::Keyboard::Key hotKey);
	void update(sf::Vector2f pointerPos=sf::Vector2f(0.f,0.f), bool pressed=false);


protected:
	sf::Keyboard::Key hotKey;
	bool hotPress;
};

#endif /* PRESSABLE_HPP_ */
