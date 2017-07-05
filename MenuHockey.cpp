/*
 * MenuHockey.cpp
 *
 *  Created on: 31.03.2017
 *      Author: jakub
 */

#include "MenuHockey.hpp"
#include "Program.hpp"

MenuHockey::MenuHockey(Program* p):
	ButtonView(p->getUniPointer())
{
	MenuButton b;
	std::function<void(const MenuButton&)> f;

	b.setFontSize(bigFont);

	f = std::bind(&Program::launchHockeySingleplayerEvent, p, std::placeholders::_1);
	b.setName(S::button::singleplayer);
	b.setAction(f);
	b.setSize(bigSize);
	b.setHotKey(sf::Keyboard::S);
	add(b);

	f = std::bind(&Program::hockeySelectMultiEvent, p, std::placeholders::_1);
	b.setName(S::button::multiplayer);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::M);
	add(b);

	f = std::bind(&Program::returnToMenuEvent, p, std::placeholders::_1);
	b.setName(S::button::back);
	b.setAction(f);
	b.setSize(medSize);
	b.setFontSize(medFont);
	b.setHotKey(sf::Keyboard::Escape);
	add(b);
}

void MenuHockey::update() {
	const float gap = 50.f * Conf::gs;
	sf::Vector2f shift(0,gap);
	MenuButton* b;
	b=get(S::button::singleplayer);
	if(b!=nullptr){
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5- b->getSizeReal().x*0.5,0));
		shift.y += gap + b->getSizeReal().y;
	}
	b=get(S::button::multiplayer);
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
