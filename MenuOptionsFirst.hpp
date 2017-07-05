/*
 * MenuOptions.hpp
 *
 *  Created on: 25.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy MenuOptionsFirst dziedziczącej po ButtonView
 *
 * \class MenuOptionsFirst
 * \brief
 * Klasa reprezentująca menu pierwszej strony opcji
 */
#ifndef MENUOPTIONSFIRST_HPP_
#define MENUOPTIONSFIRST_HPP_

#include "ButtonView.hpp"
class MenuOptionsFirst : public ButtonView {
public:
	MenuOptionsFirst(Program* p);
	virtual void update();

private:

};

#endif /* MENUOPTIONSFIRST_HPP_ */
