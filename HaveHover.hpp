/*
 * HaveHover.hpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja bazowej klasy HaveHover dziedziczącej po Object2d
 *
 * \class HaveHover
 * \brief
 * Bazowa klasa obiektu posiadającego stan wskazywania przez kursor.
 *
 * Bazowa klasa posiadająca pole hover i metody do jego aktualizacji.
 */

#ifndef HAVEHOVER_HPP_
#define HAVEHOVER_HPP_

#include "Object2d.hpp"

class HaveHover : public Object2d {
public:
	HaveHover(bool h = false);
	bool isHover() const;
	void setHover(bool hover);
	bool updateHover(sf::Vector2f pointer);

protected:
	bool hover;

};

#endif /* HAVEHOVER_HPP_ */
