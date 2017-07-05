/*
 * HavePressed.hpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja bazowej klasy HavePressed
 *
 * \class HavePressed
 * \brief
 * Bazowa klasa obiektu posiadający stan wciśnięcia
 *
 * Bazowa klasa posiadająca pole pressed oraz jego mutator i akcesor.
 */


#ifndef HAVEPRESSED_HPP_
#define HAVEPRESSED_HPP_

class HavePressed {
public:
	HavePressed(bool p = false);
	virtual ~HavePressed(){}
	virtual bool isPressed() const;
	virtual void setPressed(bool pressed);
protected:
	bool pressed;
};

#endif /* HAVEPRESSED_HPP_ */
