/*
 * MenuMain.hpp
 *
 *  Created on: 25.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy MenuMain dziedziczącej po ButtonView
 *
 * \class MenuMain
 * \brief
 * Klasa reprezentująca widok menu głównego widocznego po uruchomieniu programu.
 */

#ifndef MENUMAIN_HPP_
#define MENUMAIN_HPP_

#include "ButtonView.hpp"

class MenuMain : public ButtonView{
public:
	MenuMain(Program* p);
	virtual void update();

private:

};

#endif /* MENUMAIN_HPP_ */
