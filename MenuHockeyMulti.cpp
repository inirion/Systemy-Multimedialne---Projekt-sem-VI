/*
 * MenuHockeyMulti.cpp
 *
 *  Created on: 31.03.2017
 *      Author: jakub
 */

#include "MenuHockeyMulti.hpp"
#include "Program.hpp"

MenuHockeyMulti::MenuHockeyMulti(Program* p):
	ButtonView(p->getUniPointer())
{
	MenuButton b;
	std::function<void(const MenuButton&)> f;

	f = std::bind(&Program::hockeyCreateSideBySideMenuEvent, p, std::placeholders::_1);
	b.setName(S::button::sidebyside);
	b.setAction(f);
	b.setSize(bigSize);
	b.setFontSize(bigFont);
	b.setHotKey(sf::Keyboard::Num1);
	add(b);

	f = std::bind(&Program::hockeyCreateServerMenuEvent, p, std::placeholders::_1);
	b.setName(S::button::create_lan_server);
	b.setAction(f);
	b.setFontSize(medFont);
	b.setHotKey(sf::Keyboard::Num2);
	add(b);

	f = std::bind(&Program::hockeyConnectToServerMenuEvent, p, std::placeholders::_1);
	b.setName(S::button::connect_lan_server);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::Num3);
	add(b);

	f = std::bind(&Program::hockeySelectEvent, p, std::placeholders::_1);
	b.setName(S::button::back);
	b.setAction(f);
	b.setSize(medSize);
	b.setHotKey(sf::Keyboard::Escape);
	add(b);
}

void MenuHockeyMulti::update() {
	const float gap = 50.f * Conf::gs;
	sf::Vector2f shift(0,gap);
	MenuButton* b;
	b=get(S::button::sidebyside);
	if(b!=nullptr){
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5- b->getSizeReal().x*0.5,0));
		shift.y += gap + b->getSizeReal().y;
	}
	b=get(S::button::create_lan_server);
	if(b!=nullptr){
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5- b->getSizeReal().x*0.5,0));
		shift.y += gap + b->getSizeReal().y;
	}
	b=get(S::button::connect_lan_server);
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
