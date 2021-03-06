/*
 * MenuHockeyCreateServer.cpp
 *
 *  Created on: 31.03.2017
 *      Author: jakub
 */

#include "MenuHockeyCreateServer.hpp"
#include "Program.hpp"

MenuHockeyCreateServer::MenuHockeyCreateServer(Program* p):
	ButtonView(p->getUniPointer())
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

	f = std::bind(&Program::hockeySelectMultiEvent, p, std::placeholders::_1);
	b.setName(S::button::back);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::Escape);
	add(b);
}

void MenuHockeyCreateServer::update() {
	const float gap = 50.f * Conf::gs;
	sf::Vector2f shift(0, Conf::ws.y*0.5f + gap);
	MenuButton* b;

	b=get(S::button::create);
	if(b!=nullptr){
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5- b->getSizeReal().x*0.5,0));
		shift.y += gap + b->getSizeReal().y;
	}

	b=get(S::button::back);
	if(b!=nullptr){
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5- b->getSizeReal().x*0.5,0));
		shift.y += gap + b->getSizeReal().y;
	}

	updateButtons();
}
