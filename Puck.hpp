/**
 * \file
 * \brief
 * Definicja klasy Puck dziedziczącej po sf::Drawable i DynamicObject2d
 *
 * \class Puck
 * \brief
 * Klasa reprezentuje krążek hokejowy
 */

#ifndef PUCK_HPP
#define PUCK_HPP
#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "DynamicObject2d.hpp"
#include "Conf.hpp"
#include "Paddle.hpp"

class Puck: public sf::Drawable, public DynamicObject2d {
private:
	sf::Color color;
	bool wasCollision;

	float dot(sf::Vector2f v1, sf::Vector2f v2);
public:
	Puck();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(bool checkBounds=true);
	bool updateCollision(const Paddle& paddle);
	void setColor(const sf::Color c) { color = c; }
	void resetPos();
};

#endif
