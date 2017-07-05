/**
 * \file
 * \brief
 * Definicja klasy Paddle dziedziczącej po sf::Drawable i DynamicObject2d
 *
 * \class Paddle
 * \brief
 * Klasa reprezentująca paletkę w grze Air Hockey
 */

#ifndef PADDLE_HPP
#define PADDLE_HPP

#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Graphics.hpp>
#include "DynamicObject2d.hpp"
#include "CameraPointer.hpp"
#include "Conf.hpp"

class Paddle : public sf::Drawable, public DynamicObject2d{
private:

public:
	Paddle();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(CameraPointer &pointer);
};

#endif
