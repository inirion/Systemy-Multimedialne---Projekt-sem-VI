/*
 * MenuHockeyCreateServer.cpp
 *
 *  Created on: 31.03.2017
 *      Author: jakub
 */

#include "MenuHockeyConnectServer.hpp"
#include "Program.hpp"

MenuHockeyConnectServer::MenuHockeyConnectServer(Program* p, Client& c, Broadcaster &bb):
	ButtonView(p->getUniPointer()), client(c), broadcaster(bb)
{
	MenuButton b;
	std::function<void(const MenuButton&)> f;

	f = std::bind(&MenuHockeyConnectServer::FillButtonList, this, std::placeholders::_1);
	b.setName(S::button::lobby_refresh);
	b.setSize(medSize);
	b.setFontSize(smallFont);
	b.setAction(f);
	add(b);


	f = std::bind(&Program::hockeySelectMultiEvent, p, std::placeholders::_1);
	b.setName(S::button::back);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::Escape);
	add(b);
}

void MenuHockeyConnectServer::update() {

	sf::Vector2f pp = uniPointer.getPos();
	bool p = uniPointer.isPressed();

	sf::Vector2f shift(0,0);
	MenuButton* b;

	b=get(S::button::lobby_refresh);
	if(b!=nullptr){
		b->setPosition(Conf::refPos + sf::Vector2f(Conf::ws.x - b->getSizeReal().x, 0));
	}
	b=get(S::button::back);
	if(b!=nullptr){
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5- b->getSizeReal().x*0.5,0));
	}
	for (auto& btn : btns) {
		btn.setPosition(Conf::refPos + shift + sf::Vector2f(0, btn.getSizeReal().y));
		btn.update(pp, p);
		shift.y += btn.getSizeReal().y;
	}
	updateButtons();
}

void MenuHockeyConnectServer::StartConnection(const MenuButton& btn)
{
	std::cout << "StartConnection" << std::endl;
	Conf::TCPstart = client.setConnection(btn.getAdress());
	std::cout << btn.getAdress().toString() << " " << Conf::TCPstart << std::endl;
}

bool MenuHockeyConnectServer::GetStartButtonClick()
{
	sf::Packet p;
	if (client.Recive(p)) {
		int a;
		p >> a;
		if (0 == a) {
			return true;
		}
	}
	return false;
}

void MenuHockeyConnectServer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	ButtonView::draw(target, states);
	for (auto &btn : btns) {
		target.draw(btn);
	}
}

void MenuHockeyConnectServer::FillButtonList(const MenuButton&)
{
	std::cout << "FillButtonList" << std::endl;
	btns.clear();
	MenuButton b;
	std::function<void(const MenuButton&)> f;

	f = std::bind(&MenuHockeyConnectServer::StartConnection, this, std::placeholders::_1);
	b.setFontSize(medFont);
	b.setSize(sf::Vector2f(900,150));
	b.setAction(f);
	for (auto connection : broadcaster.getConns()) {
		if (connection.second != sf::IpAddress("0.0.0.0")) {
			std::string name(connection.first.begin(), connection.first.end());
			b.setName(name);
			b.setAdress(connection.second);
			btns.push_back(b);
		}
	}
}
