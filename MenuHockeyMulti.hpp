/*
 * MenuHockeyMulti.hpp
 *
 *  Created on: 31.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy MenuHockeyMulti dziedziczącej po ButtonView
 *
 * \class MenuHockeyMulti
 * \brief
 * Klasa reprezentująca widok menu wyboru trybu side by side, tworzenia serwera i łączenia z serwerem.
 */
#ifndef MENUHOCKEYMULTI_HPP_
#define MENUHOCKEYMULTI_HPP_

#include "ButtonView.hpp"

class MenuHockeyMulti : public ButtonView {
public:
	MenuHockeyMulti(Program* p);
	virtual void update();

private:

};

#endif /* MENUHOCKEYMULTI_HPP_ */
