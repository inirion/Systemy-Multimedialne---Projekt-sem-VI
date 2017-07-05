/*
 * MenuHockey.hpp
 *
 *  Created on: 31.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy MenuHockey dziedziczącej po ButtonView
 *
 * \class MenuHockey
 * \brief
 * Klasa reprezentująca widok menu wyboru trybu singleplayer i multiplayer.
 */
#ifndef MENUHOCKEY_HPP_
#define MENUHOCKEY_HPP_

#include "ButtonView.hpp"

class MenuHockey : public ButtonView {
public:
	MenuHockey(Program* p);
	virtual void update();

private:

};

#endif /* MENUHOCKEY_HPP_ */
