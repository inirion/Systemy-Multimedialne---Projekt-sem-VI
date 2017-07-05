/*
 * MenuMain.cpp
 *
 *  Created on: 25.03.2017
 *      Author: jakub
 */

#include "MenuMain.hpp"
#include "Program.hpp"

MenuMain::MenuMain(Program* p):
	ButtonView(p->getUniPointer())
{
	MenuButton b;
	std::function<void(const MenuButton&)> f;

	b.setFontSize(bigFont);

	f = std::bind(&Program::hockeySelectEvent, p, std::placeholders::_1);
	b.setName(S::button::pong);
	b.setAction(f);
	b.setSize(bigSize);
	b.setHotKey(sf::Keyboard::N);
	add(b);

	f = std::bind(&Program::launchPaintEvent, p, std::placeholders::_1);
	b.setName(S::button::paint);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::P);
	add(b);

	f = std::bind(&Program::openOptionsFirstEvent, p, std::placeholders::_1);
	b.setName(S::button::options);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::O);
	add(b);
}

void MenuMain::update() {
	const float gap = 50.f * Conf::gs;
	sf::Vector2f shift(0,gap);
	MenuButton* b;
	b=get(S::button::pong);
	if(b!=nullptr){
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5- b->getSizeReal().x*0.5,0));
		shift.y += gap + b->getSizeReal().y;
	}
	b=get(S::button::paint);
	if(b!=nullptr){
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5- b->getSizeReal().x*0.5,0));
		shift.y += gap + b->getSizeReal().y;
	}
	b=get(S::button::options);
	if(b!=nullptr){
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5- b->getSizeReal().x*0.5,0));
		shift.y += gap + b->getSizeReal().y;
	}

	updateButtons();
}
