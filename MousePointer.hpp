/*
 * MousePointer.hpp
 *
 *  Created on: 25.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy MousePointer dziedziczącej po HavePressed
 *
 * \class MousePointer
 * \brief
 * Klasa reprezentująca mysz
 *
 * Klasa reprezentuje mysz i zwiększa funkcjonalność standardowej klasy sf::Mouse
 */
#ifndef MOUSEPOINTER_HPP_
#define MOUSEPOINTER_HPP_

#include <SFML/Graphics.hpp>
#include "HavePressed.hpp"

class MousePointer : public HavePressed {
public:
	MousePointer(sf::RenderWindow& rw);
	void update();
	sf::Vector2f getPosDiff() const;
	sf::Vector2f getPos() const;
	sf::Vector2i getRawPos() const;
	bool isMouseFocus() const;

private:
	sf::RenderWindow& rw;
	sf::Vector2f pos;
	sf::Vector2f lastPos;
	sf::Vector2f posDiff;
	sf::Vector2i rawPos;

	float lastMouseMoveTime;
	bool mouseFocus;
};

#endif /* MOUSEPOINTER_HPP_ */
