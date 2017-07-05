/*
 * MenuDefaultsAsk.cpp
 *
 *  Created on: 25.03.2017
 *      Author: jakub
 */

#include "MenuDefaultsAsk.hpp"
#include "Program.hpp"

MenuDefaultsAsk::MenuDefaultsAsk(Program* p):
	ButtonView(p->getUniPointer())
{
	MenuButton b;
	std::function<void(const MenuButton&)> f;

	f = std::bind(&Program::defaultsOptionsEvent, p, std::placeholders::_1);
	b.setAction(f);
	b.setName(S::button::yes);
	b.setFontSize(medFont);
	b.setSize(medSize);
	add(b);

	b.setName(S::button::no);
	b.setHotKey(sf::Keyboard::Escape);
	add(b);
}

void MenuDefaultsAsk::update() {
	const float gap = 50.f * Conf::gs;
	sf::Vector2f shift(0,gap);

	MenuButton* b;
	b=get(S::button::yes);
	if(b!=nullptr){
		sf::Vector2f rs = b->getSizeReal();
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5 - rs.x - gap,Conf::ws.y*0.5));
	}
	b=get(S::button::no);
	if(b!=nullptr){
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5 + gap, Conf::ws.y*0.5));
	}

	updateButtons();
}
