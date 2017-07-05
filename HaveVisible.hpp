/*
 * HaveVisible.hpp
 *
 *  Created on: 25.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja bazowej klasy HaveVisible
 *
 * \class HaveVisible
 * \brief
 * Bazowa klasa obiektu posiadający stan widoczności
 *
 * Bazowa klasa posiadająca pole visible oraz jego mutator i akcesor.
 */

#ifndef HAVEVISIBLE_HPP_
#define HAVEVISIBLE_HPP_

class HaveVisible {
public:
	HaveVisible(bool v = true);
	bool isVisible() const;
	void setVisible(bool visible);

protected:
	bool visible;
};

#endif /* HAVEVISIBLE_HPP_ */
