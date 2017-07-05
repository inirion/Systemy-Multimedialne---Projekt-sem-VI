/*
 * Object2d.hpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy Object2d
 *
 * \class Object2d
 * \brief
 * Bazowa klasa obiektów posiadających pozycję, rozmiar i kąt obrotu.
 */
#ifndef OBJECT2D_HPP_
#define OBJECT2D_HPP_

#include <SFML/System.hpp>
#include <stdexcept>

class Object2d {
public:
	Object2d(sf::Vector2f p = sf::Vector2f(0,0), sf::Vector2f s=sf::Vector2f(0,0));
	virtual ~Object2d(){}
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);
	sf::Vector2f getSize() const;
	void setSize(sf::Vector2f size);
	virtual sf::Vector2f getSizeReal() const;
	float getAngle() const;
	void setAngle(float angle);

protected:
	sf::Vector2f position;
	sf::Vector2f size;
	float angle;
};

float toRad(float deg);


#endif /* OBJECT2D_HPP_ */
