/*
 * MenuHockeyCreateServer.hpp
 *
 *  Created on: 31.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy MenuHockeyConnectServer dziedziczącej po ButtonView
 *
 * \class MenuHockeyConnectServer
 * \brief
 * Klasa reprezentująca widok menu wyboru serwera.
 */

#ifndef MENUHOCKEYCONNECTSERVER_HPP_
#define MENUHOCKEYCONNECTSERVER_HPP_

#include "ButtonView.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Broadcaster.hpp"

using connections = std::vector<std::pair<std::wstring, sf::IpAddress>>;

class MenuHockeyConnectServer : public ButtonView {
public:
	MenuHockeyConnectServer(Program* p, Client &c, Broadcaster &bb);
	virtual void update();
	bool GetStartButtonClick();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
private:
	std::vector<MenuButton> btns;
	Client &client;
	Broadcaster &broadcaster;
	void StartConnection(const MenuButton& );
	void FillButtonList(const MenuButton&);
};

#endif /* MENUHOCKEYCONNECTSERVER_HPP_ */
