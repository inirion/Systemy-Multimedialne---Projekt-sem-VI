/*
* MenuHockeyCreateServer.cpp
*
*  Created on: 31.03.2017
*      Author: jakub
*/

#include "MenuHockeyLobby.hpp"
#include "Program.hpp"

MenuHockeyLobby::MenuHockeyLobby(Program* p, Broadcaster &bb, Server &s) :
	ButtonView(p->getUniPointer()), broadcast(bb), server(s)
{
	MenuButton b;
	std::function<void(const MenuButton&)> f;

	f = std::bind(&Program::hockeyCreateServerEvent, p, std::placeholders::_1);
	b.setName(S::button::create);
	b.setFontSize(medFont);
	b.setSize(medSize);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::Return);
	add(b);

	f = std::bind(&Program::SendStartButtonClickEvent, p, std::placeholders::_1);
	b.setName(S::button::play_btn);
	b.setFontSize(medFont);
	b.setSize(medSize);
	b.setAction(f);
	b.setVisible(false);
	add(b);

	f = std::bind(&Program::hockeySelectMultiEvent, p, std::placeholders::_1);
	b.setName(S::button::back);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::Escape);
	add(b);
}

void MenuHockeyLobby::update() {

	if(!Conf::TCPstart)
	Conf::TCPstart = server.setConnection();

	const float gap = 50.f * Conf::gs;
	sf::Vector2f shift(0, Conf::ws.y*0.5f + gap);
	MenuButton* b;

	b = get(S::button::create);
	if (b != nullptr) {
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5 - b->getSizeReal().x*0.5, 0));
		shift.y += gap + b->getSizeReal().y;
		b->setVisible(false);
	}

	b = get(S::button::play_btn);
	if (b != nullptr) {
		b->setPosition(Conf::refPos + sf::Vector2f(Conf::ws.x - b->getSizeReal().x, Conf::ws.y - b->getSizeReal().y));
		shift.y += gap + b->getSizeReal().y;
		if(Conf::TCPstart)
			b->setVisible(true);
		else 
			b->setVisible(false);
	}

	b = get(S::button::back);
	if (b != nullptr) {
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5 - b->getSizeReal().x*0.5, 0));
		shift.y += gap + b->getSizeReal().y;
	}

	updateButtons();
}
