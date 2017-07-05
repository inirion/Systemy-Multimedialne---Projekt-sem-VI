/*
 * MenuHockeyCreateServer.hpp
 *
 *  Created on: 31.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy MenuHockeyCreateServer dziedziczącej po ButtonView
 *
 * \class MenuHockeyCreateServer
 * \brief
 * Klasa reprezentująca widok menu tworzenia serwera.
 */
#ifndef MENUHOCKEYCREATESERVER_HPP_
#define MENUHOCKEYCREATESERVER_HPP_

#include "ButtonView.hpp"

class MenuHockeyCreateServer : public ButtonView {
public:
	MenuHockeyCreateServer(Program* p);
	virtual void update();

private:

};

#endif /* MENUHOCKEYCREATESERVER_HPP_ */
