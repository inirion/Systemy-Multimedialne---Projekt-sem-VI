/*
* MenuHockeyCreateServer.hpp
*
*  Created on: 31.03.2017
*      Author: jakub
*/
/**
 * \file
 * \brief
 * Definicja klasy MenuHockeyLobby dziedziczącej po ButtonView
 *
 * \class MenuHockeyLobby
 * \brief
 * Klasa reprezentująca widok lobby serwera oczekującego na gracza.
 */
#ifndef MENUHOCKEYCREATELOBBY_HPP_
#define MENUHOCKEYCREATELOBBY_HPP_

#include "ButtonView.hpp"
#include "Server.hpp"
#include "Broadcaster.hpp"

class MenuHockeyLobby : public ButtonView {
public:
	MenuHockeyLobby(Program* p, Broadcaster &bb, Server &s);
	virtual void update();

private:
	Broadcaster &broadcast;
	Server &server;
	
};

#endif /* MENUHOCKEYCREATELOBBY_HPP_ */
