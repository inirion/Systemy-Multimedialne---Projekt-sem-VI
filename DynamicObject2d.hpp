/*
 * DynamicObject2d.hpp
 *
 *  Created on: 28.04.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja bazowej klasy DynamicObject2d dziedziczącej po Object2d
 *
 * \class DynamicObject2d
 * \brief
 * Bazowa klasa dynamicznego obiektu
 *
 * Klasa reprezentuje dynamiczny obiekt, posiada pola dotyczące prędkości liniowej i obrotowej.
 */
#ifndef DYNAMICOBJECT2D_HPP_
#define DYNAMICOBJECT2D_HPP_

#include "Object2d.hpp"

class DynamicObject2d : public Object2d {
public:
	float getAngularVelocity() const;
	float getLinearVelocity() const;
	void updateLinearVelocity();
	void updateAngularVelocity();

protected:
	sf::Vector2f lastPosition;
	float lastAngle;
	float angularVelocity;
	float linearVelocity;


};


#endif /* DYNAMICOBJECT2D_HPP_ */
