/*
 * Gate.hpp
 *
 *  Created on: 06.05.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy Gate dziedziczącej po public sf::Drawable i Object2d
 *
 * \class Gate
 * \brief
 * Klasa bramki w grze
 *
 * Klasa reprezentuje bramkę w grze Air Hockey.
 */

#ifndef GATE_HPP_
#define GATE_HPP_

#include <SFML/Graphics.hpp>
#include "Object2d.hpp"
#include "Conf.hpp"

class Gate : public sf::Drawable, public Object2d{
private:
	
public:
	Gate();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif /* GATE_HPP_ */
