/*
 * MenuOptionsSecond.hpp
 *
 *  Created on: 01.05.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy MenuOptionsSecond dziedziczącej po ButtonView
 *
 * \class MenuOptionsSecond
 * \brief
 * Klasa reprezentująca menu drugiej strony opcji.
 */
#ifndef MENUOPTIONSSECOND_HPP_
#define MENUOPTIONSSECOND_HPP_

#include "ButtonView.hpp"
class MenuOptionsSecond : public ButtonView {
public:
	MenuOptionsSecond(Program* p);
	virtual void update();

private:

};

#endif /* MENUOPTIONSSECOND_HPP_ */
