/*
 * MenuOptions.cpp
 *
 *  Created on: 25.03.2017
 *      Author: jakub
 */

#include "MenuOptionsFirst.hpp"
#include "Program.hpp"

MenuOptionsFirst::MenuOptionsFirst(Program* p):
	ButtonView(p->getUniPointer())
{
	MenuButton b;
	std::function<void(const MenuButton&)> f;

	f = std::bind(&Program::optionsBackEvent, p, std::placeholders::_1);
	b.setName(S::button::back);
	b.setAction(f);
	b.setFontSize(smallFont);
	b.setSize(sf::Vector2f(300,100));
	b.setHotKey(sf::Keyboard::Escape);
	add(b);

	f = std::bind(&Program::defaultsOptionsEvent, p, std::placeholders::_1);
	b.setName(S::button::defaults);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::F12);
	add(b);

	f = std::bind(&Program::openOptionsSecondEvent, p, std::placeholders::_1);
	b.setName(S::button::options_second);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::O);
	add(b);
}

void MenuOptionsFirst::update() {
	const float gap = 50.f * Conf::gs;
	sf::Vector2f shift(0,gap);

	MenuButton* b;
	b=get(S::button::back);
	if(b!=nullptr){
		sf::Vector2f rs = b->getSizeReal();
		b->setPosition(Conf::refPos + sf::Vector2f(gap, Conf::ws.y - rs.y-gap));
		shift.y += gap + rs.y;
	}
	b=get(S::button::defaults);
	if(b!=nullptr){
		sf::Vector2f rs = b->getSizeReal();
		b->setPosition(Conf::refPos + sf::Vector2f(Conf::ws.x - rs.x - gap, Conf::ws.y - rs.y-gap));
		shift.y += gap + rs.y;
	}
	b=get(S::button::options_second);
	if(b!=nullptr){
		sf::Vector2f rs = b->getSizeReal();
		b->setPosition(Conf::refPos + sf::Vector2f(Conf::ws.x*0.5f - rs.x*0.5f, Conf::ws.y - rs.y-gap));
		shift.y += gap + rs.y;
	}

	updateButtons();
}
