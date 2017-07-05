/*
 * MenuHockeyCreateSideBySide.hpp
 *
 *  Created on: 21.04.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy MenuHockeyCreateSideBySide dziedziczącej po ButtonView
 *
 * \class MenuHockeyCreateSideBySide
 * \brief
 * Klasa reprezentująca widok menu tworzenia gry side by side.
 */
#ifndef MENUHOCKEYCREATESIDEBYSIDE_HPP_
#define MENUHOCKEYCREATESIDEBYSIDE_HPP_

#include "ButtonView.hpp"

class MenuHockeyCreateSideBySide : public ButtonView{
public:
	MenuHockeyCreateSideBySide(Program* p);
	virtual void update();

private:

};

#endif /* MENUHOCKEYCREATESIDEBYSIDE_HPP_ */
